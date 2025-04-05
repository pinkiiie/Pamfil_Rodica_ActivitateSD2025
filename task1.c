#include<stdio.h>
#include<malloc.h>


//Nume Pamfil Rodica -> Proprietar
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

    p.nume = (char*)malloc(strlen(nume) + 1);


    strcpy_s(p.nume, strlen(nume) + 1, nume);

    p.adresaProprietate = (char*)malloc(strlen(adresaProprietate) + 1);

    strcpy_s(p.adresaProprietate, strlen(adresaProprietate) + 1, adresaProprietate);

    return p;
}

void afiseazaProprietar(struct Proprietar p) {
    printf("ID: %d, Nume: %s, Varsta: %d\n", p.id, p.nume, p.varsta);
    printf("Adresa proprietate: %s, Suprafata: %.2f mp\n", p.adresaProprietate, p.suprafata);
    printf("Valoare impozabila: %.2f, Pret total: %.2f\n", p.valoareImpozabila, p.pretTotalProprietate);
}

float calculImpozitAnual(struct Proprietar proprietar, float cotaImpozit) {
    return proprietar.valoareImpozabila * cotaImpozit;
}

float calculPretMediuPeMetruPatrat(struct Proprietar proprietar) {
    if (proprietar.suprafata > 0) {
        return proprietar.pretTotalProprietate / proprietar.suprafata;
    }
    else {
        return 0;
    }
}

void modificaVarstaProprietar(struct Proprietar* proprietar, int nouaVarsta) {
    proprietar->varsta = nouaVarsta;
}

int main() {
    struct Proprietar proprietarulMeu;
    float cotaImpozit = 0.01;

    proprietarulMeu = initializareProprietar(1, "Popescu Ion", 45, "Str. Lalelelor 10", 100.5, 50000.0, 150000.0);

    printf("Informatiile despre proprietar:\n");
    afiseazaProprietar(proprietarulMeu);

    float impozitAnual = calculImpozitAnual(proprietarulMeu, cotaImpozit);
    printf("\nImpozitul anual estimat (cota %.2f): %.2f\n", cotaImpozit, impozitAnual);

    float pretMediu = calculPretMediuPeMetruPatrat(proprietarulMeu);
    printf("Pretul mediu pe metru patrat: %.2f\n", pretMediu);

    int nouaVarsta = 46;
    modificaVarstaProprietar(&proprietarulMeu, nouaVarsta);

    printf("\nInformatiile despre proprietar dupa modificarea varstei:\n");
    afiseazaProprietar(proprietarulMeu);

    free(proprietarulMeu.nume);
    proprietarulMeu.nume = NULL;
    free(proprietarulMeu.adresaProprietate);
    proprietarulMeu.adresaProprietate = NULL;

    return 0;
}
