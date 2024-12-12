#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define N 20

struct uef {
	unsigned coefficient;
	float note;
};

typedef struct releve_BF_N2_info {
	unsigned long identifiant;
	struct uef algebre;
	struct uef programmation;
	struct uef logique;
} *lien;


float moyenne(lien t);

void trier_moyenne_tab_releves(lien *t, int taille);

int nombre_BF_valide_tab_releves(lien *t, int taille);

lien * initialiser_tab_releves(int taille);

void affichage(lien *t, int taille);

int rechercher_tab_releves(lien *t, int taille, float m_min, float m_max);

int main(){

	
	lien * etudiants = initialiser_tab_releves(N);
	
	affichage(etudiants, N);
	
	trier_moyenne_tab_releves(etudiants, N);
	
	affichage(etudiants, N);
	
	printf("Nombre d'individu ayant validé le semestre: %d \n", nombre_BF_valide_tab_releves(etudiants, N));
	
	printf("Etudiant dont la moyenne est comprise entre 9 et 10 est d'indice: %d \n", rechercher_tab_releves(etudiants, N, 9.0, 10.5));

	return EXIT_SUCCESS;

}


float moyenne(lien t){
	
	int somme = t->algebre.coefficient + t->programmation.coefficient + t->logique.coefficient;
	
	return (float) (t->algebre.coefficient * t->algebre.note + t->programmation.coefficient * t->programmation.note + t->logique.coefficient * t->logique.note) / somme;

}

void trier_moyenne_tab_releves(lien *t, int taille) {
	
	int i, j;
	
	
	for (i=1; i<taille; i++) {
		j=i;
		lien etu = t[j];
		
		while ((j>0) && (moyenne(t[j]) < (moyenne(t[j-1]) ) )) {	
			t[j] = t[j-1];
			j--;
		}
		
		t[j] = etu;
	}
}


int nombre_BF_valide_tab_releves(lien *t, int taille) {
	
	int i=0;
	
	while ((moyenne(t[i]) < 10) && (i < taille)) i++; 
	
	return taille - i;

}

void affichage(lien *t, int taille){

	int i;
	
	for (i=0; i<taille; i++) {
		printf("%2.2g ", moyenne(t[i]));
	}
	printf("\n");
	
}


int rechercher_tab_releves(lien *t, int taille, float m_min, float m_max) {
	
	if ((m_min > moyenne(t[taille - 1])) || (m_max < moyenne(t[0])) || (m_min > m_max)) return -1;
	
	int milieu = taille / 2;
	
	if ((m_min <= milieu) && (milieu <=m_max)) return milieu;
	
	if (milieu < m_min) return rechercher_tab_releves(t+milieu+1, taille, m_min, m_max);
	
	return rechercher_tab_releves(t, milieu, m_min, m_max);
	
}


lien * initialiser_tab_releves(int taille){
	int i;
  
	lien *t = malloc(taille * sizeof(lien));
	
	if (t == NULL){
  		perror("Erreur allocation tableau");
    		exit(2);
  	}
  
  	for (i = 0; i < taille; ++i){
	    
	    t[i] = malloc(sizeof(struct releve_BF_N2_info));
	    
	    if (t[i] == NULL){
	    	fprintf(stderr, "Erreur allocation t[%d] \n", i);
	    	exit(3);
	    }
	    
	    t[i]->identifiant = (122 + rand() % 2) * 100000 + rand() % 18000;
	    t[i]->algebre.coefficient = 7;
	    t[i]->algebre.note = 2.0 + (rand() % 37) * 0.5;
	    t[i]->programmation.coefficient = 6;
	    t[i]->programmation.note = 2.0 + (rand() % 37) * 0.5;
	    t[i]->logique.coefficient = 4;
	    t[i]->logique.note = 2.0 + (rand() % 37) * 0.5;
	
	}
	
	return t;
	
}

