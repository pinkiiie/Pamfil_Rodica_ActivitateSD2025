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

Lampa crearelampa(int id, const char* material, float pret) {
	Lampa l;
	l.id = id;
	l.material = malloc(strlen(material) + 1);
	strcpy_s(l.material, strlen(material) + 1, material);
	l.pret = pret;
	return l;
}

//Nod Avl
struct Nod {
	Lampa info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

//inaltime arbore
int inaltime(Nod* rad) {
	if (rad) {
		int h1 = inaltime(rad->st);
		int h2 = inaltime(rad->dr);
		return 1 + (h1 > h2?h1 : h2);
	}
	return 0;
}

//grad echilibru
int gradEchi(Nod* rad) {
	if (rad) {
		return inaltime(rad->st) - inaltime(rad->dr);
	}
	return 0;
}

//Rotire stand



//Rotire dreapta









int main() {


	return 0;
}