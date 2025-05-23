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
	printf("Lampa cu id-ul: %d , este facuta din materialul: %s , are pretul: %.2f", l.id, l.material, l.pret);
}

struct Heap {
	int lungime;
	Lampa* vector;
	int nrElemente;
};

typedef struct Heap Heap;

Heap initializareHeap(int capacitate) {
	Heap h;
	h.lungime = capacitate;
	h.nrElemente = 0;
	h.vector = (Lampa*)malloc(sizeof(Lampa) * capacitate);
	return h;
}

void filtrareHeap(Heap h, int poz) {
	int st = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int max = poz;

	if (st<h.nrElemente && h.vector[st].pret>h.vector[max].pret)
		max = st;
	if (dr<h.nrElemente && h.vector[dr].pret>h.vector[max].pret)
		max = dr;
	if (max != poz) {
		Lampa aux = h.vector[max];
		h.vector[max] = h.vector[poz];
		h.vector[poz] = aux;
		if (max <= (((h.nrElemente) - 2) / 2)) {
			filtrareHeap(h, max);
		}
	}

}


Heap citesteHeapDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap h = initializareHeap(10);
	while (!feof(f)) {
		h.vector[h.nrElemente++] = citireLampaFisier(f);
	}
	fclose(f);
	for (int i = ((h.nrElemente - 2) / 2); i >= 0; i--) {
		filtrareHeap(h, i);
	}
	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++)
		afisareLampa(h.vector[i]);
}

Lampa extragereDinHeap(Heap* h) {
	if (h->nrElemente > 0) {
		Lampa l = h->vector[0];
		h->vector[0] = h->vector[h->nrElemente - 1];
		h->nrElemente--;
	
	for (int i = (h->nrElemente - 2) / 2; i >= 0; i--) {
		filtrareHeap(*h, i);
	}
	return l;
}
}

void dezalocareHeap(Heap* h) {
	for (int i = 0; i < h->lungime; i++) {
		free(h->vector[i].material);
	}
	free(h->vector);
	h->vector = NULL;
	h->lungime = h->nrElemente = 0;
}



int main() {

	Heap heap = citesteHeapDinFisier("dateLampa.txt");
	afisareHeap(heap);
	printf("Elementele extrase sunt: \n");
	for (int i = 0; i < 10; i++)
		afisareLampa(extragereDinHeap(&heap));

	dezalocareHeap(&heap);


	return 0;
}

