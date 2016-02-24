/*
 *	Author: Chris Zehr, ch452589
 * 	COP 3502 - CS 1 Section 1 Spring 2016
 *
 * 	Lab 4
 * 	2/22/2016
 */

/*  
 *	Libraries and definitions
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define RIDE_TIME 120				/* Time in Seconds */
#define WALK_SPEED 1 				/* Meters / Second */
#define DAY_LENGTH 86400			/* Seconds / Day */

/*
 *	Structs
 */
struct ThemePark
{

	int 	numRides;				/* numRides < 11 */
	int 	numBlockedPaths;		/* numBlockedPaths < numRides^2 */
	double 	bestRouteTime;			/* Time to finish all rides in seconds */

	double 	*startPoint;			/* Initialized to {0,0} */
	double 	**parkMap;				/* numRides * 2 */
	double 	**nodeNetwork;			/* numRides * numRides */
	int 	*nodeRoute;				/* numRides */				
};

/*
 *	Function Declaration
 */
void initialize(	struct ThemePark *parkInstance);
void close(			struct ThemePark *parkInstance);
void getRouteTime(	struct ThemePark *parkInstance);

void getShortestRoute(	struct ThemePark *parkInstance, 
						int startIndex, 
						int endIndex);

double getDistance(	double point1[], 
					double point2[]);

void swapInts(		int *x, 
					int *y);


/*
 *	Main
 */
int main(){

	int numInputCases, i;
	struct ThemePark parkInstance;
	scanf("%d", &numInputCases);

	/* Loop through each case */
	for(i = 0; i < numInputCases; i++)
	{
		/* Allocate memory, read input and generate nodeNetwork */
		initialize(&parkInstance);

		/* Calculate shortest route */
		getShortestRoute(&parkInstance, 0, parkInstance.numRides - 1);

		/* Print results */
		if(parkInstance.bestRouteTime <= DAY_LENGTH)
			printf("Vacation #%d:\nJimmy can finish all of the rides in %.3f seconds.\n\n", 
					i + 1, parkInstance.bestRouteTime);
		else
			printf("Vacation #%d:\nJimmy should plan this vacation a different day.\n\n", i + 1);
		
		/* Free memory */
		close(&parkInstance);
	}

	return 0;
}


/*
 *	Function Implementation
 */

/* Allocate memory for a ThemePark instance, create the node network, and calculate distances */
void initialize(struct ThemePark *parkInstance)
{
	
	int i, j;						/* Iterators */
	double parkEntrance[] = {0,0};	/* Given starting point */
	int node1, node2;				/* Nodes with blocked path */

	/* Initialize member values */
	parkInstance->bestRouteTime = DAY_LENGTH + 1;
	parkInstance->startPoint = parkEntrance;

	/* Read parkInstance info from stdin */
	scanf("%d", &parkInstance->numRides);
	scanf("%d", &parkInstance->numBlockedPaths);

	/* Allocate matrix for nodeNetwork (including numRides extra spaces and distance "both ways") */
	double **nodeMatrix = (double **)malloc(sizeof(*nodeMatrix) * parkInstance->numRides);
    for (i = 0; i < parkInstance->numRides; i++)
        nodeMatrix[i] = (double *)malloc(sizeof(**nodeMatrix) * parkInstance->numRides);
    parkInstance->nodeNetwork = nodeMatrix;

    /* Allocate matrix for parkMap */
    double **mapMatrix = (double **)malloc(sizeof(*mapMatrix) * parkInstance->numRides);
    for(i = 0; i < parkInstance->numRides; i++)
    	mapMatrix[i] = (double*)malloc(sizeof(**mapMatrix) * 2);
    parkInstance->parkMap = mapMatrix;

    /* Allocate array for nodeRoute */
    int *array = (int *)malloc(sizeof(int ) * parkInstance->numRides);
    parkInstance->nodeRoute = array; 

    /* Initialize nodeRoute */
    for(i =0; i < parkInstance->numRides; i++)
    	parkInstance->nodeRoute[i] = i;

    /* Read ride location info from stdin and store in parkMap */
	for(i = 0; i < parkInstance->numRides; i++)
		for(j = 0; j < 2; j++)
			scanf("%lf", &parkInstance->parkMap[i][j]);
	
    /* Populate nodeNetwork */
    for(i = 0; i < parkInstance->numRides; i++)
		for(j = 0; j < parkInstance->numRides; j++)
		{
			/* Store distance from entrance in matrix diagonal */
			if(i == j)
				parkInstance->nodeNetwork[i][j] = getDistance(	parkInstance->parkMap[i],
																parkInstance->startPoint);
			/* Store distance between nodes at their indexes */
			else
	  			parkInstance->nodeNetwork[i][j] = getDistance(	parkInstance->parkMap[i], 
	  															parkInstance->parkMap[j]);
		}

	/* Flag blocked paths in both directions*/
	for(i = 0; i < parkInstance->numBlockedPaths; i++)
	{
		scanf("%d", &node1 );
		scanf("%d", &node2 );
		parkInstance->nodeNetwork[node1 - 1][node2 - 1] = -1;
		parkInstance->nodeNetwork[node2 - 1][node1 - 1] = -1;
	}

	/**
	printf("\nNodeNetwork:\n");
    for(i = 0; i < parkInstance->numRides; i++)
	{
		for(j = 0; j < parkInstance->numRides; j++)
	 		printf("%7.3f ", parkInstance->nodeNetwork[i][j]);

		printf("\n");
	}	
	printf("\n\n");
	/**/

}

