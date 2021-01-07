/*Napisati program koji pomoću vezanih listi (stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod-direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij. Točnije program treba preko menija simulirati
korištenje DOS naredbi: 1- "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.
md radi novi child direktorij
cd dir ulazi u poddirektorij
cd.. se vraca u parent direktorij
dir ispisuje sadrzaj direktorija
exit brise stablo i izlazi
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 255

struct tree;
typedef struct tree* position;
struct tree {
	char dir[MAXCHAR];
	position sibling;
	position child;
	position parent;
};

struct stack;
typedef struct stack* nav;
struct stack {
	position directory;
	nav nextStack;
};

position processAndSelectCommand(position, char*, nav); //rjeseno
position changeDirectory(position, char*); //rjeseno
position previousDirectory(position); //rjeseno
int printContentsOfCurrentDirectory(position); //rjeseno
position makeNewDirectory(position p, char* dirName); //rjeseno
void deleteAll(position); //rjeseno
//nav stackPush(nav);
//nav stackPop(nav);
//int printStack(nav);

int main()
{
	char username[MAXCHAR] = { 0 };
	char input[MAXCHAR] = { 0 };
	struct tree root;
	position currentDirectory;
	struct stack head;
	int loop = 1;

	root.child = NULL;
	root.sibling = NULL;
	root.parent = NULL;

	head.nextStack = NULL;
	head.directory = NULL;

	currentDirectory = &root;

	printf("Microsoft Windows [Version 6.1.7601]\nCopyright <c> 2009 Microsoft Corporation. All rights reserved.\n\n");
	printf("Enter your username:\n");
	gets(username);
	strcpy(root.dir, username);

	while (loop) {
		printf("%s/", currentDirectory->dir);
		gets(input);
		//printf("provjera upisa u input: %s\n", input);
		currentDirectory = processAndSelectCommand(currentDirectory, input, &head);
		//printStack(head.nextStack);
		if (currentDirectory == NULL) {
			loop = 0;
		}
	}
	return 0;
}

position processAndSelectCommand(position p, char* input, nav stack) {
	char operation[MAXCHAR] = { 0 };
	char argument[MAXCHAR] = { 0 };
	char buffer[MAXCHAR] = { 0 };
	char* token;
	position current;

	strcpy(buffer, input);
	token = strtok(buffer, " ");
	while (token != NULL) {
		if (strcmp(token, "md") == 0 || strcmp(token, "cd") == 0 || strcmp(token, "cd..") == 0 || strcmp(token, "dir") == 0 || strcmp(token, "exit") == 0) {
			strcpy(operation, token);
			token = strtok(NULL, " ");
		}
		else {
			strcpy(argument, token);
			token = strtok(NULL, " ");
		}
	}
	
	if (strcmp(operation, "md") == 0) {
		current = makeNewDirectory(p, argument);
		//stackPush(stack, current);
	}
	else if (strcmp(operation, "cd") == 0) {
		current = changeDirectory(p, argument);
	}
	else if (strcmp(operation, "cd..") == 0) {
		current = previousDirectory(p);
	}
	else if (strcmp(operation, "dir") == 0) {
		printContentsOfCurrentDirectory(p);
		current = p;
	}
	else if (strcmp(operation, "exit") == 0) {
		deleteAll(p->child);
		current = NULL;
	}
	return current;
}

position previousDirectory(position p) {
	/*while (p->prevSibling != NULL) {
		p = p->prevSibling;
	}*/
	if (p->parent != NULL) {
		/*while (p->parent != NULL) {
			p = p->prevSibling;
		}*/
		p = p->parent;
		return p;
	}
	else {
		printf("Chosen directory is root, there is no parent directory\n");
		return p;
	}
}

int printContentsOfCurrentDirectory(position p) { //ispisuje sadrzaj direktorija u kojem se trenutno nalazimo
	if (p->child == NULL) {
		printf("Selected directory is empty!\n");
	}
	else {
		printf("List of contents:\n");
		p = p->child;
		printf("%s", p->dir);
		while (p->sibling != NULL) {
			printf("%s\t", p->dir);
			p = p->sibling;
		}
	}
	printf("\n");
	return 0;
}

position makeNewDirectory(position p, char* dirName) { //radi novi direktorij, u ovisnosti je li prvi ili vec postoje drugi poddirektoriji
	position temp, parentDir;
	
	parentDir = p;
	temp = (position)malloc(sizeof(struct tree));
	strcpy(temp->dir, dirName);
	temp->sibling = NULL;
	temp->child = NULL;

	if (p->child == NULL) {
		p->child = temp;
		temp->parent = p;
	}
	else if (p->child != NULL) {
		p = p->child;
		while (p->sibling != NULL) {
			p = p->sibling;
		}
		p->sibling = temp;
		temp->parent = parentDir;
	}
	return temp;
}

/*nav stackPush(nav p, position d) {
	nav temp;

	temp = (nav)malloc(sizeof(struct stack));
	temp->nextStack = p->nextStack;
	p->nextStack = temp;
	temp->directory = d;

	return temp;
}*/

/*nav stackPop(nav p) {
	nav temp;

	temp = p->nextStack;
	p->nextStack = temp->nextStack;
	free(temp);

	return temp;
}*/

/*int printStack(nav p) {
	while (p->nextStack != NULL) {
		printf("%s/", p->directory->dir);
	}
	return 0;
}*/

void deleteAll(position p) {
	if (p == NULL)
		return;
	deleteAll(p->sibling);
	deleteAll(p->child);
	printf("Removed %s\n", p->dir);
	free(p);
}

position changeDirectory(position p, char* dirName) {
	p = p->child;
	while (strcmp(p->dir, dirName) != 0) {
		p = p->sibling;
	}
	return p;
}
