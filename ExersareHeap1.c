//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraRuj {
//	int id;
//	float pret;
//	char* brand;
//};
//typedef struct StructuraRuj Ruj;
//
//struct Heap {
//	int lungime;
//	Ruj* vector;
//	int nrElemente;
//};
//typedef struct Heap Heap;
//
//Ruj citireRujDinFisier(FILE* file) {
//	char buffer[100];
//	fgets(buffer, 100, file);
//	char sep[3] = ",\n";
//	Ruj r;
//	char* aux;
//	aux = strtok(buffer, sep);
//
//	r.id = atoi(aux);
//	r.pret = atof(strtok(NULL, sep));
//
//	aux = strtok(NULL, sep);
//	r.brand = malloc(strlen(aux)+1);
//	strcpy_s(r.brand, strlen(aux)+1, aux);
//	return r;
//}
//
//void afisareRuj(Ruj r) {
//	printf("Id ruj:%d\n", r.id);
//	printf("Pret:%.2f\n", r.pret);
//	printf("Brandul rujului:%s\n", r.brand);
//}
//
//Heap initializareHeap(int capacitate) {
//	Heap h;
//	h.lungime = capacitate;
//	h.nrElemente = 0;
//	h.vector = (Ruj*)malloc(sizeof(Ruj) * capacitate);
//
//	return h;
//
//}
//
//void filtrareHeap(Heap h, int poz) {
//	int st = 2 * poz + 1;
//	int dr = 2 * poz + 2;
//	int max = poz;
//
//	if (st<h.nrElemente && h.vector[st].pret>h.vector[max].pret)
//		max = st;
//	if (dr<h.nrElemente && h.vector[dr].pret>h.vector[max].pret)
//		max = dr;
//	if (max != poz) {
//		Ruj aux = h.vector[max];
//		h.vector[max] = h.vector[poz];
//		h.vector[poz] = aux;
//
//		if (max >= (h.nrElemente - 2)/2) {
//			filtrareHeap(h, max);
//		}
//	}
//}
//
//Heap citireHeapDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	Heap h = initializareHeap(10);
//	while (!feof(file)) {
//		h.vector[h.nrElemente++] = citireRujDinFisier(file);
//	}
//	fclose(file);
//	for (int i = (h.nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareHeap(h, i);
//	}
//
//	return h;
//}
//
//void afisareHeap(Heap h) {
//	for (int i = 0; i < h.nrElemente; i++) {
//		afisareRuj(h.vector[i]);
//	}
//
//}
//
//Ruj extragereRuj(Heap* h) {
//	if (h->nrElemente > 0) {
//		Ruj r = h->vector[0];
//		h->vector[0] = h->vector[h->nrElemente - 1];
//		h->vector[h->nrElemente - 1] = r;
//	
//	h->nrElemente--;
//
//	for (int i = (h->nrElemente - 2) / 2; i >= 0; i--) {
//		filtrareHeap(*h, i);
//	}
//
//	return r;
//	}
//}
//
//void dezalocareHeap(Heap* h) {
//	for (int i = 0; i < h->lungime; i++) {
//		free(h->vector[i].brand);
//	}
//	free(h->vector);
//	h->vector = NULL;
//	h->lungime = h->nrElemente = 0;
//}
//
//
//int main() {
//	Heap heap = citireHeapDinFisier("DateRuj.txt");
//	afisareHeap(heap);
//	printf("elemente extrase: \n\n");
//	for (int i = 0; i < 10; i++) { //avem 10 rujuri in fisierul cu date
//		afisareRuj(extragereRuj(&heap));
//	}
//	dezalocareHeap(&heap);
//
//
//
//
//	return 0;
//}
//
//
//
//
//
//
//
