//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct {
//	int id;
//	char* nume;
//	int nr_locuitori;
//	float suprafata;
//} Tara;
//
//Tara createTara(int id, const char* nume, int nr_locuitori, float suprafata) {
//	Tara t;
//	t.id = id;
//	t.nume = (char*)malloc(strlen(nume) + 1);
//	strcpy(t.nume, nume);
//	t.nr_locuitori = nr_locuitori;
//	t.suprafata = suprafata;
//	return t;
//}
//
//typedef struct NOD {
//	Tara info;
//	struct NOD* st;
//	struct NOD* dr;
//} NOD;
//
//int inaltimeArbore(NOD* rad) {
//	if (rad) {
//		int hS = inaltimeArbore(rad->st);
//		int hD = inaltimeArbore(rad->dr);
//		return 1 + (hS > hD ? hS : hD);
//	}
//	else return 0;
//}
//
//int gradEchilibru(NOD* rad) {
//	if (rad) {
//		int hS = inaltimeArbore(rad->st);
//		int hD = inaltimeArbore(rad->dr);
//		return hS - hD;
//	}
//	else return 0;
//}
//
//NOD* rotireLaStanga(NOD* rad) {
//	if (rad) {
//		NOD* aux = rad->dr;
//		rad->dr = aux->st;
//		aux->st = rad;
//		return aux;
//	}
//	else return rad;
//}
//
//NOD* rotireLaDreapta(NOD* rad) {
//	if (rad) {
//		NOD* aux = rad->st;
//		rad->st = aux->dr;
//		aux->dr = rad;
//		return aux;
//	}
//	else return rad;
//}
//
//NOD* inserareAVL(NOD* rad, Tara t) {
//	if (rad) {
//		if (t.id < rad->info.id) {
//			rad->st = inserareAVL(rad->st, t);
//		}
//		else {
//			rad->dr = inserareAVL(rad->dr, t);
//		}
//
//		int ge = gradEchilibru(rad);
//
//		if (ge == -2) {
//			int ged = gradEchilibru(rad->dr);
//			if (ged != -1) {
//				rad->dr = rotireLaDreapta(rad->dr);
//			}
//			rad = rotireLaStanga(rad);
//		}
//
//		if (ge == 2) {
//			int ges = gradEchilibru(rad->st);
//			if (ges == 1) {
//				rad = rotireLaDreapta(rad);
//			}
//			else {
//				rad->st = rotireLaStanga(rad->st);
//				rad = rotireLaDreapta(rad);
//			}
//		}
//
//		return rad;
//	}
//	else {
//		NOD* nou = (NOD*)malloc(sizeof(NOD));
//		nou->info = t;
//		nou->st = nou->dr = NULL;
//		return nou;
//	}
//}
//
//void afisareTara(Tara t) {
//	printf("ID: %d | Nume: %s | Locuitori: %d | Suprafata: %.2f km^2\n", t.id, t.nume, t.nr_locuitori, t.suprafata);
//}
//
//void afisareInordine(NOD* rad) {
//	if (rad) {
//		afisareInordine(rad->st);
//		afisareTara(rad->info);
//		afisareInordine(rad->dr);
//	}
//}
//
//void eliberareArbore(NOD* rad) {
//	if (rad) {
//		eliberareArbore(rad->st);
//		eliberareArbore(rad->dr);
//		free(rad->info.nume);
//		free(rad);
//	}
//}
//
//void main() {
//	NOD* rad = NULL;
//
//	FILE* f = fopen("Tari.txt", "r");
//	if (f) {
//		int n;
//		fscanf(f, "%d", &n);
//
//		for (int i = 0; i < n; i++) {
//			int id, nr_loc;
//			float sup;
//			char nume[100];
//			fscanf(f, "%d %s %d %f", &id, nume, &nr_loc, &sup);
//
//			Tara t = createTara(id, nume, nr_loc, sup);
//			rad = inserareAVL(rad, t);
//		}
//
//		fclose(f);
//	}
//
//	printf("\nTari in ordine (AVL):\n");
//	afisareInordine(rad);
//
//	printf("\nInaltime arbore AVL: %d\n", inaltimeArbore(rad));
//
//	eliberareArbore(rad);
//}
