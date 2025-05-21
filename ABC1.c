//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <string.h>
//#include <malloc.h>
//
//struct tara {
//	int id;
//	char* nume;
//	int nr_locuitori;
//	float suprafata;
//};
//
//typedef struct tara tara;
//
//tara citesteTara(FILE* f) {
//	tara t;
//	char buffer[100];
//	fscanf(f, "%d", &t.id);
//	fscanf(f, "%s", buffer);
//	t.nume = (char*)malloc(strlen(buffer) + 1);
//	strcpy(t.nume, buffer);
//	fscanf(f, "%d", &t.nr_locuitori);
//	fscanf(f, "%f", &t.suprafata);
//	return t;
//}
//
//void afisareTara(tara t) {
//	printf("%d. %s - %d locuitori - %.2f km2\n", t.id, t.nume, t.nr_locuitori, t.suprafata);
//}
//
//struct NOD {
//	tara info;
//	struct NOD* st;
//	struct NOD* dr;
//};
//
//typedef struct NOD NOD;
//
//NOD* initNod(tara t, NOD* st, NOD* dr) {
//	NOD* nou = (NOD*)malloc(sizeof(NOD));
//	nou->info = t;
//	nou->st = st;
//	nou->dr = dr;
//	return nou;
//}
//
//NOD* inserare(NOD* rad, tara t) {
//	if (rad) {
//		if (rad->info.id > t.id) {
//			rad->st = inserare(rad->st, t);
//		}
//		else {
//			rad->dr = inserare(rad->dr, t);
//		}
//		return rad;
//	}
//	else {
//		return initNod(t, NULL, NULL);
//	}
//}
//
//void afisareArbore(NOD* rad) {
//	if (rad) {
//		afisareArbore(rad->st);
//		afisareTara(rad->info);
//		afisareArbore(rad->dr);
//	}
//}
//
//tara cautareTara(NOD* rad, int id) {
//	if (rad) {
//		if (rad->info.id == id) {
//			return rad->info;
//		}
//		else {
//			if (rad->info.id < id) {
//				return cautareTara(rad->dr, id);
//			}
//			else {
//				return cautareTara(rad->st, id);
//			}
//		}
//	}
//	else {
//		tara t;
//		t.id = -1;
//		t.nume = NULL;
//		t.nr_locuitori = 0;
//		t.suprafata = 0;
//		return t;
//	}
//}
//
//int inaltimeArbore(NOD* rad) {
//	if (rad) {
//		int hSt = inaltimeArbore(rad->st);
//		int hDr = inaltimeArbore(rad->dr);
//		return 1 + (hSt > hDr ? hSt : hDr);
//	}
//	else {
//		return 0;
//	}
//}
//
//void afisareDePeNivel(NOD* rad, int nivelCautat, int nivelCurent) {
//	if (rad) {
//		if (nivelCautat == nivelCurent) {
//			afisareTara(rad->info);
//		}
//		else {
//			afisareDePeNivel(rad->st, nivelCautat, nivelCurent + 1);
//			afisareDePeNivel(rad->dr, nivelCautat, nivelCurent + 1);
//		}
//	}
//}
//
//void main() {
//	NOD* rad = NULL;
//	FILE* f = fopen("tari.txt", "r");
//	int nrTari = 0;
//	fscanf(f, "%d", &nrTari);
//	for (int i = 0; i < nrTari; i++) {
//		rad = inserare(rad, citesteTara(f));
//	}
//	fclose(f);
//
//	afisareArbore(rad);
//	printf("\nTara cautata:\n");
//	afisareTara(cautareTara(rad, 4));
//	printf("\nInaltime arbore: %d\n", inaltimeArbore(rad));
//	printf("\nTari de pe nivelul 2:\n");
//	afisareDePeNivel(rad, 2, 1);
//}
