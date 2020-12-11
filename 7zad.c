#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Radna verzija s laba, nije gotovo

struct node;
typedef struct node* position;
struct node{
	int element;
	position next;
};

int fileSize(FILE*);
char* createExpression(FILE*);
int evaluateExpression(char*);
int push(position);
int pop(position);

int main()
{
	FILE *fp;
	char nameOfFile[20];
	int sizeOfFileInBytes, result;
	char* expression;

	printf("Upisite ime datoteke\n");
	scanf(" %s", nameOfFile);
	fp = fopen(nameOfFile, "r");
	if(fp == NULL){
		printf("Datoteka se ne moze otvoriti!\n");
		return -1;
	}

	sizeOfFileInBytes = fileSize(fp);
	expression = createExpression(fp);
	result = evaluateExpression(expression);

	printf("Postfix izraz je: %s", expression);
	printf("Rezultat postfix izraza je: %d", result);

	return 0;
}

int fileSize(FILE *fp){
	int sizeOfBuffer = 0;

	fseek(fp, 0, SEEK_END);
	sizeOfBuffer = ftell(fp);
	rewind(fp);

	printf("Velicina buffera je: %d", sizeOfBuffer);
	return sizeOfBuffer;
}

char* createExpression(FILE *fp, int sizeOfFile){
	char* expression;

	expression = (char*)calloc(sizeOfFile, sizeof(char));
	fread(expression, sizeOfFile, 1, fp);
	return expression;
}

int evaluateExpression(char* expression){
	
}

int push(position p, char* ){
	position temp;

	temp = (position)malloc(sizeof(struct node));

}
