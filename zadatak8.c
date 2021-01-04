#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 256

//NIJE JOS GOTOVO

struct tree;
typedef struct tree* position;
struct tree {
	char dir[MAXCHAR];
	position sibling;
	position child;
	position parent;
};

char* enterNewCommand(); //rjeseno
int printDirectoryPath();
int makeDefaultDirectories(); //rjeseno
int makeChildDirectory(position, char*); //rjeseno valjda
int makeSiblingDirectory(position, char*);
position changeDirectory(position, char*); //rjeseno
position previousDirectory(position); //rjeseno
int printContentsOfCurrentDirectory(position); //rjeseno
int printTree(position);
void deleteAll(); //rjeseno
void returnToRoot(position);
int processAndSelectCommand(position, char*);

int main()
{
	char username[MAXCHAR], input[MAXCHAR];
	struct tree root;
	int loop = 1;

	printf("Microsoft Windows [Version 6.1.7601]\nCopyright <c> 2009 Microsoft Corporation. All rights reserved.\n\n");
	printf("Enter your username:\n");
	scanf(" %s", username);
	makeDefaultDirectories(&root, username);
	printDirectoryPath();
	while (loop) {
		strcpy(input, enterNewCommand());
		processAndSelectCommand(&root, input);
	}
	return 0;
}

int makeChildDirectory(position p, char* dirName) { //radi novi poddirektorij u direktoriju gdje se trenutno nalazimo
	position temp;

	temp = (position)malloc(sizeof(struct tree));
	strcpy(temp->dir, dirName);
	p->child = temp;
	temp->parent = p;
	temp->sibling = NULL;
	temp->child = NULL;

	return 0;
}

int makeSiblingDirectory(position p, char* dirName) {
	position temp;

	temp = (position)malloc(sizeof(struct tree));
	strcpy(temp->dir, dirName);
	p->sibling = temp;
	temp->sibling = NULL;
	temp->child = NULL;
	temp->parent = NULL;
	return 0;
}

int makeDefaultDirectories(position p, char* username) {
	char root[MAXCHAR] = "C:";
	char users[MAXCHAR] = "Users";
	
	makeChildDirectory(p, root);
	p = p->child;
	makeChildDirectory(p, users);
	p = p->child;
	makeChildDirectory(p, username);
	return 0;
}

int printDirectoryPath(position p) {
	if (p->parent == NULL) {
		printf("%s/", p->dir);
	}
	else {
		
	}
}

char* enterNewCommand() { //upis nove operacije
	char input[MAXCHAR];

	printf("Enter new command:\n");
	scanf(" %s", input);

	return input;
}

int processAndSelectCommand(position p, char* input) { //prebacuje izraz u buffer, odvaja operaciju i direktorij, bira odgovarajucu funkciju i argumente
	char operation[MAXCHAR];
	char argument[MAXCHAR];
	char buffer[MAXCHAR];

	strcpy(buffer, input);
	sscanf(buffer, "%s %s", &operation, &argument);

	if (strcmp(operation, "md") == 0) {
		makeChildDirectory(p, argument);
	}
	else if (strcmp(operation, "root") == 0) {
		returnToRoot();
	}
	else if (strcmp(operation, "cd") == 0) {
		changeDirectory(p, argument);
		printDirectoryPath(p);
	}
	else if (strcmp(operation, "cd..") == 0) {
		previousDirectory(p);
		printDirectoryPath(p);
	}
	else if (strcmp(operation, "dir") == 0) {
		printContentsOfCurrentDirectory(p);
	}
	else if (strcmp(operation, "exit") == 0) {
		deleteAll(p);
		return 0;
	}
	return 1;
}

position previousDirectory(position p) { //naredba cd.. vraca se jedan direktorij iznad tj. parent direktorij ako postoji, inace ispisuje da ne postoji
	if (p->parent != NULL) {
		p = p->parent;
		return p;
	}
	else {
		printf("Chosen directory is root, there is no parent directory");
		return NULL;
	}
}

int printContentsOfCurrentDirectory(position p) { //ispisuje sadrzaj direktorija u kojem se trenutno nalazimo
	if (p->child == NULL) {
		printf("Selected directory is empty!");
	}
	else {
		p = p->child;
		while (p->sibling->sibling != NULL) {
			printf("%s\t", p->dir);
			p = p->sibling;
		}
	}
	return 0;
}

int printTree(position p) { //rekurzivno ispisuje sadrzaje svih poddirektorija roota
	printf("%s\n", p->dir);
	p = p->child;
	while (p != NULL) {
		printf("%s\t", p);
		p = p->sibling;
	}
}

position changeDirectory(position p, char* dirName) {
	p = p->child;
	while(strcmp(p->sibling->dir, dirName) != 0){
		p = p->sibling;
	}
	return p;
}

void deleteAll(position p) { ////poziva se prilikom izlaza iz programa, rekurzivno brise cijelu vezanu listu(stablo)
	if (p == NULL)
		return;
	remove(p->sibling);
	remove(p->child);
	free(p);
}

