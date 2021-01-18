#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXCHAR 256

struct tree;
typedef struct tree* treePos;
struct tree {
	char data[MAXCHAR];
	treePos left;
	treePos right;
};

struct stack;
typedef struct stack* stackPos;
struct stack {
	treePos tree;
	stackPos next;
};

stackPos stackPush(stackPos, treePos);
treePos stackPop(stackPos);
treePos createNode(char*);
int fileSize(FILE*);
char* createBuffer(FILE*, int);
int isOperator(char);
treePos evaluateExpression(char*);
void printInOrder(treePos, char*);
treePos createSubTree(treePos, treePos, treePos);

int main() {
	FILE* fpIn;
	FILE* fpOut;
	int fileSizeCounter = 0;
	char* buffer;
	treePos root;
	char* infix = (char*)calloc(fileSizeCounter + 10, sizeof(char));

	fpIn = fopen("inFile.txt", "r");
	if (fpIn == NULL) {
		printf("Input file cannot be opened!\n");
		return -1;
	}
	fileSizeCounter = fileSize(fpIn);
	buffer = createBuffer(fpIn, fileSizeCounter);
	printf("Loaded postfix expression: %s\n\n", buffer);
	root = evaluateExpression(buffer);
	fclose(fpIn);
	printInOrder(root, infix);
	printf("\nProcessed infix expression: %s\n", infix);
	fpOut = fopen("outFile.txt", "w");
	if (fpOut == NULL) {
		printf("Output file cannot be opened!\n");
		return -1;
	}
	fwrite(infix, 1, fileSizeCounter, fpOut);
	fclose(fpOut);

	return 0;
}

stackPos stackPush(stackPos p, treePos node) {
	stackPos temp;

	if (p == NULL) {
		printf("Invalid pointer in stack!\n");
		return NULL;
	}

	temp = (stackPos)malloc(sizeof(struct stack));
	temp->tree = node;
	temp->next = p->next;
	p->next = temp;

	return p;
}

treePos stackPop(stackPos p) {
	stackPos temp;
	treePos retVal;

	if (p == NULL) {
		printf("Stack is empty!\n");
		return NULL;
	}
	else {
		temp = p->next;
		p->next = temp->next;
		retVal = temp->tree;
		//printf("Element %s popped off stack!\n", temp->tree->data);
		free(temp);
	}
	return retVal;
}

treePos createNode(char* data) {
	treePos temp;

	//printf("U createNode poslano: %s\n", data);
	temp = (treePos)malloc(sizeof(struct tree));
	temp->left = NULL;
	temp->right = NULL;
	strcpy(temp->data, data);
	//printf("Stvoren node sa vrijednoscu: %s\n", temp->data);

	return temp;
}

int fileSize(FILE* fp) {
	int bufferSize = 0;

	fseek(fp, 0, SEEK_END);
	bufferSize = ftell(fp) + 1;
	rewind(fp);
	//printf("Buffer size: %d\n", bufferSize);

	return bufferSize;
}

char* createBuffer(FILE* fp, int bufferSize) {
	char* buffer;

	buffer = (char*)calloc(bufferSize, sizeof(char));
	fread(buffer, bufferSize, 1, fp);

	return buffer;
}

int isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	else
		return 0;
}

treePos evaluateExpression(char* expression) {
	char* token;
	treePos newNode, operatorNode, newTree, temp;
	treePos NodeL, NodeR, stackTop;
	struct stack stog;
	treePos treeRoot = (treePos)malloc(sizeof(struct tree));

	stog.next = NULL;
	token = strtok(expression, " ");
	while (token != NULL) {
		if (isdigit(*token)) {
			//printf("%c je broj\n", *token);
			newNode = createNode(token);
			stackPush(&stog, newNode);
		}
		else if (isOperator(*token)) {
			//printf("%c je operator!\n", *token);
			operatorNode = createNode(token);
			treeRoot = operatorNode;
			NodeL = stackPop(&stog);
			NodeR = stackPop(&stog);
			createSubTree(operatorNode, NodeL, NodeR);
			//printf("DJECA SU: %s i %s\n", treeRoot->left->data, treeRoot->right->data);
			stackPush(&stog, treeRoot);
		}
		token = strtok(NULL, " ");
	}
	return treeRoot;
}

void printInOrder(treePos p, char* string) {
	if (p == NULL)
		return;
	printInOrder(p->left, string);
	printf("%s ", p->data);
	strcat(string, " ");
	strcat(string, p->data);
	printInOrder(p->right, string);
}

treePos createSubTree(treePos operatorNode, treePos varNode1, treePos varNode2) {
	operatorNode->left = varNode1;
	operatorNode->right = varNode2;
	//printf("Stvoreno je stablo: parent = %s, left = %s, right = %s\n", operatorNode->data, operatorNode->left->data, operatorNode->right->data);

	return operatorNode;
}
