#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 256

//NIJE GOTOVO

struct tree;
typedef struct tree* treePos;
struct tree{
	char data[MAXCHAR];
	treePos left;
	treePos right;
};

struct stack;
typedef struct stack* stackPos;
struct stack{
	treePos tree;
	stackPos next;
};

int stackPush(stackPos); //rjeseno
stackPos stackPop(stackPos); //rjeseno
int treePush(treePos);
int fileSize(FILE*); //rjeseno
char* createExpression(FILE*, int); //rjeseno
int isOperator(char*); //rjeseno
int evaluateExpression(stackPos, char*);
void printInOrder(treePos); //rjeseno

int main(){
	FILE* fp;
	int fileSizeCounter = 0;
	char buffer[MAXCHAR] = {0};

	fp = fopen("expression.txt", "r");
	if(fp == NULL){
		printf("File cannot be opened!\n");
		return NULL;
	}
	fileSizeCounter = fileSize(fp);
	buffer = createExpression(fp, fileSizeCounter);



	return 0;
}

int stackPush(stackPos p){
	stackPos temp;

	temp = (stackPos)malloc(sizeof(struct tree));
	temp->tree = ;
	temp->next = p->next;
	p->next = temp;
	return 0;
}

stackPos stackPop(stackPos p){
	stackPos temp;

	if(p == NULL){
		printf("Stack is empty!\n");
		return NULL;
	}
	else{
		temp = p->next;
		p->next = temp->next;
		printf("Element %c popped off stack!\n", temp->tree->data);
		free(temp);
	}
	return temp;
}

int treePush(treePos p, char* data){
	treePos temp;

	temp = (treePos)malloc(sizeof(struct tree));
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
}

int fileSize(FILE* fp){
	int bufferSize = 0;
	
	fseek(fp, 0, SEEK_END);
	bufferSize = ftell(fp)+1;
	rewind(fp);
	printf("Buffer size: %d\n", bufferSize);

	return bufferSize;
}

char* createExpression(FILE* fp, int bufferSize){
	char* expression;

	expression = (char*)calloc(bufferSize, sizeof(char));
	fread(expression, bufferSize, 1, fp);
	return expression;
}

int isOperator(char ch){
	if(ch == '+' || ch == '-' ||ch == '*' ||ch == '/')
		return 1;
	else
		return 0;
}

int evaluateExpression(stackPos p, char* expression){
	char* token;

	token = strtok(expression, " ");
	while(token != NULL){
		if(isOperator(*token)){
			printf("%c je operator!\n", *token);
		}
		else{
			printf("%c je broj", *token);
			pushStack();
		}
		token = strtok(NULL, " ");
	}
}

void printInOrder(treePos p){
	if(p == NULL)
		return;
	printInOrder(p->left);
	printf("%c", p);
	printInOrder(p->right);
}
