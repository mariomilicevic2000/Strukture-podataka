#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

/*Radna verzija, ne radi jos*/

struct node;
typedef struct node* position;
struct node {
	int num;
	position next;
};

int printNodes();
int push(position);
position popStack(position);
position popQueue(position);

int main()
{
	int i;
	time_t t;
	struct node head;
	int numOfElements;
	char choice = NULL;
	head.next = NULL;
	srand(time(&t));

	printf("Koliko elemenata zelite u strukturi?\n");
	scanf("%d", &numOfElements);

	printf("Odaberite nacin rada:\ns za stog\nr za red\n");
	scanf(" %c", &choice);
	switch (choice) {
	case 's':
		for (i = 0; i < numOfElements; i++) {
			push(&head);
			printNodes(head.next);
		}
		for (i = 0; i < numOfElements; i++) {
			popStack(&head);
		}
		break;
	case 'r':
		for (i = 0; i < numOfElements; i++) {
			push(&head);
			printNodes(head.next);
		}
		for (i = 0; i < numOfElements; i++) {
			popQueue(&head);
		}
		break;
	}
	return 0;
}

int printNodes(position p) {
	if (p == NULL) {
		printf("Struktura je prazna!");
		return -1;
	}
	else {
		printf("U strukturi se nalaze elementi:\n");
		while (p != NULL) {
			printf("%d\n", p->num);
			p = p->next;
		}
	}
	return 0;
}

int push(position p) {
	position temp;
	int lowerLimit, upperLimit;
	lowerLimit = 10;
	upperLimit = 100;

	temp = (position)malloc(sizeof(struct node));

	printf("Dodaje se novi nasumicni element od %d do %d\n", lowerLimit, upperLimit);
	temp->num = lowerLimit + (rand()) % (upperLimit - lowerLimit);
	temp->next = p->next;
	p->next = temp;

	return 0;
}

position popStack(position p) {
	position temp;

	if (p == NULL) {
		printf("Stog je prazan!\n");
		return NULL;
	}
	else {
		temp = p->next;
		p->next = temp->next;
		printf("Element %d je izbrisan!\n", temp->num);
		free(temp);
	}
	return temp;
}

position popQueue(position p) {
	position temp, prev;

	if (p == NULL) {
		printf("Red je prazan!\n");
		return NULL;
	}
	else {
		while (p->next != NULL) {
			prev = p;
			p = p->next;
		}
		prev->next = p->next;
		printf("Element %d je izbrisan!\n", p->num);
		free(p);
	}

	return p;
}
