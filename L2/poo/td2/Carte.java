/**
 * Classe représentant une carte avec un rang, une famille, une visibilité et un marquage.
 */
public class Carte {
    
    private Rang r;          // Le rang de la carte (As, Roi, etc.)
    private Famille f;       // La famille de la carte (Pique, Trèfle, etc.)
    private boolean visible; // Statut de visibilité de la carte (face visible ou non)
    private boolean marque;  // Indicateur de marquage (si la carte est marquée)

    /**
     * Constructeur de la classe Carte.
     * Initialise la carte avec un rang et une famille, la carte est par défaut non visible et non marquée.
     *
     * @param r Le rang de la carte.
     * @param f La famille de la carte.
     */
    public Carte(Rang r, Famille f) {
        this.r = r;
        this.f = f;
        this.visible = false;  // La carte est initialement face cachée.
        this.marque = false;   // La carte est initialement non marquée.
    }

    /**
     * Retourne la couleur de la carte en fonction de sa famille.
     * Les cartes de Pique et Trèfle sont noires, les autres sont rouges.
     *
     * @return Couleur.NOIR si la carte est de la famille Pique ou Trèfle, Couleur.ROUGE sinon.
     */
    public Couleur getCouleur() {
        if (this.f == Famille.PIQUE || this.f == Famille.TREFLE)
            return Couleur.NOIR;
        return Couleur.ROUGE;
    }

    /**
     * Accède au rang de la carte.
     *
     * @return Le rang de la carte.
     */
    public Rang getRang() {
        return this.r;
    }

    /**
     * Accède à la famille de la carte.
     *
     * @return La famille de la carte.
     */
    public Famille getFamille() {
        return this.f;
    }

    /**
     * Inverse le statut de visibilité de la carte.
     * Si elle était visible, elle devient cachée et vice versa.
     */
    public void retournerCarte() {
        this.visible = !this.visible;
    }

    /**
     * Vérifie si la carte est visible.
     *
     * @return true si la carte est visible, false sinon.
     */
    public boolean estVisible() {
        return this.visible;
    }

    /**
     * Marque la carte. Le marquage est utilisé pour signaler un statut particulier.
     */
    public void marquer() {
        this.marque = true;
    }

    /**
     * Vérifie si la carte est marquée.
     *
     * @return true si la carte est marquée, false sinon.
     */
    public boolean estMarque() {
        return this.marque;
    }

    /**
     * Démarque la carte, annulant le statut de marquage.
     */
    public void demarquer() {
        this.marque = false;
    }

    /**
     * Compare cette carte avec une autre carte pour vérifier si elles sont identiques.
     * Deux cartes sont considérées égales si elles ont le même rang, la même famille,
     * le même statut de visibilité et de marquage.
     *
     * @param c La carte à comparer.
     * @return true si les cartes sont identiques, false sinon.
     */
    public boolean equals(Carte c) {
        return (this.r == c.r && this.f == c.f && this.visible == c.visible && this.marque == c.marque);
    }

    /**
     * Affiche une représentation textuelle de la carte.
     * Le format affiché est "{rang} de {famille}".
     */
    public void afficher() {
        System.out.println(this.r + " de " + this.f);
    }
}

