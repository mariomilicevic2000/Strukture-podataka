#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct polynomial poly;
typedef struct polynomial* position;

struct polynomial {
	int coefficient;
	int exponent;
	position next;
};

void loadFromFile(position p) {
	FILE* fp;
	char nameOfFile[20];
	position temp;
	static int iterationCount = 1;

	printf("Upisite ime datoteke koja sadrzi %d. polinom:\n", iterationCount);
	scanf(" %s", nameOfFile);

	fp = fopen(nameOfFile, "r");

	if (fp == NULL) {
		printf("Datoteka ne postoji ili se ne moze otvoriti!\n");
		return -1;
	}
	while (!feof(fp)) {
		temp = (position)malloc(sizeof(poly));
		fscanf(fp, "%d %d ", &temp->coefficient, &temp->exponent);
		temp->next = p->next;
		p->next = temp;
		p = temp;
	}
	if (temp != NULL) {
		printf("Polinom uspjesno procitan!\n");
	}
	fclose(fp);
	iterationCount++;
}

int printPolynomial(position p) {
	p = p->next;

	while (p != NULL) {
		if (p->exponent == 0) {
			printf("%d + ", p->coefficient);
		}
		else if(p->exponent == 1){
			printf("%dx + ", p->coefficient);
		}
		else if(p->next == NULL){
			printf("%dx^%d", p->coefficient, p->exponent);
		}
		else {
			printf("%dx^%d + ", p->coefficient, p->exponent);
		}
		p = p->next;
	}
	printf("\n");
	return 0;
}


int sortedInput(position p) {
	position q, q_previous, temp, end;
	end = NULL;

	while (p->next != end) {
		q_previous = p;
		q = p->next;

		while (q->next != end) {
			if (q->exponent > q->next->exponent) {
				temp = q->next;
				q_previous->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			q_previous = q;
			q = q->next;
		}
		end = q;
	}
	return 0;
}
 
int addPolynomials(position p1, position p2, position sum) {
	position q, temp;

	temp = sum;

	printf("\nZbroj polinoma je:\n");

	while (p1 != NULL && p2 != NULL) {
		if (p1->exponent < p2->exponent) {
			q = (position)malloc(sizeof(poly));

			q->exponent = p1->exponent;
			q->coefficient = p1->coefficient;

			q->next = sum->next;
			sum->next = q;

			p1 = p1->next;
			sum = sum->next;
		}
		else if (p1->exponent > p2->exponent) {
			q = (position)malloc(sizeof(poly));

			q->exponent = p2->exponent;
			q->coefficient = p2->coefficient;

			q->next = sum->next;
			sum->next = q;

			p2 = p2->next;
			sum = sum->next;
		}

		else if (p1->exponent == p2->exponent) {
			q = (position)malloc(sizeof(poly));

			q->exponent = p2->exponent;
			q->coefficient = p2->coefficient + p1->coefficient;


			q->next = sum->next;
			sum->next = q;

			p1 = p1->next;
			p2 = p2->next;

			sum = sum->next;
		}
		if (p1 != NULL) {
			while (p1 != NULL) {
				q = (position)malloc(sizeof(poly));

				q->coefficient = p1->coefficient;
				q->exponent = p1->exponent;

				q->next = sum->next;
				sum->next = q;

				p1 = p1->next;
				sum = sum->next;
			}

		}

		if (p2 != NULL) {
			while (p2 != NULL) {
				q = (position)malloc(sizeof(poly));

				q->coefficient = p2->coefficient;
				q->exponent = p2->exponent;

				q->next = sum->next;
				sum->next = q;

				p2 = p2->next;
				sum = sum->next;
			}

		}
	}
}

int multiplyPolynomials(position p1, position p2, position product) {
	position q, temp;
	position p2head;

	temp = product;
	p2head = p2;

	printf("\nUmnozak polinoma je: \n");

	while (p1 != NULL) {

		while (p2 != NULL) {

			q = (position)malloc(sizeof(poly));

			q->exponent = p1->exponent + p2->exponent;
			q->coefficient = p1->coefficient * p2->coefficient;

			q->next = product->next;
			product->next = q;

			product = product->next;

			p2 = p2->next;
		}

		p1 = p1->next;
		p2 = p2head;
	}

}

int removeZeroes(position p) {
	position temp;

	if (p->next == NULL)
		p = NULL;

	else {
		while (p->next->coefficient != 0 && p->next->next != NULL)
			p = p->next;

		if (p->next->coefficient != 0)
			p = NULL;

	}

	temp = p;

	if (temp != NULL) {
		p = temp->next;
		temp->next = p->next;

		free(p);
	}
}

void addExponents(position p)
{
	position prev, q, after;

	prev = p;
	q = p->next;
	after = q->next;

	while (after != NULL)
	{
		if (q->exponent == after->exponent) {
			after->coefficient = after->coefficient + q->coefficient;

			prev->next = after;

			free(q);

			q = after;
			after = after->next;
			after = prev;
		}
		else {

			prev = q;
			q = after;
			after = after->next;
		}
	}

}

int main()
{
	poly poly1, poly2, sum, product;
	char choice;

	poly1.next = NULL;
	poly2.next = NULL;
	sum.next = NULL;
	product.next = NULL;

	loadFromFile(&poly1);
	sortedInput(&poly1);
	printPolynomial(&poly1);

	loadFromFile(&poly2);
	sortedInput(&poly2);
	printPolynomial(&poly2);
	
	printf("Odaberite operaciju nad polinomima:\nz za zbrajanje\nm za mnozenje\n");
	scanf(" %c", &choice);

	switch (choice) {
	case 'z':
		addPolynomials(poly1.next, poly2.next, &sum);
		sortedInput(&sum);
		removeZeroes(&sum);
		addExponents(&sum);
		printPolynomial(&sum);
		break;
	case 'm':
		multiplyPolynomials(poly1.next, poly2.next, &product);
		sortedInput(&product);
		removeZeroes(&product);
		addExponents(&product);
		printPolynomial(&product);
		break;
	default:
		printf("Odabrana operacija ne postoji!\n");
	}
	return 0;
}
