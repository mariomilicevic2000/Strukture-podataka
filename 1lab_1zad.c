#include <stdio.h>
#include <stdlib.h>

/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

typedef struct studenti	//inicijalizacija strukture
{
	char ime[50];
	char prezime[50];
	int bodovi;
}_stud;

int main()
{
	FILE* fp = NULL;
	int i = 0, brojac = 0;
	char c;
	_stud* studenti;

	fp = fopen("studenti.txt", "r");	//otvaranje datoteke
	if (fp == NULL) {
		printf("Datoteka nije uspjesno otvorena!\n");
		return 1;	//ako se datoteka ne otvori uspjesno javljamo korisniku i izlazimo iz programa
	}
	while (!feof(fp))	//vrtimo do kraja datoteke
	{
		c = fgetc(fp);
		if (c == '\n')	//podizemo brojac svaki put kada naletimo na new line
		{
			brojac++;	//brojac redaka
		}
	}
	printf("Broj redaka u datoteci je %d\n", brojac);	//provjera ispravnosti brojaca redaka
	rewind(fp);		//vracanje na pocetak datoteke
	studenti = (_stud*)malloc(brojac * sizeof(_stud));	//dinamicka alokacija niza struktura
	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);	//upis podataka iz txt filea u strukturu
		i++;	//iteriranje na sljedeci clan niza struktura
	}
	for (i = 0; i < brojac; i++) {
		printf("%s %s %d\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);	//ispis podataka iz strukture
	}
	fclose(fp);		//zatvaranje datoteke
	return 0;
}
