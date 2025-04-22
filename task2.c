#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Proprietar {
    int id;
    char* nume;
    int varsta;
    char* adresaProprietate;
    float suprafata;
    float valoareImpozabila;
    float pretTotalProprietate;
};

struct Proprietar initializareProprietar(int id, const char* nume, int varsta, const char* adresaProprietate, float suprafata, float valoareImpozabila, float pretTotalProprietate) {
    struct Proprietar p;
    p.id = id;
    p.varsta = varsta;
    p.suprafata = suprafata;
    p.valoareImpozabila = valoareImpozabila;
    p.pretTotalProprietate = pretTotalProprietate;

    size_t dimNume = strlen(nume) + 1;
    p.nume = (char*)malloc(dimNume);
    strcpy_s(p.nume, dimNume, nume);

    size_t dimAdresa = strlen(adresaProprietate) + 1;
    p.adresaProprietate = (char*)malloc(dimAdresa);
    strcpy_s(p.adresaProprietate, dimAdresa, adresaProprietate);

    return p;
}

void afiseazaProprietar(struct Proprietar p) {
    printf("ID: %d, Nume: %s, Varsta: %d\n", p.id, p.nume, p.varsta);
    printf("Adresa: %s, Suprafata: %.2f mp\n", p.adresaProprietate, p.suprafata);
    printf("Valoare impozabila: %.2f, Pret total: %.2f\n\n", p.valoareImpozabila, p.pretTotalProprietate);
}

void afiseazaVector(struct Proprietar* vector, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        afiseazaProprietar(vector[i]);
    }
}

struct Proprietar* copiazaProprietariCuSuprafata(struct Proprietar* vector, int dim, float prag, int* dimNoua) {
    *dimNoua = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].suprafata > prag) {
            (*dimNoua)++;
        }
    }

    struct Proprietar* rezultat = (struct Proprietar*)malloc((*dimNoua) * sizeof(struct Proprietar));
    int k = 0;
    for (int i = 0; i < dim; i++) {
        if (vector[i].suprafata > prag) {
            rezultat[k++] = initializareProprietar(vector[i].id, vector[i].nume, vector[i].varsta, vector[i].adresaProprietate, vector[i].suprafata, vector[i].valoareImpozabila, vector[i].pretTotalProprietate);
        }
    }
    return rezultat;
}

struct Proprietar* mutaProprietariCuVarstaMaiMica(struct Proprietar** vector, int* dim, int pragVarsta, int* dimNoua) {
    *dimNoua = 0;
    for (int i = 0; i < *dim; i++) {
        if ((*vector)[i].varsta < pragVarsta) {
            (*dimNoua)++;
        }
    }

    struct Proprietar* rezultat = (struct Proprietar*)malloc((*dimNoua) * sizeof(struct Proprietar));
    int k = 0;
    int j = 0;
    struct Proprietar* nouVector = (struct Proprietar*)malloc((*dim - *dimNoua) * sizeof(struct Proprietar));

    for (int i = 0; i < *dim; i++) {
        if ((*vector)[i].varsta < pragVarsta) {
            rezultat[k++] = initializareProprietar((*vector)[i].id, (*vector)[i].nume, (*vector)[i].varsta, (*vector)[i].adresaProprietate, (*vector)[i].suprafata, (*vector)[i].valoareImpozabila, (*vector)[i].pretTotalProprietate);
            free((*vector)[i].nume);
            free((*vector)[i].adresaProprietate);
        }
        else {
            nouVector[j++] = (*vector)[i];
        }
    }

    free(*vector);
    *vector = nouVector;
    *dim -= *dimNoua;

    return rezultat;
}

struct Proprietar* concateneazaVectori(struct Proprietar* v1, int dim1, struct Proprietar* v2, int dim2, int* dimRezultat) {
    *dimRezultat = dim1 + dim2;
    struct Proprietar* rezultat = (struct Proprietar*)malloc((*dimRezultat) * sizeof(struct Proprietar));

    for (int i = 0; i < dim1; i++) {
        rezultat[i] = initializareProprietar(v1[i].id, v1[i].nume, v1[i].varsta, v1[i].adresaProprietate, v1[i].suprafata, v1[i].valoareImpozabila, v1[i].pretTotalProprietate);
    }
    for (int i = 0; i < dim2; i++) {
        rezultat[i + dim1] = initializareProprietar(v2[i].id, v2[i].nume, v2[i].varsta, v2[i].adresaProprietate, v2[i].suprafata, v2[i].valoareImpozabila, v2[i].pretTotalProprietate);
    }

    return rezultat;
}

int main() {
    int dim = 5;
    struct Proprietar* vector = (struct Proprietar*)malloc(dim * sizeof(struct Proprietar));

    vector[0] = initializareProprietar(1, "Ion Popescu", 45, "Str. Lalelelor 10", 100.5, 50000.0, 150000.0);
    vector[1] = initializareProprietar(2, "Maria Ionescu", 38, "Str. Crizantemelor 5", 80.0, 40000.0, 120000.0);
    vector[2] = initializareProprietar(3, "Vasile Georgescu", 50, "Str. Zorilor 20", 120.0, 70000.0, 210000.0);
    vector[3] = initializareProprietar(4, "Elena Marin", 30, "Str. Viilor 3", 60.0, 30000.0, 90000.0);
    vector[4] = initializareProprietar(5, "Doru Stan", 65, "Str. Teiului 7", 110.0, 60000.0, 180000.0);

    printf("=== Vector initial ===\n");
    afiseazaVector(vector, dim);

    int dimCopia = 0;
    struct Proprietar* vectorCopia = copiazaProprietariCuSuprafata(vector, dim, 100.0, &dimCopia);

    printf("=== Proprietari cu suprafata > 100 mp ===\n");
    afiseazaVector(vectorCopia, dimCopia);

    int dimMutare = 0;
    struct Proprietar* vectorMutat = mutaProprietariCuVarstaMaiMica(&vector, &dim, 40, &dimMutare);

    printf("=== Vector dupa mutarea celor cu varsta < 40 ===\n");
    afiseazaVector(vector, dim);

    printf("=== Proprietari mutati (varsta < 40) ===\n");
    afiseazaVector(vectorMutat, dimMutare);

    int dimConcat = 0;
    struct Proprietar* vectorConcat = concateneazaVectori(vector, dim, vectorCopia, dimCopia, &dimConcat);

    printf("=== Vector concatenat ===\n");
    afiseazaVector(vectorConcat, dimConcat);

    // Eliberare memorie
    for (int i = 0; i < dim; i++) {
        free(vector[i].nume);
        free(vector[i].adresaProprietate);
    }
    free(vector);

    for (int i = 0; i < dimCopia; i++) {
        free(vectorCopia[i].nume);
        free(vectorCopia[i].adresaProprietate);
    }
    free(vectorCopia);

    for (int i = 0; i < dimMutare; i++) {
        free(vectorMutat[i].nume);
        free(vectorMutat[i].adresaProprietate);
    }
    free(vectorMutat);

    for (int i = 0; i < dimConcat; i++) {
        free(vectorConcat[i].nume);
        free(vectorConcat[i].adresaProprietate);
    }
    free(vectorConcat);

    return 0;
}
