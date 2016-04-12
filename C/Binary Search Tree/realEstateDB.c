/*
 *	author: Chris Zehr
 *	4/10/2016
 *	Program #6 Binary Search Tree
 *	UCF Spring 2016 Computer Science 1
 */

#define ADD_LENGTH 30


/*
 *	Include libraries
 */
#include <stdio.h>
#include <stdlib.h>

/*
 *	Structs
 */

typedef struct Listing
{

	int listingID;
	char agent[12];		/* No Spaces */
	int price;
	int size;			/* Square Feet */
	int numBeds;
	double numBaths;
	int yearBuilt;
	char address[ADD_LENGTH];
} Listing;

typedef struct Node
{
	Listing data;
	struct Node* left;
	struct Node* right;
} Node;

/*
 *	Function Declaration
 */
Node* createNode(Listing data);
Node* insertNode(Node *root, Listing data);
Node* deleteNode(Node *root, int listingID);
void searchID(Node *root, int listingID);
void searchPrice(Node *node, int price);
void searchAgent(Node *node, char* agent);
void displayListings(Node* node);

void printListing(Listing listing);
void printHeader();

/*
 *	Main
 */
int main(){

	
	int numInputCases, i;
	scanf("%d", &numInputCases);

	Listing currentListing;
	Node *root = NULL;

	/* Loop through each case */
	for(i = 0; i < numInputCases; i++)
	{
		scanf("%d", &currentListing.listingID);
		scanf("%s", currentListing.agent);
		scanf("%d", &currentListing.price);
		scanf("%d", &currentListing.size);
		scanf("%d", &currentListing.numBeds);
		scanf("%lf", &currentListing.numBaths);
		scanf("%d", &currentListing.yearBuilt);
		scanf("%[^\n]", currentListing.address);

		/* Add to DB */
		root = insertNode(root, currentListing);
	}

	printHeader();
	displayListings(root);
	printf("\n");

	int numInputCommands, command, listingID, price;
	char agent[12];
	scanf("%d", &numInputCommands);

	/* Loop through each command */
	for(i = 0; i < numInputCommands; i++)
	{
		scanf("%d", &command);

		switch(command)
		{
			/* Add listing to DB */
			case 1:
				scanf("%d", &currentListing.listingID);
				scanf("%s", currentListing.agent);
				scanf("%d", &currentListing.price);
				scanf("%d", &currentListing.size);
				scanf("%d", &currentListing.numBeds);
				scanf("%lf", &currentListing.numBaths);
				scanf("%d", &currentListing.yearBuilt);
				scanf("%[^\n]", currentListing.address);

				root = insertNode(root, currentListing);

				printf("Listing %d has been added to the database\n\n", currentListing.listingID);

				break;

			/* Delete listing */
			case 2:
				scanf("%d", &listingID);
				root = deleteNode(root, listingID);

				printf("Listing %d has been deleted from the database\n\n", listingID);

				break;

			/* Search by ID */
			case 3:
				scanf("%d", &listingID);
				searchID(root, listingID);
				break;

			/* Search by Price */	
			case 4:
				scanf("%d", &price);
				printHeader();
				searchPrice(root, price);
				printf("\n");
				break;

			/* Search by Agent */	
			case 5:
				scanf("%s", agent);
				printHeader();
				searchAgent(root, agent);
				printf("\n");
				break;

			/* Print all listings */	
			case 6:
				printHeader();
				displayListings(root);
				break;

				
			default:
				printf("Invalid command\n");
		}
	}

	return 0;
}

/*
 *	Function Implementation
 */
Node* createNode(Listing data)
{
	/* Allocate memory for new node */
	Node *newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL)
	{
		printf("Out of memory when calling createNode()\n");
		exit(1);
	}

	/* Set struct member variables */
	newNode->data= data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

