#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tara {
	int id;
	char* nume;
	int nr_locuitori;
	float suprafata;
};
typedef struct tara tara;

struct nod {
	tara info;
	struct nod* st;
	struct nod* dr;
};
typedef struct nod nod;

tara citesteTaraFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	tara t;

	aux = strtok(buffer, sep);
	t.id = atoi(aux);

	aux = strtok(NULL, sep);
	t.nume = malloc(strlen(aux) + 1);
	strcpy(t.nume, aux);

	t.nr_locuitori = atoi(strtok(NULL, sep));
	t.suprafata = atof(strtok(NULL, sep));

	return t;
}

void afisareTara(tara t) {
	printf("Id: %d\n", t.id);
	printf("Nume: %s\n", t.nume);
	printf("Nr locuitori: %d\n", t.nr_locuitori);
	printf("Suprafata: %.2f\n\n", t.suprafata);
}

nod* creareNod(tara info, nod* st, nod* dr) {
	nod* temp = (nod*)malloc(sizeof(nod));
	temp->info.id = info.id;
	temp->info.nume = malloc(strlen(info.nume) + 1);
	strcpy(temp->info.nume, info.nume);
	temp->info.nr_locuitori = info.nr_locuitori;
	temp->info.suprafata = info.suprafata;
	temp->st = st;
	temp->dr = dr;
	return temp;
}

nod* inserare(nod* radacina, tara info) {
	if (radacina == NULL)
		return creareNod(info, NULL, NULL);
	if (info.id < radacina->info.id)
		radacina->st = inserare(radacina->st, info);
	else
		radacina->dr = inserare(radacina->dr, info);
	return radacina;
}

void afisareArbore(nod* rad) {
	if (rad) {
		afisareArbore(rad->st);
		afisareTara(rad->info);
		afisareArbore(rad->dr);
	}
}

void dezalocareArbore(nod* rad) {
	if (rad) {
		dezalocareArbore(rad->st);
		dezalocareArbore(rad->dr);
		free(rad->info.nume);
		free(rad);
	}
}

int main() {
	nod* rad = NULL;
	FILE* f = fopen("Tari.txt", "r");

	while (!feof(f)) {
		tara t = citesteTaraFisier(f);
		rad = inserare(rad, t);
	}
	fclose(f);

	printf("Afisare tari in ordine (dupa id):\n");
	afisareArbore(rad);

	dezalocareArbore(rad);
	return 0;
}
