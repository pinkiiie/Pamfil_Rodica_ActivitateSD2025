//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Lampa {
//	int id;
//	char* material;
//	float pret;
//};
//typedef struct Lampa Lampa;
//
//Lampa crearelampa(int id, const char* material, float pret) {
//	Lampa l;
//	l.id = id;
//	l.material = malloc(strlen(material) + 1);
//	strcpy_s(l.material, strlen(material) + 1, material);
//	l.pret = pret;
//	return l;
//}
//
////Nod Avl
//struct Nod {
//	Lampa info;
//	struct Nod* st;
//	struct Nod* dr;
//};
//typedef struct Nod Nod;
//
////inaltime arbore
//int inaltime(Nod* rad) {
//	if (rad) {
//		int h1 = inaltime(rad->st);
//		int h2 = inaltime(rad->dr);
//		return 1 + (h1 > h2?h1 : h2);
//	}
//	return 0;
//}
//
////grad echilibru
//int gradEchi(Nod* rad) {
//	if (rad) {
//		return inaltime(rad->st) - inaltime(rad->dr);
//	}
//	return 0;
//}
//
////Rotire stand
//Nod* rotireStanga(Nod* rad) {
//	if (rad) {
//		Nod* aux = rad->dr;
//		rad->dr = aux->st;
//		aux->st = rad;
//		return aux;
//	}
//	return rad;
//}
//
//
////Rotire dreapta
//
//Nod* rotireDreapta(Nod* rad) {
//	if (rad) {
//		Nod* aux = rad->st;
//		rad->st = aux->dr;
//		aux->dr = rad;
//		return aux;
//	}
//	return rad;
//}
//
////Inserare
//
//Nod* inserareAVL(Nod* rad, Lampa l) {
//	if (rad) {
//		if (l.id < rad->info.id) rad->st = inserareAVL(rad->st, l);
//		else rad->dr = inserareAVL(rad->dr, l);
//		int ge = gradEchi(rad);
//		if (ge == -2) { //dezechi de dreapta
//			if (gradEchi(rad->dr) > 0)
//				rad->dr = rotireDreapta(rad->dr);
//			rad = rotireStanga(rad);
//		}
//		if (ge == 2) {//dezechi de stanga
//			if (gradEchi(rad->st) < 0) rad->st = rotireStanga(rad->st);
//			rad = rotireDreapta(rad);
//		}
//	
//	return rad;
//	}
//	else {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->info = l;
//		nou->st = nou->dr = NULL;
//		return nou;
//	}
//}
//
//void afisareLampa(Lampa l) {
//	printf("Lampa cu id-ul: %d , este facuta din materialul: %s , are pretul: %.2f \n", l.id, l.material, l.pret);
//}
//
//void afisareInOrdine(Nod* rad) {
//	if (rad) {
//		afisareInOrdine(rad->st);
//		afisareLampa(rad->info);
//		afisareInOrdine(rad->dr);
//	}
//}
//
//
//Nod* citireDinFisier(const char* numeFisier, int n) {
//	FILE* f = fopen(numeFisier, "r");
//
//	Nod* rad = NULL;
//	for (int i = 0; i < n; i++) {
//		int id;
//		char material[100];
//		float pret;
//		fscanf(f, "%d,%99[^,],%f", &id, material, &pret);
//		rad = inserareAVL(rad, crearelampa(id, material, pret));
//	}
//
//	fclose(f);
//	return rad;
//}
//
//
//void dezalocare(Nod* rad) {
//	if (rad) {
//		dezalocare(rad->st);
//		dezalocare(rad->dr);
//		free(rad->info.material);
//		free(rad);
//	}
//}
//
//
//
//
//int main() {
//	Nod* rad = citireDinFisier("dateLampa.txt", 10);
//	if (rad) {
//		printf("Arbore AVL in inordine:\n");
//		afisareInOrdine(rad);
//		dezalocare(rad);
//	}
//
//	return 0;
//}