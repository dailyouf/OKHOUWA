/* Définition du type struct mat_float qui représente des matrices à coefficients flottants */
struct mat_float {
  int lig; /* nombre de lignes de la matrice */
  int col; /* nombre de lignes de la matrice */
  double ** tab_coeff; /* tableau dynamique bidimensionnel des coefficients de la matrice */
                  /* tab_coeff est un tableau de tableaux de flottants */
                  /* c'est-à-dire un pointeur vers un bloc de pointeurs, pointant chacun vers un bloc de flottants */
};

/** Alloue sur le tas l'espace pour une struct mat_float à l lignes et c colonnes, */
/* tous les coefficients étant initialisés à 0.0 */
/* et renvoie l'adresse de la struct mat_float */
struct mat_float *creer_initialiser_matrice (int l, int c);

/** Affiche ligne par ligne le contenu du tab_coeff de l matrice pointée par m */
void afficher_matrice (const struct mat_float *m);

/** Supprime la ligne d'indice l et la colonne d'indice c de la matrice pointée par m */
/* et désalloue l'espace occupé par la ligne et la colonne supprimées */
void reduire_matrice (struct mat_float *m, int l, int c);

/** Crée une struct mat_float et l'initialise à la somme des matrices pointées par m1 et m2 */
/* et renvoie un pointeur vers cette matrice somme */
/* Renvoie NULL si le 1er et le 2nd opérandes n'ont pas le même nombre de lignes et de colonnes */
struct mat_float *additionner_matrice (const struct mat_float *m1, const struct mat_float *m2);

/** Crée une struct mat_float et l'initialise au produit des matrices pointées par m1 et m2 */
/* et renvoie un pointeur vers cette matrice produit */
/* Renvoie NULL si le nombre de colonnes du 1er opérande est différent du nbre de lignes du 2nd */
struct mat_float *multiplier_matrice (const struct mat_float *m1, const struct mat_float *m2);

/** Calcule et renvoie la valeur du déterminant de la matrice pointée par m */
/* (méthode des cofacteurs) */
double determinant_matrice (const struct mat_float *m);

/** Calcule et renvoie la valeur du déterminant de la matrice pointée par m (variante) */
/* (méthode des cofacteurs) */
double determinant_matrice_bis (const struct mat_float *m);

/** Libère la totalité de l'espace mémoire occupé par la matrice dont l'adresse est pointée par m */
void detruire_matrice (struct mat_float **m);

/** Initialise de façon psudo-aléatoire les coefficients de la matrice pointée par m */
/* à des valeurs comprises dans l'intervalle [min, max] */
void initialiser_alea_matrice (struct mat_float *m, double min, double max);
