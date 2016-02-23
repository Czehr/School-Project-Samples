/*
 *	author: Chris Zehr
 *	2/21/2016
 *	Program #3
 *	UCF Spring 2016 Computer Science 1
 */

/*
 *	Include libraries
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *	Structs
 */
struct MastermindInstance
{

	int numColors, rows, cols, totalSolutions;
	int **gameData;
};

/*
 *	Function Declaration
 */
void initialize(struct MastermindInstance* gameState);
void close(struct MastermindInstance* gameState);
void countPossibleSolutions(int n, struct MastermindInstance *gameState);
void checkGuess(int *guess, int *solution, int *response, int size);

/*
 *	Main
 */
int main(){

	int numInputCases, i;
	struct MastermindInstance gameState;

	scanf("%d", &numInputCases);

	/* Loop through each case */
	for(i = 0; i < numInputCases; i++)
	{
		/* Allocate memory and read input */
		initialize(&gameState);

		/* For every possible solution, check to see if it matches input */
		countPossibleSolutions(gameState.cols, &gameState);

		/* Print results */
		printf("%d\n", gameState.totalSolutions);

		/* Free memory */
		close(&gameState);
	}

	return 0;
}

/*
 *	Function Implementation
 */
void initialize(struct MastermindInstance *gameState)
{
	/* Iterators */
	int i, j;

	gameState->totalSolutions = 0;

	/* Read gameState info from stdin */
	scanf("%d", &gameState->cols);
	scanf("%d", &gameState->numColors);
	scanf("%d", &gameState->rows);

	/* Allocate space for gameState->gameData (including black/white pegs and bottom row for guesses) */
	int **array = (int **)malloc(sizeof(*array) * gameState->rows + 1);
    for (i = 0; i < gameState->rows + 1; i++)
        array[i] = (int *)malloc(sizeof(**array) * gameState->cols + 2);
    gameState->gameData = array;

	/* Read gameState->gameData info from stdin */
	for(i = 0; i < gameState->rows; i++)
		for(j = 0; j < gameState->cols + 2; j++)
			scanf("%d", &gameState->gameData[i][j]);

}

void close(struct MastermindInstance *gameState)
{
	int i;

	/* Free all memory from gameState */
	for (i = 0; i < gameState->rows + 1; i++)
        free((*gameState).gameData[i]);

	free((*gameState).gameData);
}

/* Stores number of white and black pegs as an array */
void checkGuess(int * guess, int * solution, int * response, int size)
{
	/* Iterators */
	int i, j;

	int numBlackPegs = 0;
	int numWhitePegs = 0;
	int flag[size];

	for(i = 0; i < size; i++)
		flag[i] = 0;

	/* Count number of black pegs */
	for(i = 0; i < size; i++)
	{
		if(guess[i] == solution[i])
		{
			numBlackPegs++;
			flag[i] = 1;
		}
	}

	/* Count number of white pegs */
	for(i = 0; i < size; i++)
	{
		if(guess[i] != solution[i])
			for(j = 0; j < size; j++)
				if(j != i && guess[i] == solution[j] && !flag[j])
				{
					numWhitePegs++;
					flag[j]=1;
					break;
				}
	}

	/* Store answer in response */
	response[0] = numBlackPegs;
	response[1] = numWhitePegs;

	return;
}

void countPossibleSolutions(int n, struct MastermindInstance *gameState)
{
	int i, j;
	int rows = gameState->rows;
	int cols = gameState->cols;
	int response[2];
	int flag = 1;

	/* Base case, we have a full potential solution */
	if(n == 0)
	{

		for(i = 0; i < rows; i++)
		{
			/* Get answer for our potential solution */
			checkGuess((*gameState).gameData[i], (*gameState).gameData[rows], response, cols);

			/* Check our solution's response against actual response */
			if( (*gameState).gameData[i][cols] != response[0] )
				flag = 0;

			if( (*gameState).gameData[i][cols + 1] != response[1] )
				flag = 0;
		}

		/* Update total solutions if this is a possible solution */
		if (flag)
			gameState->totalSolutions++;

		return;
	}

	/* Update our potential solution, every color in every slot */
	for(i = 0; i < gameState->numColors; i++)
	{
		gameState->gameData[rows][n - 1] = i;

		/* Recurse into every previous slot */
		countPossibleSolutions(n - 1, gameState);
	}
}
