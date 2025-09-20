typedef enum {ROUGE, NOIR} Couleur;
typedef enum {AS, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF DIX} Rang;
typedef enum {PIQUE, CARREAU, TREFLE, COEUR} Famille;
typedef enum {TRUE, FALSE} Boolean;
typedef struct Carte_s * Carte;


Carte creerCarte(Rang r, Famille f);

Couleur getCouleur(Carte c);

Rang getRang(Carte c);

Famille getFamille(Carte c);

Boolen equals(Carte c1, Carte c2);

void retournerCarte(Carte c);

Boolean estVisible(Carte c);

void marquer(Carte c);

Boolean estMarque(Carte c);

void libererCarte(Carte * c);
