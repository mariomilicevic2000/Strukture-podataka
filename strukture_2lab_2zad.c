#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Definirati strukturu osoba (ime, prezime, godina rođenja) i napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable*/

struct osoba;
typedef struct osoba *pozicija;
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

int main()
{
	struct osoba head, *q;
	head.next = NULL;
	char izbor = 0;

	while (izbor != 'k') {
		printf("Odaberite operaciju nad listom:\n");
		printf("i za ispis liste\n");
		printf("u za upis na prvo mjesto\n");
		printf("z za upis na zadnje mjesto\n");
		printf("p za pronalazak elementa\n");
		printf("b za brisanje elementa\n");
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
				printf("Ne postoji osoba s tim prezimenom u listi.\n");
			}
			else {
				printf("%s %s %d\n\n", q->ime, q->prezime, q->godina);
			}
			break;
		case 'b':
			izbrisielement(&head);
			break;
		}
	}
}
