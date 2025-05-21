#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraRuj {
	int id;
	float pret;
	char* brand;
};
typedef struct StructuraRuj Ruj;

struct Heap {
	int lungime;
	Ruj* vector;
	int nrElemente;
};
typedef struct Heap Heap;

Ruj citireRujDinFisier(FILE* file) {
	char buffer[100];
	fgets(buffer, 100, file);
	char sep[3] = ",\n";
	Ruj r;
	char* aux;
	aux = strtok(buffer, sep);

	r.id = atoi(aux);
	r.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	r.brand = malloc(strlen_s(aux + 1));
	strcpy_s(r.brand, strlen_s(aux + 1), aux);
	return r;
}

void afisareRuj(Ruj r) {
	printf("Id ruj:%d\n", r.id);
	printf("Pret:%.2f\n", r.pret);
	printf("Brandul rujului:%s\n", r.brand);
}

