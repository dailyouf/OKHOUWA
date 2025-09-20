import java.util.ArrayList;

/**
 * Classe représentant un joueur avec un nom, une pièce dans laquelle il se trouve, 
 * et un poids maximum d'ObjetZorks qu'il peut transporter.
 */
public class Joueur {

        // Le poids maximum que le joueur peut transporter.
        private final int poid_max = 100;
    
        // Nom du joueur.
        private String nom;
    
        // La pièce actuelle dans laquelle se trouve le joueur.
        private Piece piece;

        // La liste des ObjetZorks transportés par le joueur.
        private ArrayList<ObjetZork> objets;

        // Le poids total des ObjetZorks actuellement transportés par le joueur.
        private int poidsTotal;

        /**
         * Constructeur de la classe Joueur.
         * Initialise un joueur avec un nom, une pièce et une liste vide d'ObjetZorks transportés.
         *
         * @param nom Le nom du joueur.
         * @param p La pièce initiale où se trouve le joueur.
         */
        public Joueur(String nom, Piece p) {
                this.nom = nom;
                this.piece = p;
                this.objets = new ArrayList<ObjetZork>();  // Initialisation de la liste des ObjetZorks transportés.
                this.poidsTotal = 0;  // Le poids total est initialement nul.
        }

        /**
         * Accède au nom du joueur.
         *
         * @return Le nom du joueur.
         */
        public String getNom() {
                return this.nom;
        }

        /**
         * Change la pièce dans laquelle se trouve le joueur.
         *
         * @param p La nouvelle pièce où se déplace le joueur.
         */
        public void changer_piece(Piece p) {
                this.piece = p;
        }
        
         
        /**
         * Ajoute un ObjetZork au sac du joueur si le poids total après ajout ne dépasse pas le poids maximum.
         *
         * @param ObjetZork L'ObjetZork à ajouter.
         * @return true si l'ObjetZork a été ajouté, false si le poids maximum est dépassé.
         */
        public boolean ajouterObjet(ObjetZork objet) {
                if (this.poidsTotal + objet.getPoids() <= this.poid_max) {
                        this.objets.add(objet);
                        this.poidsTotal += objet.getPoids();
                        return true;  
                }
                return false;
        }

        /**
         * Retire un ObjetZork du sac du joueur.
         *
         * @param ObjetZork L'ObjetZork à retirer.
         * @return true si l'ObjetZork a été retiré, false s'il n'était pas dans le sac.
         */
        public boolean retirerObjetZork(ObjetZork objet) {
                if (this.objets.remove(objet)) {
                        this.poidsTotal -= objet.getPoids();  // Mise à jour du poids total après retrait.
                        return true;
                }
                return false;
        }

        /**
         * Accède à la liste des ObjetZorks actuellement transportés par le joueur.
         *
         * @return La liste des ObjetZorks transportés.
         */
        public ArrayList<ObjetZork> getObjets() {
                return this.objets;
        }

        /**
         * Vérifie si le joueur peut encore transporter un certain poids supplémentaire.
         *
         * @param poids Le poids à vérifier.
         * @return true si le joueur peut encore transporter ce poids, false sinon.
         */
        public boolean peutTransporter(int poids) {
                return this.poidsTotal + poids <= this.poid_max;
        }

        /**
         * Affiche la liste des ObjetZorks transportés par le joueur.
         */
        public void afficherObjets() {
        
                if (this.objets.isEmpty()) {
                        System.out.println(this.nom + " ne transporte aucun ObjetZork.");
                } 
                else {
                        System.out.println(this.nom + " transporte les ObjetZorks suivants :");
			
			for (int i=0; i<objets.size(); i++) {
				
				System.out.println(i + ": " + objets.get(i).getNom() + " qui pèse " + objets.get(i).getPoids());
				
				
			}	
                }
        }
        
}

