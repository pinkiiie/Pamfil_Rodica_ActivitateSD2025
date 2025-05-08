#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* nume;
    int varsta;
    char* adresaProprietate;
    float suprafata;
    float valoareImpozabila;
    float pretTotalProprietate;
} Proprietar;

void afisareProprietar(Proprietar p) {
    printf("ID:%d\n", p.id);
    printf("Nume:%s\n", p.nume);
    printf("Varsta:%d\n", p.varsta);
    printf("Adresa:%s\n", p.adresaProprietate);
    printf("Suprafata:%.2f\n", p.suprafata);
    printf("Valoare impozabila:%.2f\n", p.valoareImpozabila);
    printf("Pret total:%.2f\n\n", p.pretTotalProprietate);
}

void afisareVector(Proprietar* v, int n) {
    for (int i = 0; i < n; i++) {
        afisareProprietar(v[i]);
    }
}

void adaugaProprietarInVector(Proprietar** v, int* n, Proprietar p) {
    Proprietar* aux = (Proprietar*)malloc(sizeof(Proprietar) * (*n + 1));
    for (int i = 0; i < *n; i++) {
        aux[i] = (*v)[i];
    }
    aux[*n] = p;
    free(*v);
    *v = aux;
    (*n)++;
}

Proprietar citireProprietar(FILE* f) {
    Proprietar p;
    char buffer[256];
    char* token;

    if (!fgets(buffer, 256, f)) {
        p.nume = NULL;
        return p;
    }

    token = strtok(buffer, "/");
    if (!token) { p.nume = NULL; return p; }
    p.id = atoi(token);

    token = strtok(NULL, "/");
    if (!token) { p.nume = NULL; return p; }
    p.nume = (char*)malloc(strlen(token) + 1);
    strcpy(p.nume, token);

    token = strtok(NULL, "/");
    if (!token) { free(p.nume); p.nume = NULL; return p; }
    p.varsta = atoi(token);

    token = strtok(NULL, "/");
    if (!token) { free(p.nume); p.nume = NULL; return p; }
    p.adresaProprietate = (char*)malloc(strlen(token) + 1);
    strcpy(p.adresaProprietate, token);

    token = strtok(NULL, "/");
    if (!token) { free(p.nume); free(p.adresaProprietate); p.nume = NULL; return p; }
    p.suprafata = atof(token);

    token = strtok(NULL, "/");
    if (!token) { free(p.nume); free(p.adresaProprietate); p.nume = NULL; return p; }
    p.valoareImpozabila = atof(token);

    token = strtok(NULL, "/");
    if (!token) { free(p.nume); free(p.adresaProprietate); p.nume = NULL; return p; }
    p.pretTotalProprietate = atof(token);

    return p;
}

Proprietar* citireVectorFisier(const char* numeFisier, int* n) {
    FILE* f = fopen(numeFisier, "r");
    Proprietar* v = NULL;
    *n = 0;
    while (!feof(f)) {
        Proprietar p = citireProprietar(f);
        if (p.nume != NULL)
            adaugaProprietarInVector(&v, n, p);
    }
    fclose(f);
    return v;
}

void scrieProprietarInFisier(FILE* f, Proprietar p) {
    fprintf(f, "%d/%s/%d/%s/%.2f/%.2f/%.2f\n", p.id, p.nume, p.varsta, p.adresaProprietate, p.suprafata, p.valoareImpozabila, p.pretTotalProprietate);
}

void scrieVectorInFisier(const char* numeFisier, Proprietar* v, int n) {
    FILE* f = fopen(numeFisier, "w");
    for (int i = 0; i < n; i++) {
        scrieProprietarInFisier(f, v[i]);
    }
    fclose(f);
}

void dezalocareVector(Proprietar** v, int* n) {
    for (int i = 0; i < *n; i++) {
        free((*v)[i].nume);
        free((*v)[i].adresaProprietate);
    }
    free(*v);
    *v = NULL;
    *n = 0;
}

Proprietar** creareLinieDinVector(Proprietar* vector, int n, int varstaMin, int varstaMax, int* dim) {
    Proprietar** linie = NULL;
    *dim = 0;
    for (int i = 0; i < n; i++) {
        if (vector[i].varsta >= varstaMin && vector[i].varsta <= varstaMax) {
            linie = (Proprietar**)realloc(linie, (*dim + 1) * sizeof(Proprietar*));
            linie[*dim] = &vector[i];
            (*dim)++;
        }
    }
    return linie;
}

Proprietar*** creeazaMatriceCluster(Proprietar* vector, int n, int* nrLinii, int** dimensiuni) {
    *nrLinii = 3;
    Proprietar*** matrice = (Proprietar***)malloc((*nrLinii) * sizeof(Proprietar**));
    *dimensiuni = (int*)malloc((*nrLinii) * sizeof(int));

    matrice[0] = creareLinieDinVector(vector, n, 0, 30, &((*dimensiuni)[0]));
    matrice[1] = creareLinieDinVector(vector, n, 31, 50, &((*dimensiuni)[1]));
    matrice[2] = creareLinieDinVector(vector, n, 51, 100, &((*dimensiuni)[2]));

    return matrice;
}

void sorteazaLiniile(Proprietar**** matrice, int* dimensiuni, int nrLinii) {
    for (int i = 0; i < nrLinii - 1; i++) {
        for (int j = i + 1; j < nrLinii; j++) {
            if (dimensiuni[i] > dimensiuni[j]) {
                int auxDim = dimensiuni[i];
                dimensiuni[i] = dimensiuni[j];
                dimensiuni[j] = auxDim;

                Proprietar** auxLinie = (*matrice)[i];
                (*matrice)[i] = (*matrice)[j];
                (*matrice)[j] = auxLinie;
            }
        }
    }
}

void afisareMatrice(Proprietar*** matrice, int* dimensiuni, int nrLinii) {
    for (int i = 0; i < nrLinii; i++) {
        printf("Linia %d (nr elemente = %d):\n", i + 1, dimensiuni[i]);
        for (int j = 0; j < dimensiuni[i]; j++) {
            afisareProprietar(*(matrice[i][j]));
        }
    }
}

int main() {
    int n = 0;
    Proprietar* vector = citireVectorFisier("proprietari.txt", &n);
    afisareVector(vector, n);
    scrieVectorInFisier("date.txt", vector, n);

    int nrLinii;
    int* dimensiuni;
    Proprietar*** matrice = creeazaMatriceCluster(vector, n, &nrLinii, &dimensiuni);

    sorteazaLiniile(&matrice, dimensiuni, nrLinii);
    afisareMatrice(matrice, dimensiuni, nrLinii);

    free(dimensiuni);
    free(matrice);
    dezalocareVector(&vector, &n);
    return 0;
}
