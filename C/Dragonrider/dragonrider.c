 /*

 Chris Zehr
 COP 3223C- 15Fal 0R04

 Program 6
 12/12/2015

*/


/*
    Headers, Definitions, and Structs
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


//Number of items in game
#define NUM_ITEMS 6

//Item enumeration
enum Item {
	BLANKET,
	SADDLE,
	JACKET,
	HARNESS,
	GOGGLES,
	HELMET
};

enum bool{
    FALSE,
    TRUE
};

//Item Strings ONLY FOR PRINTING
const char * itemStrings[] = {
	"Blanket",
	"Saddle",
	"Jacket",
	"Harness",
	"Goggles",
	"Helmet"
};

//Struct that stores game state
struct dragonGame {

	int isRunning;
	int dragonRiders[6][6];
	int numRiders;
	int winner;
};


/*
    Function Declaration
*/
void init(struct dragonGame * myDragonGame);
void update(struct dragonGame * myDragonGame);
void close(struct dragonGame * myDragonGame);

void takeTurn(int dragonRiderNumber, int dragonRider[NUM_ITEMS]);
int processTurn(int dragonRiderNumber, int dragonRider[NUM_ITEMS]);


/*
    Main
*/

int main(){

	struct dragonGame DRAGON_SHED_RAID;

	/*
		Initialize game
	*/
	init(&DRAGON_SHED_RAID);


	/*
		Run Game
	*/
	update(&DRAGON_SHED_RAID);


	/*
		Shut Down
	*/
	close(&DRAGON_SHED_RAID);


return 0;
}


/*
    Function Implementation
*/

// Pre-condition: myDragonGame is a pointer to a dragonGame struct that stores
// the game state.
// Post-condition: Random number generator is seeded, myDragonGame.isRunning
// is set to 1, number of players is asked for and stored in numRiders, and
// dragonRiders array is initialized to zero.
void init(struct dragonGame * myDragonGame)
{
	//Seed random number generator
	srand((unsigned) time(NULL));

	//Game is now running
	myDragonGame->isRunning = TRUE;

	//Get number of players from user
	while(TRUE)
	{
		//Prompt user for number of players
		printf("How many dragonriders are raiding the equipment shed? (1-6)\n");

		//Save number of players in numRiders
		scanf("%d", &myDragonGame->numRiders);

		if(myDragonGame->numRiders > 6 || myDragonGame->numRiders < 1)
		{
			printf("Please enter an integer between 1 and 6!\n");
		}
		else
			break;
	}

	//Initialize dragonRiders array to all zero
	int i;
	int j;
	for(i = 0; i < myDragonGame->numRiders; i++)
	{
		for(j = 0; j < NUM_ITEMS; j++)
		{
			myDragonGame->dragonRiders[i][j] = 0;
		}
	}
}

// Pre-condition: init() has been run on the struct being passed in
// Post-condition: Game is no longer running, and the winner has been stored
// in myDragonGame->winner.
void update(struct dragonGame * myDragonGame)
{
	//Main game loop
	int i, itemCount, response;
	while(myDragonGame->isRunning)
	{
		//Cycle through each player
		for(i = 0; i < myDragonGame->numRiders; i++)
		{
			while(TRUE)
			{
				//Prompt user to take their turn
				printf("Rider %d, it is your turn. Enter '0' to look for an item.\n", i+1);

				scanf("%d", &response);

				if (response == 0)
					break;
			}

			//Get item, or get caught
			takeTurn(i, myDragonGame->dragonRiders[i]);

			//If this rider has 6 items
			if(processTurn(i, myDragonGame->dragonRiders[i]) == NUM_ITEMS)
			{
				//We have a winner!
				myDragonGame->winner = i;
				myDragonGame->isRunning = FALSE;
				break;
			}
		}
	}
}

// Pre-condition: update() has been run on the struct being passed in.
// Post-condition: Winner data has been printed, program free to close.
void close(struct dragonGame * myDragonGame)
{
	//Print winner message
	printf("Congratulations Rider %d, you are the first dragon rider!\n\n", myDragonGame->winner + 1);

	//Print end game state
	int i;
	int j;
	printf("Dragonrider Array: \n\n");
	for(i = 0; i < myDragonGame->numRiders; i++)
	{
		for(j = 0; j < NUM_ITEMS; j++)
		{
			printf(" %d ", myDragonGame->dragonRiders[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
}

// Pre-condition: Takes an array that represents the player's inventory and
// an integer that tracks the current player.
// Post-condition: Inventory is updated and ready to be processed.
void takeTurn(int dragonRiderNumber, int dragonRider[NUM_ITEMS])
{
	int sumPlayerItems;
	int response;
	int i;

	//Get an integer between 0 and NUM_ITEMS
	int itemNum = rand() % (NUM_ITEMS + 1);

	//If the player was caught
	if(itemNum == NUM_ITEMS)
	{
		printf("You've been caught!\n");
		sumPlayerItems = 0;
		//Loop through player inventory
		for(i = 0; i < NUM_ITEMS; i++)
		{
			//Count how many items they have
			sumPlayerItems += dragonRider[i];

		}

		//If they have nothing
		if(sumPlayerItems == 0)
			printf("There is no equipment for you to lose. Lucky you, sort of");

		//They have something
		else
		{
			//Prompt user for input
			printf("Which piece would you like to lose?\n\n");
			//Loop through player inventory
			for(i = 0; i < NUM_ITEMS; i++)
			{

				//If they have the item, print
				if(dragonRider[i])
				{

					//If they have a saddle, don't print blanket
					if(i == BLANKET && dragonRider[SADDLE])
					{
						//Do nothing
					}

					//If they have a harness, don't print jacket
					else if(i == JACKET && dragonRider[HARNESS])
					{
						//Do nothing
					}

					else
					{
						printf("%d. %s\n", i+1, itemStrings[i]);
					}
				}
			}

			scanf("%d", &response);     //Pressing 0 here makes everything break.

			//Remove item from inventory
			dragonRider[response - 1] = 0;

		}

	}
	//The player was not caught
	else
	{
		printf("Rider %d, you found a %s\n", dragonRiderNumber+1, itemStrings[itemNum]);

		//If they already have this item
		if(dragonRider[itemNum])
			printf("You already have that item\n");

		//If new item is a saddle, and they don't have a blanket
		else if(itemNum == SADDLE && !dragonRider[BLANKET])
			printf("Sorry, you can't obtain %s (You need a Blanket!)\n", itemStrings[itemNum]);

		//If the new item is a flight harness, and they don't have a jacket.
		else if(itemNum == HARNESS && !dragonRider[JACKET])
			printf("Sorry, you can't obtain %s (You need a Jacket!)\n", itemStrings[itemNum]);

		//They're able to add this item to their inventory
		else
		{
			printf("Congrats, you now have a %s\n", itemStrings[itemNum]);
			dragonRider[itemNum] = 1;
		}
	}
}

// Pre-condition: dragonRider is the inventory of a player, should be
// called immediately after a player takes their turn.
// Post-condition: Rider inventory is printed, returns number of items
// in the player's inventory.
int processTurn(int dragonRiderNumber, int dragonRider[NUM_ITEMS])
{
	int i, itemCount;

	itemCount = 0;
	printf("Rider %d, here is what you currently have:\n\n", dragonRiderNumber+1);
	for(i = 0; i < NUM_ITEMS; i++)
	{
		//Count how many items this rider has
		itemCount += dragonRider[i];

		//Print Inventory
		if(dragonRider[i] == 1)
		{
			printf("%d. %s\n", i+1, itemStrings[i]);
		}

	}
	printf("\n");

	return itemCount;
}
