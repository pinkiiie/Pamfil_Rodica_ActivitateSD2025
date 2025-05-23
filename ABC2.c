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






int main() {





	return 0;
}