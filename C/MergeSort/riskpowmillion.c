/*
 *	author: Chris Zehr
 *	3/6/2016
 *	Program #4 Risk
 *	UCF Spring 2016 Computer Science 1
 */

/*
 *	Include libraries
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *	Function Declaration
 */
int initialize(int ***armyMatrix, int *armySize);
void close(int ***armyMatrix);
void countVictories(int **armyMatrix, int armySize);
void mergeSort(int *mainArray, int size);
void merge(int *mainArray, 	
							int *rightArray, 
							int rightSize, 
							int *leftArray,
							int leftSize);

/*
 *	Main
 */
int main(){

	int **armyMatrix;
	int armySize;
	
	int numInputCases, i;
	scanf("%d", &numInputCases);

	/* Loop through each case */
	for(i = 0; i < numInputCases; i++)
	{
		/* Allocate memory and read input */
		initialize(&armyMatrix, &armySize);

		/* Merge Sort both armies */
		mergeSort(armyMatrix[0], armySize);
		mergeSort(armyMatrix[1], armySize);
		
		/* Count victories and print */
		countVictories(armyMatrix, armySize);

		/* Free memory */
		close(&armyMatrix);

	}

	return 0;
}

/*
 *	Function Implementation
 */
int initialize(int ***armyMatrix, int *armySize)
{
	/* Iterators */
	int i, j;

	/* Read size info from stdin */
	scanf("%d", armySize);

	/* Allocate space for both army Arrays */
	int **matrix = (int **)malloc(sizeof(*matrix) * 2);
    for (i = 0; i < 2; i++)
        matrix[i] = (int *)malloc(sizeof(**matrix) * (*armySize));
    *armyMatrix = matrix;

	/* Read army info from stdin */
	for(i = 0; i < 2; i++)
		for(j = 0; j < *armySize; j++)
			scanf("%d", &(*armyMatrix)[i][j]); 

}

void close(int ***armyMatrix)
{
	/* Iterator */
	int i;

	/* Free all memory from armyMatrix */
	for (i = 0; i < 2; i++)
        free((*armyMatrix)[i]);

	free(*armyMatrix); 
}

/* Sorts and merge's two un-sorted array's */
void merge(int *mainArray, int *rightArray, int rightSize, int *leftArray, int leftSize)
{
	/* Iterators */ 
	int i = 0;
	int j = 0;
	int k = 0;

	/* Sort and Merge until hitting the end of one array */
	while(i < leftSize && j < rightSize)
	{
		if(leftArray[i] < rightArray[j] )
		{
			mainArray[k] = leftArray[i];
			i++;
		}
		else
		{
			mainArray[k] = rightArray[j];
			j++;
		}

		k++;
	}

	/* Put the rest of the unfinished array into mainArray */
	while(i < leftSize)
	{
		mainArray[k] = leftArray[i];
		i++;
		k++;
	}
	while(j < rightSize)
	{
		mainArray[k] = rightArray[j];
		j++;
		k++;
	}
}

void mergeSort(int *mainArray, int size)
{
	int i;
	int partition;
	int *leftArray, *rightArray;

	/* Base Case */
	if(size < 2)
		return;

	/* Choose a partition */
	partition = size / 2;

	/* Allocate memory for partitioned array */
	leftArray = (int*)malloc(sizeof(int) * partition);
	rightArray = (int*)malloc(sizeof(int) * (size - partition) );

	/* Read data into both partitions */
	for(i = 0; i < partition; i++)
		leftArray[i] = mainArray[i];
	for(i = partition; i < size; i++)
		rightArray[i - partition] = mainArray[i];

	/* Recursive Step, sort both arrays */
	mergeSort(rightArray, size - partition);
	mergeSort(leftArray, partition);

	/* Merge sorted sub-arrays */
	merge(mainArray, rightArray, size - partition, leftArray, partition);

	/* Deallocate memory */
	free(rightArray);
	free(leftArray);
}

void countVictories(int **armyMatrix, int armySize)
{
	int i;
	int j = armySize - 1;
	int victoryCount = 0;

	/* Loop through Army arrays */
	for(i = armySize - 1; i >= 0; i--)
	{
		/* If the attacker won */
		if(armyMatrix[0][i] > armyMatrix[1][j])
		{
			/* Do nothing */	
		}
		else
		{
			/* Defender won, move to next defender (strongest defender left) */
			j--;
			victoryCount++;
		}
	}

	printf("%d\n", victoryCount);
}