Node* insertNode(Node *root, Listing data)
{
	/* If the tree is empty */
	if(root == NULL)
	{
		root = createNode(data);
	}
	else
	{
		int flag = 0;
		int result = 0;
		Node* currentNode = root;
		Node* prevNode = NULL;

		/* Find position in tree */
		while(currentNode != NULL)
		{
			/* Compare the listing ID of both Listings */
			result = data.listingID - currentNode->data.listingID;
			prevNode = currentNode;

			/* Move left or right depending on listing ID's */
			if(result < 0)
			{
				flag = 1;
				currentNode = currentNode->left;
			}
			else if(result > 0)
			{
				flag = 0;
				currentNode = currentNode->right;
			}
		}

		/* Create the node and put in tree */
		if(flag)
			prevNode->left = createNode(data);
		else
			prevNode->right = createNode(data);
	}

	return root;
}

void displayListings(Node* node)
{
	/* Base Case */
	if(node == NULL)
		return;

	/* Recurse through rest of tree in order */
	displayListings(node->left);

	/* Print Node Data */
	printListing(node->data);

	displayListings(node->right);


}

void printListing(Listing listing)
{
	printf("%d  %-12s  %d     %d  %d   %.1lf  %d  %s\n", 
			listing.listingID, 
			listing.agent, 
			listing.price/1000,
			listing.size,
			listing.numBeds,
			listing.numBaths,
			listing.yearBuilt,
			listing.address);
}

void printHeader()
{
	printf("LID  Agent       Price $K  size  Bd  Bth  Yr     Address\n");
	printf("-------------------------------------------------------------------------\n");
}

Node* deleteNode(Node* root, int listingID)
{
	/* Check if root is null */
	if(root == NULL)
		return NULL;

	Node *currentNode;
	int result = listingID - root->data.listingID;

	/* Recurse into subtrees */
	if(result < 0)
		root->left = deleteNode(root->left, listingID);
	else if(result > 0)
		root->right = deleteNode(root->right, listingID);
	/* Else handle children */
	else
	{
		/* Handle left child */
		if(root->left == NULL)
		{
			currentNode = root->right;
			free(root);
			root = currentNode;
		}
		/* Handle right child */
		else if(root->right == NULL)
		{
			currentNode = root->left;
			free(root);
			root = currentNode;
		}
		/* Handle both children */
		else
		{
			currentNode = root->right;
			Node *parent = NULL;

			while(currentNode->left != NULL)
			{
				parent = currentNode;
				currentNode = currentNode->left;
			}

			root->data = currentNode->data;
			if(parent != NULL)
				parent->left = deleteNode(parent->left, parent->left->data.listingID);
			else
				root->right = deleteNode(root->right, root->right->data.listingID);
		}
	} 
	
	return root;
}

void searchID(Node *root, int listingID)
{
	int result;
	int flag = 0;
	Node* currentNode = root;

	while(currentNode != NULL)
	{
		result = listingID - currentNode->data.listingID;
		if(result < 0)
			currentNode = currentNode->left;
		else if(result > 0)
			currentNode = currentNode->right;
		else
		{
			flag = 1;
			break;
		}
	}

	if(!flag)
		printf("Listing %d does not exist in the database\n\n", listingID);
	else
	{
		printHeader();
		printListing(currentNode->data);
	}
}

void searchPrice(Node* node, int price)
{
	/* Base Case */
	if(node == NULL)
		return;
	
	/* Recurse through rest of tree */
	searchPrice(node->left, price);

	/* Print Node Data */
	if(node->data.price <= price)
		printListing(node->data);

	searchPrice(node->right, price);
}

void searchAgent(Node *node, char* agent)
{
	/* Base Case */
	if(node == NULL)
		return;

	int result = strcmp(agent, node->data.agent);
	

	/* Recurse through rest of tree */
	searchAgent(node->left, agent);

	/* Print Node Data */
	if(result == 0)
		printListing(node->data);

	searchAgent(node->right, agent);
}