#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Lampa {
	int id;
	char* material;
	float pret;
};
typedef struct Lampa Lampa;

Lampa citireLampaFisier(FILE* f) {
	char buffer[100];
	fgets(buffer, 100, f);
	char sep[3] = ",\n";
	char* aux;
	aux = strtok(buffer, sep);
	Lampa l;
	
	l.id = atoi(aux);
	aux = strtok(NULL, sep);
	l.material = malloc(strlen(aux) + 1);
	strcpy_s(l.material, strlen(aux) + 1, aux);
	l.pret = atof(strtok(NULL, sep));

	return l;
}

void afisareLampa(Lampa l) {
	printf("Lampa cu id-ul: %d , este facuta din materialul: %s , are pretul: %.2f \n", l.id, l.material, l.pret);
}

struct Nod {
	Lampa info;
	Nod* st;
	Nod* dr;
};

typedef struct Nod Nod;

Nod* initializareNod(Lampa l, Nod* st, Nod* dr) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = l;
	nou->st = st;
	nou->dr = dr;

	return nou;
}

Nod* inserare(Nod* rad, Lampa l) {
	if (rad) {
		if (l.id < rad->info.id)
			rad->st = inserare(rad->st, l);
		else
			rad->dr = inserare(rad->dr, l);
		return rad;
	}
	else
		return initializareNod(l, NULL, NULL);
}

void afisareArbore(Nod* rad) {
	if (rad) {
		afisareArbore(rad->st);
		afisareLampa(rad->info);
		afisareArbore(rad->dr);
	}
}

Lampa cautare(Nod* rad, float pretCautat) {
	if (rad) {
		if (rad->info.pret = pretCautat) return rad->info;
		else if (pretCautat < rad->info.pret) return cautare(rad->st, pretCautat);
		else return cautare(rad->dr, pretCautat);

	}
	else {
		printf("\n Nu s-a gasit\n");
	}
}




int main() {





	return 0;
}