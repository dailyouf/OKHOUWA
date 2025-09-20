#include exo1_inter.h

struct Carte {
	
	Rang r;
	
	Famille f;
	
	Boolean visible;
	
	Boolean marque;

};


Cake new() {
	
	return (Carte) malloc(sizeof(struct Carte))
}


Carte creerCarte(Rang r, Famille f) {
	
	myCard = new();
	
	myCard.r = r;
	
	myCard.f = f;
	
	myCard.visible = FALSE;
	
	myCard.marque = FALSE;
	
	return myCard;
	
}


Couleur getCouleur(Carte c) {
	
	if (c.f == PIQUE || c.f == TREFLE)
		return NOIR;
	
	else 
		return ROUGE;
			
}


Rang getRang(Carte c) {
	
	return c.r;
	
}


Famille getFamille(Carte c) {
	
	return c.f;	
	
}

Boolen equals(Carte c1, Carte c2) {

	return (c1.r==c2.r && c1.f==c2.f && c1.visible==c2.visible && c1.marque==c2.marque);
	
}

void retournerCarte(Carte c) {

	c.visible = !(c.visible);
	
}

Boolean estVisible(Carte c) {
	
	return c.visible;
}

void marquer(Carte c){

	c.marquer = TRUE;
	
}

Boolean estMarque(Carte c) {
	
	return c.marque;
	
}

void libererCarte(Carte * c) {
	
	free(c);
	*c = NULL;
}



