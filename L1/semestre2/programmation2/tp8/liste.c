#include "liste.h"
#include <stdio.h>
#include <stdlib.h>

/* Alloue sur le tas de la mémoire pour un maillon de valeur v */
/* et renvoie l'adresse du maillon */
struct maillon *nouveau_maillon (item v) {
  struct maillon *m = malloc(sizeof(struct maillon));
  m->valeur = v;
  m->suivant = NULL;
  return m;
}

/* Libère l'espace mémoire occupé sur le tas par le maillon d'adresse m */
void detruire_maillon (struct maillon **m) {
  if (*m != NULL) {
    destroy((*m)->valeur);
    free(*m);
    *m = NULL;
  }
}

/* Alloue sur le tas de la mémoire pour une liste, */
/* initialise cette liste à la liste vide */
/* et renvoie l'adresse de la liste allouée */
struct liste *nouvelle_liste() {
  struct liste *l = malloc(sizeof(struct liste));
  l->premier = NULL;
  l->dernier = NULL;
  l->longueur = 0;
  return l;
}

/** Teste si la liste est vide */
/* renvoie un entier ≠ 0 si la liste d'adresse l est vide, 0 sinon */
int est_vide_liste(const struct liste *l) {
  return (l->premier == NULL);
}

/** Renvoie le nombre de maillons dans la liste d'adresse l */
int longueur_liste(const struct liste *l) {
  return l->longueur;
}

/** Teste l'appartenance de la valeur v à la liste d'adresse l */
/* Renvoie l'adresse du premier maillon portant la valeur recherchée, */
/* renvoie NULL si la valeur n'a pas été trouvée */
struct maillon *appartient_liste(const struct liste *l, item v) {
  struct maillon *m;
  for (m = l->premier; m != NULL; m = m->suivant) {
    if eq(m->valeur, v) { return m; }
  }
  return NULL;
}

/* Affiche les valeurs de la liste d'adresse l */
void afficher_liste(const struct liste *l) {
  struct maillon *m;
  for (m = l->premier; m != NULL; m = m->suivant) {
    display(m->valeur);
  }
  printf("\n");
}

/** Renvoie l'adresse du maillon qui occupe la position pos dans la liste d'adresse l */
/* N.B. Le premier maillon occupe la position 0 */
/* Renvoie NULL si la longueur de la liste est inférieure ou égale à pos */
struct maillon *acceder_pos_liste(const struct liste *l, unsigned pos) {
  struct maillon *m;
  for (m = l->premier; m != NULL && pos != 0; pos--)
    m = m->suivant;
  return m;
}

/* Insère le maillon d'adresse m au début de la liste d'adresse l */
void ajouter_maillon_debut_liste(struct liste *l, struct maillon *m) {
  if (est_vide_liste(l)) {  l->dernier = m; }
  m->suivant = l->premier;
  l->premier = m;
  ++l->longueur;
}

/* insertion d'un maillon d'adresse m à la fin de la liste d'adresse l */
/* void ajouter_maillon_fin_liste(struct liste *l, struct maillon *m)
{
  struct maillon *p;
  if (l->longueur == 0) { ajouter_maillon_debut_liste(l,m); return; }
  p = acceder_pos_liste(l, l->longueur - 1);
  p->suivant = m;
  m->suivant = NULL;
  ++l->longueur;
}
*/

/* Insère le maillon d'adresse m à la fin de la liste d'adresse l */
void ajouter_maillon_fin_liste(struct liste *l, struct maillon *m) {
  if (est_vide_liste(l)) {  l->premier = m; }
  m->suivant = NULL;
  l->dernier->suivant = m;
  l->dernier = m;
  ++l->longueur;
}

/** Extrait le premier maillon de la liste d'adresse l */
/* et renvoie l'adresse du maillon extrait */
/** Renvoie NULL si la liste est vide */
struct maillon *extraire_maillon_debut_liste(struct liste *l) {
  struct maillon *m = l->premier;
  if (m != NULL) {
    if (l->longueur == 1) { l->dernier = NULL; }
    l->premier = m->suivant;
    --l->longueur;
    m->suivant = NULL;
  }
  return m;
}

/** Extrait le dernier maillon de la liste d'adresse l */
/* et renvoie l'adresse du maillon extrait */
/* Renvoie NULL si la liste est vide */
struct maillon *extraire_maillon_fin_liste(struct liste *l) {
  struct maillon *m = l->premier, *res;
  if (m == NULL) {  return m; }
  --l->longueur;
  if (m->suivant == NULL) {
    l->premier = NULL;
    l->dernier = NULL;
    return m;
  }
  while (m->suivant->suivant != NULL) {
    m = m->suivant;
  }
  l->dernier = m;
  res = m->suivant;
  m->suivant = NULL;
  return res;
}

/** Libère l'espace mémoire occupé sur le tas par la liste et tous ses maillons */
void detruire_liste (struct liste **l) {
  if (*l != NULL) {
    while (!est_vide_liste(*l)) {
      struct maillon *m = extraire_maillon_debut_liste(*l);
      detruire_maillon(&m);
    }
    free(*l);
    *l = NULL;
  }
}
