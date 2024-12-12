#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_NOM 50
#define TAILLE_TELEPHONE 15

struct contact {
    char nom[TAILLE_NOM];
    char telephone[TAILLE_TELEPHONE];
    int departement;
};

struct contact *creer_contact(const char *nom, const char *telephone, int departement) {
    struct contact *c = malloc(sizeof(struct contact));
    if (c != NULL) {
        strcpy(c->nom, nom);
        strcpy(c->telephone, telephone);
        c->departement = departement;
    }
    return c;
}

void copier_contact(struct contact *dest, const struct contact *src) {
    if (dest != NULL && src != NULL) {
        strcpy(dest->nom, src->nom);
        strcpy(dest->telephone, src->telephone);
        dest->departement = src->departement;
    }
}

void affichage_contact(const struct contact *c) {
    if (c != NULL) {
        printf("%c%s%s dep. %d : \n", c->nom[0], c->nom + 1, c->telephone, c->departement);
    }
}

int main() {
    struct contact * C1 = creer_contact("Raoul Boisjoli", "06.43.30.20.12", 63);
    struct contact * C3;
    C3 = C1;
    C1->departement = 64;
    C1->nom[0] = 'T';
    affichage_contact(C1);
    affichage_contact(C3);
    free(C1);
    free(C3);
    return 0;
}
