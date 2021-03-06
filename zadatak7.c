#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct node;
typedef struct node* position;
struct node {
	int element;
	position next;
};

int push(position, int);
position pop(position);
int printNodes(position);
int fileSize(FILE*);
char* createExpression(FILE*, int);
int evaluateExpression(position, char*);
int calculateExpression(position, char);

int main()
{
	FILE* fp;
	//char nameOfFile[20];
	int sizeOfFileInBytes, result;
	char* expression;
	struct node head;
	int sizeOfArray;

	head.next = NULL;

	//printf("Upisite ime datoteke\n");
	//scanf(" %s", nameOfFile);
	fp = fopen("datoteka.txt", "r");
	if (fp == NULL) {
		printf("Datoteka se ne moze otvoriti!\n");
		return -1;
	}

	sizeOfFileInBytes = fileSize(fp);
	expression = createExpression(fp, sizeOfFileInBytes);
	printf("Postfix izraz je: %s\n", expression);
	evaluateExpression(&head, expression);
	printNodes(head.next);

	return 0;
}

int push(position p, int num) {
	position temp;

	if (p == NULL) {
		printf("Greska!\n");
		return -1;
	}

	temp = (position)malloc(sizeof(struct node));
	temp->element = num;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

position pop(position p) {
	position temp;

	if (p == NULL) {
		printf("Stack is empty!\n");
		return -1;
	}
	else {
		temp = p->next;
		p->next = temp->next;
		printf("Element %d je maknut sa stacka!\n", temp->element);
		free(temp);
	}
	return temp;
}

int printNodes(position p) {
	if (p == NULL) {
		printf("Stack je prazan!\n");
		return -1;
	}
	else {
		printf("Rezultat postfix izraza je: ");
		while (p != NULL) {
			printf("%d\n", p->element);
			p = p->next;
		}
	}
	return 0;
}

int fileSize(FILE* fp) {
	int sizeOfBuffer = 0;

	fseek(fp, 0, SEEK_END);
	sizeOfBuffer = ftell(fp) + 1;
	rewind(fp);
	printf("Velicina buffera u byteovima: %d\n", sizeOfBuffer);
	return sizeOfBuffer;
}

char* createExpression(FILE* fp, int sizeOfFile) {
	char* expression;

	expression = (char*)calloc(sizeOfFile, sizeof(char));
	fread(expression, sizeOfFile, 1, fp);
	return expression;
}

int evaluateExpression(position p, char* expression) {
	char* current;

	current = strtok(expression, " ");
	while (current != NULL) {
		if (isdigit(*current)) {
			printf("%c je stavljen na stack!\n", *current);
			push(p, atoi(current));
		}
		else {
			printf("%c je operator\n", *current);
			calculateExpression(p, *current);
		}
		current = strtok(NULL, " ");
	}
}

int calculateExpression(position p, char operation) {
	int result, var1, var2;
	var1 = p->next->element;
	var2 = p->next->next->element;

	switch (operation) {
	case'+':
		result = var1 + var2;
		printf("Rezultat operacije %d + %d je %d\n", var1, var2, result);
		break;
	case '-':
		result = var1 - var2;
		printf("Rezultat operacije %d - %d je %d\n", var1, var2, result);
		break;
	case '*':
		result = var1 * var2;
		printf("Rezultat operacije %d * %d je %d\n", var1, var2, result);
		break;
	case '/':
		result = var1 / var2;
		printf("Rezultat operacije %d / %d je %d\n", var1, var2, result);
		break;
	}
	pop(p);
	pop(p);
	printf("Rezultat %d je stavljen na stack!\n", result);
	push(p, result);
	return result;
}
