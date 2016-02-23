/* 
	Chris Zehr
	1/24/2016
	Program #1
	UCF Spring 2016 Computer Science 1  
*/

/*
	Libraries and constants
*/
#include <stdio.h>
#define SIZE 9
#define BOX 3

/*
	Function Declaration
*/
void handlePuzzleInput(int puzzle[SIZE][SIZE]);
void checkPuzzle(int puzzle[SIZE][SIZE]);

/* 
	Function Implementation
*/
void handlePuzzleInput(int puzzle[SIZE][SIZE])
{
	char line[SIZE + 1];
	int i, j;

	/* Loop through the puzzle and save data in puzzle[][] */
	for(i = 0; i < SIZE; i++)
	{
		scanf("%s", line);
		for(j = 0; j < SIZE; j++)
		{
			puzzle[i][j] = line[j] - '0';
		
		}		
	}
}

void checkPuzzle(int puzzle[SIZE][SIZE])
{
	int flag = 0;
	int i, j, k, x, y, r;

	/* Check rows and columns for duplicates */
	for (i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			for (k = j + 1; k < SIZE; k++)
			{	
				/* If a duplicate is found in row or column, flip flag */
				if(puzzle[i][j] == puzzle[i][k] )
				{
					flag = 1;
				}
				
				if (puzzle[j][i] == puzzle[k][i])
				{
					flag = 1;
				}
			}
		}
	}

	/* Check each box for duplicates */
	for (i = 0; i < BOX; i++)
		for(r = 0; r < BOX; r++)
			/* For each number in the box */
			for (j = 0; j < BOX ; j++)
	    		for (k = 0; k < BOX; k++)
    			    /* Check with every number in the box */
    			    for (x = 0; x < BOX ; x++)
    			        for (y = 0; y < BOX; y++)
    			        {	
    			        	/* Except for itself */
    			            if(j == x && k == y)
    			               continue;
    			            if(puzzle[j + i * BOX][k + r * BOX] == puzzle[x + i * BOX][y + r * BOX])
    			               flag = 1;
    				    } 
    /* Print Output */
    if(!flag)
    {
    	printf("YES\n");
    }
    else
    {
    	printf("NO\n");
    } 

}	  	
    	

/*
	Main
*/
int main(){

	int puzzleCount, inputLoop, puzzle[SIZE][SIZE];

	scanf("%d", &puzzleCount);

	/* Loop through each case. */
	for(inputLoop = 0; inputLoop < puzzleCount; inputLoop++)
	{
		/* Loop through the puzzle and save data in puzzle[][] */

		handlePuzzleInput(puzzle);	

		/* Check Puzzle for correctness */

		checkPuzzle(puzzle);
	}

	return 0;
}