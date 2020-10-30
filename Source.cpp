#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Prethodnom zadatku dodati funkcije:
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.*/

struct osoba;
typedef struct osoba* pozicija;
struct osoba
{
	char ime[50];
	char prezime[50];
	int godina;
	pozicija next;
};

void upis(pozicija p)
{
	pozicija temp;

	temp = (pozicija)malloc(sizeof(struct osoba));
	printf("Unesi podatke o osobi:\n");
	scanf("%s %s %d", temp->ime, temp->prezime, &temp->godina);
	temp->next = p->next;
	p->next = temp;
}

void ispis(pozicija p)
{
	if (p == NULL) {
		printf("\nLista ne sadrzi nijedan clan.\n");
	}
	else {
		printf("\nU listi se nalaze podaci:\n");
		while (p != NULL) {
			printf("%s %s %d\n\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
}

pozicija pronadizadnji(pozicija p)
{
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

pozicija pronadiprethodni(pozicija p)
{
	char prez[50];
	if (p->next == NULL) {
		p = NULL;
	}
	else {
		printf("Upisi prezime trazene osobe:\n");
		scanf("%s", prez);
		while (strcmp(p->next->prezime, prez) != 0 && p->next->next != NULL) {
			p = p->next;
		}
		if (strcmp(p->next->prezime, prez) != 0) {
			p = NULL;
		}
	}
	return p;
}

pozicija pronadipoprezimenu(pozicija p)
{
	char prez[50];

	printf("Unesi prezime koje zelis pronaci:\n");
	scanf(" %s", prez);

	while (p != NULL && strcmp(p->prezime, prez) != 0) {
		p = p->next;
	}
	return p;
}

void izbrisielement(pozicija p) {
	pozicija prije;

	prije = pronadiprethodni(p);

	if (prije != NULL) {
		p = prije->next;
		prije->next = p->next;
		printf("Osoba %s %s rodena %d je izbrisana.\n", p->ime, p->prezime, p->godina);
		free(p);
	}
	else {
		printf("Osoba ne postoji u listi.\n");
	}
}

void sort(pozicija p) {
	pozicija temp, start;
	int i = 1;

	temp = (pozicija)malloc(sizeof(struct osoba));
	while (i == 1) {
		i = 0;
		start = p;

		while (start->next->next != NULL) {
			start = start->next;
			if (strcmp(start->prezime, start->next->prezime) > 0) {
				i = 1;

				strcpy(temp->ime, start->ime);
				strcpy(temp->prezime, start->prezime);
				temp->godina = start->godina;

				strcpy(start->ime, start->next->ime);
				strcpy(start->prezime, start->next->prezime);
				start->godina = start->next->godina;

				strcpy(start->next->ime, temp->ime);
				strcpy(start->next->prezime, temp->prezime);
				start->next->godina = temp->godina;
			}
		}
	}

	
	free(temp);
}

void citajizdatoteke(pozicija p) {
	FILE* dat;
	char imedatoteke[20];
	pozicija temp;

	printf("Napisi ime datoteke za citanje");
	scanf(" %s", imedatoteke);

	dat = fopen(imedatoteke, "r");
	if (dat == NULL) {
		printf("\nDatoteka nije uspjesno otvorena ili ne postoji\n");
	}
	else {
		while (!feof(dat)) {
			temp = (pozicija)malloc(sizeof(struct osoba));
			fscanf(dat, "%s %s %d", temp->ime, temp->prezime, &temp->godina);

			temp->next = p->next;
			p->next = temp;
			p = temp;
		}
	}
	fclose(dat);
}

void upisudatoteku(pozicija p) {
	FILE* dat;
	char imedatoteke[20];

	printf("Napisi ime datoteke za citanje");
	scanf(" %s", imedatoteke);

	dat = fopen(imedatoteke, "w");

	if (dat == NULL) {
		printf("\nDatoteka nije uspjesno otvorena ili ne postoji\n");
	}
	else {
		while (p != NULL) {
			fprintf(dat, "%s %s %d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
	fclose(dat);
}

int main()
{
	struct osoba head, * q;
	head.next = NULL;
	char izbor = 0;

	while (izbor != 'k') {
		printf("Odaberite operaciju nad listom:\n");
		printf("i za ispis liste\n");
		printf("u za upis na prvo mjesto\n");
		printf("z za upis na zadnje mjesto\n");
		printf("p za pronalazak elementa\n");
		printf("b za brisanje elementa\n");
		printf("n za dodavanje iza odabranog elementa\n");
		printf("d za dodavanje ispred odabranog elementa\n");
		printf("s za sortiranje po prezimenima\n");
		printf("w za upis u datoteku\n");
		printf("r za citanje iz datoteke\n");
		printf("k za kraj programa\n");
		

		scanf(" %c", &izbor);

		switch (izbor) {
		case 'i':
			ispis(head.next);
			break;
		case 'u':
			upis(&head);
			break;
		case 'z':
			q = pronadizadnji(&head);
			upis(q);
			break;
		case 'p':
			q = pronadipoprezimenu(&head);
			if (q == NULL) {
				printf("\nNe postoji osoba s tim prezimenom u listi.\n");
			}
			else {
				printf("%s %s %d\n\n", q->ime, q->prezime, q->godina);
			}
			break;
		case 'b':
			izbrisielement(&head);
			break;
		case'n':
			q = pronadipoprezimenu(head.next);
			if (q == NULL) {
				printf("\nNe postoji osoba s tim prezimenom u listi.\n");
			}
			else {
				upis(q);
			}
			break;
		case 'd':
			q = pronadiprethodni(&head);
			if (q == NULL) {
				printf("\nNe postoji osoba s tim prezimenom u listi.\n");
			}
			else {
				upis(q);
			}
			break;
		case's':
			sort(&head);
			printf("Sortirano!\n");
			break;
		case'w':
			citajizdatoteke(&head);
			break;
		case'r':
			upisudatoteku(&head);
			break;
		}
	}
}