/* Free all memory for a ThemePark instance */
void close(struct ThemePark *parkInstance)
{
	int i;

	/* Free all memory from ThemePark 2d arrays */
	for (i = 0; i < parkInstance->numRides; i++)
	{
        free(parkInstance->nodeNetwork[i]);
        free(parkInstance->parkMap[i]);
	}

	/* Free all memory from ThemePark 1d arrays */
	free(parkInstance->nodeNetwork);
	free(parkInstance->parkMap);
	free(parkInstance->nodeRoute);

}

/* Check if the route is possible, calculates the time for the current route, */
/* and if it's the shortest, store in parkInstance->bestRouteTime */
void getRouteTime(struct ThemePark *parkInstance)
{
	int i;
	int node1, node2;
	double currentRouteTime = 0;
	int routeLength = parkInstance->numRides - 1;

	/* For all paths in route */
	for(i = 0; i < routeLength; i++)
	{
		node1 = parkInstance->nodeRoute[i];
		node2 = parkInstance->nodeRoute[i + 1];

		/* If path is blocked */
		if(parkInstance->nodeNetwork[node1][node2] < 0) 
		{
			/* Route will not work */
			currentRouteTime = DAY_LENGTH + 1;
			break;
		}
		else
		{
			/* Add time to travel path plus ride time to current route time */
			currentRouteTime += (parkInstance->nodeNetwork[node1][node2] / (double)WALK_SPEED) + (double)RIDE_TIME;
		}
	}

	/* Set nodes to first and last node in path */
	node1 = parkInstance->nodeRoute[0];
	node2 = parkInstance->nodeRoute[routeLength];

	/* Add one ride time for first ride and time to walk to it */
	currentRouteTime += RIDE_TIME + parkInstance->nodeNetwork[node1][node1]; /**
					 +  			parkInstance->nodeNetwork[node2][node2]; /**/

	/* If this is the shortest route so far */
	if(currentRouteTime < parkInstance->bestRouteTime)
		parkInstance->bestRouteTime = currentRouteTime;

}

/* Recursively create all permutations of routes, call getRouteTime on each */
/* This is a brute force method, and is only viable since the number of rides */
/* is guaranteed to be less than 11. */
void getShortestRoute(struct ThemePark *parkInstance, int startIndex, int endIndex)
{
	int i, j;
	
	/* Base Case */
	if (startIndex == endIndex)
	{
		getRouteTime(parkInstance);	
	}
	else
	{
		/* Get all permutations of possible routes */
		for(i = startIndex; i <= endIndex; i++)
		{
			swapInts(	parkInstance->nodeRoute + startIndex,
						parkInstance->nodeRoute + i);

			/* Recurse */
			getShortestRoute(parkInstance, startIndex + 1, endIndex);

			/* Backtrack */
			swapInts(	parkInstance->nodeRoute + startIndex,
						parkInstance->nodeRoute + i);
		}
	}
}

/* Returns the distance between point1 and point2 in two dimensions */
double getDistance(double point1[], double point2[])
{
	return sqrt(pow(point1[0] - point2[0], 2) + pow(point1[1] - point2[1], 2));
}

/* Swaps two integers, used in getShortestRoute while getting all permutations of routes */
void swapInts(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}