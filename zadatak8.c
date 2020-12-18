#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 256

struct tree;
typedef struct tree* position;
struct tree{
	char dir[MAXCHAR];
	position sibling;
	position child;
};

struct stack;
typedef struct stack navStack;
typedef struct stack* stackPos
struct stack{
	char dir[MAXCHAR];
	stackPos next;
};

int createRoot(char*);
char* navStackPush();
position navStackPop();
void deleteAll(position);
int printNodes(position);
int makeDirectory(position);
position navigateToPrevious(position);


int main()
{
	struct tree root;
	char operation[MAXCHAR];
	int loop = 1;

	printf("Izaberi operaciju:\n");
	scanf(" %s", operation);
	while(loop){
		if(strcmp(operation, "md") == 0){
			
		}
	}

	return 0;
}

int makeDirectory(position p){
	position temp;
	char nameOfDirectory[MAXCHAR];

	temp = (position)malloc(sizeof(struct tree));
	printf("Ime novog direktorija?\n");
	scanf(" %s", nameOfDirectory);
	temp->dir = nameOfDirectory;
	p->child = temp;
	temp->sibling = NULL;
	temp->child = NULL;
}

void deleteAll(position p){
	if(p == NULL)
		return;
	remove(p->sibling);
	remove(p->child);
	free(p);
}

char* navStackPush(position p){
	
}

position navStackPop(position p){
	position temp;

	if (p == NULL) {
		printf("Stog je prazan!\n");
		return NULL;
	}
	else {
		
	}
	return temp;
}
