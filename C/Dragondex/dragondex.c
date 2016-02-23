 /*

 Chris Zehr
 COP 3223C- 15Fal 0R04

 Program 8
 12/4/2015
 Completed:  (4) All options implemented: adding, removing, searching, and listing dragons.
*/

/*
    Header Files
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Constants
*/
#define MAX_LENGTH 40
#define MAX_TEAM 1000

/*
    Structs
*/
struct dragon{
    char name[MAX_LENGTH];
    char color[MAX_LENGTH];
};
struct collection{
    struct dragon team[MAX_TEAM];
    int num_dragons;
};

/*
    Function Declaration
*/
void addDragon(struct collection *dragonCollection, FILE * );
void removeDragon(struct collection *dragonCollection, FILE * );
void searchDragon(struct collection *dragonCollection, FILE * );
void listDragon(struct collection *dragonCollection, FILE * );



/*
    Main
*/

int main(){

    /*
        Initialization
    */

    int num_commands;                       //Stores the number of comands in dragon.txt
    char current_command[MAX_LENGTH];       //Stores the current command string from dragon.txt
    struct collection dragonCollection;     //Stores the collection of dragons

    //Declare input file pointer and open dragon.txt
    FILE *ifp = fopen("dragon.txt", "r");

    //Read the number of commands from the file, and save in num_commands
    fscanf(ifp, "%d", &num_commands);



    /*
        Process Instructions
    */

    //Loop through each command in file
    int i;
    for(i = 0; i < num_commands; i++)
    {
        //Read next command and store in current_command
        fscanf(ifp, "%s", current_command);

        //Call appropriate function for each action
        if(strcmp(current_command, "ADD") == 0)
            addDragon(&dragonCollection, ifp);

        if(strcmp(current_command, "REMOVE") == 0)
            removeDragon(&dragonCollection, ifp);

        if(strcmp(current_command, "SEARCH") == 0)
            searchDragon(&dragonCollection, ifp);

        if(strcmp(current_command, "LIST") == 0)
            listDragon(&dragonCollection, ifp);
    };



    /*
        Shut Down
    */

    //Close file
    fclose(ifp);

return 0;

}

/*
    Function Implementation
*/
//################################################################################
//All functions take a reference to a collection struct and an input file pointer.
//################################################################################

//Adds dragon to the collection
void addDragon(struct collection *dragonCollection, FILE *ifp)
{
    //String buffer and size of collection
    char buffer[MAX_LENGTH];
    int num_drags = dragonCollection->num_dragons;

    //Read name into buffer and print
    fscanf(ifp, "%s", buffer);
    printf("%s the ", buffer);

    //Copy name to the dragon in the last position in the collection
    strcpy(dragonCollection->team[num_drags].name, buffer);

    //Read color into buffer and print
    fscanf(ifp, "%s", buffer);
    printf("%s dragon has been added to the team. \n\n", buffer);

    //Copy color to the dragon in the last position in the collection
    strcpy(dragonCollection->team[num_drags].color, buffer);

    //Increment the number of dragons in the collection
    dragonCollection->num_dragons++;

}

//Remoes dragon from collection
void removeDragon(struct collection *dragonCollection, FILE *ifp)
{
    //String buffer and size of collection
    char buffer[MAX_LENGTH];
    int num_drags = dragonCollection->num_dragons;

    //Read dragon name into buffer
    fscanf(ifp, "%s", buffer);

    //Loop through the collection of dragons
    int i;
    for(i = 0; i < num_drags; i++)
    {
        //If the name of the ith dragon in the collection matches the buffer
        if(strcmp(buffer, dragonCollection->team[i].name) == 0)
        {
            //Decrement size of collection and print
            num_drags--;
            printf("%s the %s dragon has been removed from the team. \n\n", buffer, dragonCollection->team[i].color);

            //Copy dragon in the last position (num_drags has already been decremented) to the ith position
            strcpy(dragonCollection->team[i].name, dragonCollection->team[num_drags].name);
            strcpy(dragonCollection->team[i].color, dragonCollection->team[num_drags].color);

        }
    }

}

//Searches for dragon in team
void searchDragon(struct collection *dragonCollection, FILE *ifp)
{
    //String buffer, size of collection, and flag for failure message
    char buffer[MAX_LENGTH];
    int num_drags = dragonCollection->num_dragons;
    int success = 0;

    //Read dragon name into buffer
    fscanf(ifp, "%s", buffer);

    //Loop through collection
    int i;
    for(i = 0; i < num_drags; i++)
    {
        //If the dragon's name in the ith position matches the buffer
        if(strcmp(buffer, dragonCollection->team[i].name) == 0)
        {
            //Print and flip success flag
            printf("%s the dragon is currently on the team. \n\n", buffer);
            success = 1;
        }
    }

    //If flag was not flipped after the entire collection, dragon is not in collection
    if(success == 0)
    {
        printf("%s the dragon is NOT currently on the team. \n\n", buffer);
    }
}

//List all dragons of a specified color
void listDragon(struct collection *dragonCollection, FILE *ifp)
{
    //String buffer and size of collection
    char buffer[MAX_LENGTH];
    int num_drags = dragonCollection->num_dragons;

    //Read color into string buffer and print
    fscanf(ifp, "%s", buffer);
    printf("%s dragons:\n", buffer);

    //Loop through collection of dragons
    int i;
    for(i = 0; i < num_drags; i++)
    {
        //If dragon in ith position matches, print name
        if(strcmp(buffer, dragonCollection->team[i].color) == 0)
        {
            printf("%s \n", dragonCollection->team[i].name);
        }
    }

    printf("\n");
}
