#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node;
typedef struct node* position;
struct node {
	int num;
	position next;
};

int input(position);
int output(position);
int sort(position);
int unifyElements(position, position, position);
int commonElements(position, position, position);

int main()
{
	struct node L1, L2, unionL, commonL;
	int i, numOfEl;

	L1.next = NULL;
	L2.next = NULL;
	unionL.next = NULL;
	commonL.next = NULL;

	input(&L1);
	input(&L2);

	printf("Ispis obe liste:\n");
	output(&L1);
	output(&L2);

	printf("Unija dvije liste:\n");
	unifyElements(L1.next, L2.next, &unionL);
	output(&unionL);

	printf("Presjek dvije liste:\n");
	commonElements(L1.next, L2.next, &commonL);
	output(&commonL);

	return 0;
}

int input(position p)
{
	FILE* fp;
	char nameOfFile[20];
	position temp;

	printf("\nUpisi ime datoteke: \n");
	scanf("%s", nameOfFile);

	fp = fopen(nameOfFile, "r");

	if (fp == NULL) {
		printf("\nDatoteka se ne moze otvoriti!\n");
	}
	else {
		while (!feof(fp)) {
			temp = (position)malloc(sizeof(struct node));
			fscanf(fp, "%d ", &temp->num);
			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}
	fclose(fp);
	return 0;
}

int output(position p)
{
	if (p == NULL) {
		printf("\nLista ne sadrzi nijedan clan.\n");
	}
	else {
		printf("\nU listi se nalaze:\n");
		while (p != NULL) {
			printf("%d\n", p->num);
			p = p->next;
		}
	}
	return 0;
}

int unifyElements(position p1, position p2, position rez) {

	position q, tmp;

	tmp = rez;

	while (p1 != NULL && p2 != NULL) {

		if (p1->num < p2->num) {

			q = (position)malloc(sizeof(struct node));
			q->num = p1->num;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			rez = rez->next;
		}

		else if (p1->num > p2->num) {

			q = (position)malloc(sizeof(struct node));
			q->num = p2->num;

			q->next = rez->next;
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}

		else if (p1->num == p2->num) {

			q = (position)malloc(sizeof(struct node));
			q->num = p2->num;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;
			rez = rez->next;
		}
	}
	if (p1 != NULL) {
		while (p1 != NULL) {
			q = (position)malloc(sizeof(struct node));

			q->num = p1->num;
			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			rez = rez->next;
		}
	}
	if (p2 != NULL) {
		while (p2 != NULL) {
			q = (position)malloc(sizeof(struct node));

			q->num = p2->num;
			q->next = rez->next;
			rez->next = q;

			p2 = p2->next;
			rez = rez->next;
		}
	}
}

int commonElements(position p1, position p2, position rez) {

	position q, temp;
	temp = rez;

	while (p1 != NULL && p2 != NULL) {
		if (p1->num < p2->num) {
			p1 = p1->next;
		}
		else if (p1->num > p2->num) {
			p2 = p2->next;
		}

		else if (p1->num == p2->num) {

			q = (position)malloc(sizeof(struct node));

			q->num = p2->num;

			q->next = rez->next;
			rez->next = q;

			p1 = p1->next;
			p2 = p2->next;

			rez = rez->next;
		}
	}
}