/**
 * <p>Modélise un joueur pour le jeu Zork. Un Joueur est caractérisé par un nom,
 * un poids maximal ainsi que par les ObjetZork qu'il "transporte"
 * avec lui et dont le poids total ne doit pas excéder le poids maximal.</p>
 *
 * <p>La somme des poids de tous les ObjetZork transportés doit toujours être inférieure ou
 * égale à un poids maximal fixé définitivement à la création du Joueur. Ce poids maximal
 * doit toujours être supérieur ou égal à zéro.</p>
 *
 * <p>Pour le transport des ObjetZork, le Joueur se comporte comme un conteneur d'ObjetZork
 * possédant les propriétés suivantes:
 * <ul>
 *  <li>Un nombre non borné d'ObjetZork peut être ajouté dans la mesure où la contrainte
 *      sur le poids maximal est respectée.</li>
 *  <li>Le Joueur peut transporter plusieurs exemplaires d'un même ObjetZork</li>
 *  <li>La valeur null n'est pas autorisée parmi les ObjetZork transportés</li>
 *  <li>Les objets transportés ne sont pas ordonnés</li>
 *  <li>La méthode equals de ObjetZork est utilisée pour toutes les opérations
 *  nécessitant de tester la présence d'un ObjetZork</li>
 * </ul>
 * </p>
 *
 * @invariant !contient(null);
 * @invariant getPoidsMax() > 0;
 * @invariant getPoids() >= 0 && getPoids() <= getPoidsMax();
 * @invariant getNbObjets() >= 0;
 * @invariant getNom() != null;
 *
 * @author Sujeevan ASEERVATHAM
 * @author Marc Champesme (amélioration du contrat)
 * @version 31 mars 2013
 * @since 31 janvier 2007
 */
public class Joueur extends ArrayListConteneur {
    
    private String nom;
    private int poidsMax;
    private int poids;

    /**
     * Initalise un joueur ne transportant aucun objet et dont le nom est
     * la chaîne de caractères spécifiée.
     * Le poids maximal est initialisé à 10.
     *
     * @requires nom != null;
     * @ensures getNom().equals(nom);
     * @ensures getPoidsMax() == 10;
     * @ensures getPoids() == 0;
     * @ensures getNbObjets() == 0;
     *
     * @param nom Le nom du joueur
     *
     * @throws NullPointerException si le nom spécifié est null
     */
    public Joueur(String nom) {
        super();
        if (nom == null) {
            throw new NullPointerException("Le nom du Joueur doit être non null");
        }
        this.nom = nom;
        poidsMax = 10;
        poids = 0;

    }


    /**
     * Initalise un joueur ne transportant aucun objet, dont le nom est la chaîne
     * de caractères spécifiée et le poids maximal est l'entier spécifié.
     *
     * @requires nom != null;
     * @requires poidsMax > 0;
     * @ensures getNom().equals(nom);
     * @ensures getPoidsMax() == poidsMax;
     * @ensures getPoids() == 0;
     * @ensures getNbObjets() == 0;
	 *
     * @param nom Le nom du joueur.
     * @param poidsMax Le poids maximal transportable par ce joueur.
     *
     * @throws NullPointerException si le nom spécifié est null
     * @throws IllegalArgumentException si le poids maximal spécifié est négatif ou nul
     */
      public Joueur (String nom, int poidsMax) {
        this(nom);
        if (poidsMax <= 0) {
            throw new IllegalArgumentException("Le poids maximal transportable par un Joueur doit être strictement positif");
        }
        this.poidsMax = poidsMax;
    }


    /**
     * Renvoie le nom du joueur.
     *
     *
     * @return Le nom du joueur.
     *
     * @pure
     */
    public String getNom() {
        return nom;
    }

    /**
     * Renvoie la somme des poids de l'ensemble des ObjetZork transportés
     * par ce Joueur.
     *
     *
     * @return Le poids total des ObjetZork de ce Joueur
     *
     * @pure
     */
    public int getPoids() {
        return poids;
    }

    /**
     * Retourne le poids maximal des objets que le joueur peut porter.
     *
     * @return le poids maximal transportable par ce Joueur
     *
     * @pure
     */
    public int getPoidsMax() {
        return poidsMax;
    }


    // public boolean contient(Object oz) 
    
    /**
     * Renvoie true si l'ObjetZork spécifié peut être ajouté à ce Joueur.
     * Un ObjetZork peut-être ajouté s'il est différent de null, s'il est
     * transportable et si le poids des ObjetZork transportés après l'ajout
     * resterait inférieur au poids maximal fixé pour ce Joueur.
     *
     * @ensures \result <==>
     *     (oz != null) && ((getPoids() + oz.getPoids()) <= getPoidsMax());
     *
     * @param oz L'objet dont on souhaite savoir s'il peut être ajouté aux
     * objets transportés par ce Joueur
     * @return true si l'ObjetZork spécifié peut-être ajouté à la charge de
     * ce Joueur ; false sinon.
     *
     * @pure
     */
    public boolean ajoutEstPossible(ObjetZork oz) {
        return (oz != null)
                && oz.estTransportable()
                && ((getPoids() + oz.getPoids()) <= getPoidsMax());
    }

    /**
     *  Ajoute si possible l'objet spécifié aux objets possedé par ce joueur.
     *  Si l'objet est déja en possédé, un exemplaire supplémentaire de cet objet
     *  y est ajouté. La présence d'un objet est testé en utilisant la méthode
     *  equals de la classe ObjetZork. Si l'ajout n'est pas possible (au sens de
     *  la méthode ajoutEstPossible()), l'objet n'est pas ajouté et la valeur
     *  false est retournée.
     *
     * @ensures \result == \old(ajoutEstPossible(oz));
     * @ensures \result ==> contient(oz);
     * @ensures \result ==> (getPoids() == (\old(getPoids()) + oz.getPoids()));
     * @ensures contient(oz) <==> (\old(ajoutEstPossible(oz)) || \old(contient(oz)));
     * @ensures \result <==>
     *             (contientCombienDe(oz) == (\old(contientCombienDe(oz)) + 1));
     * @ensures !\result <==>
     *             (contientCombienDe(oz) == \old(contientCombienDe(oz)));
     *
     * @param  oz  L'objet a ajouter dans cette piece
     * @return true si l'objet a été effectivement ajouté à ce Joueur ;
     * false sinon.
     */
    public boolean ajouter(ObjetZork oz) {
    	if (super.add(oz)) {
    		poids += oz.getPoids();
    		return true;
    	}
    	
    	return false;
    }
  


    /**
     *  Retire un exemplaire de l'objet spécifié du joueur si cet objet y est
     *  présent. Renvoie true si cet objet était effectivement présent chez le
     *  joueur et que l'objet a pu etre effectivement retiré ; renvoie false sinon.
     *  La présence d'un objet est testé en utilisant la méthode equals de la
     *  classe ObjetZork. L'argument doit etre non <code>null</code>.
     *
     * @ensures \old(contient(oz)) <==> \result;
     * @ensures \old(contient(oz)) <==> (contientCombienDe(oz)
     *                 == \old(contientCombienDe(oz)) - 1);
     * @ensures \old(contientCombienDe(oz) == 1) ==> !contient(oz);
     * @ensures \old(contientCombienDe(oz) > 1) <==> contient(oz);
     * @ensures \result ==> (getPoids() == (\old(getPoids()) - oz.getPoids()));
     *
     * @param  oz  Objet dont un exemplaire doit etre retirer de cette piece
     * @return     true si cet objet était effectivement présent ; false sinon.
     */
    
    
    public boolean retirer(Object o) {
    	if (super.remove(o)) {
    		poids -= oz.getPoids();
    		return true;
    	}
    	
    	return false;
    	
    }
    
    /**
     *  Renvoie une nouvelle instance de tableau contenant tous les objets transportés
     *  par ce Joueur. Le tableau renvoyé contient, pour chaque objet, autant
     *  d'exemplaires de cet objet que ce Joueur en possède. La taille du tableau
     *  renvoyé est identique au nombre d'objets que ce Joueur possède. L'ordre
     *  dans lequel les objets sont placés dans le tableau n'est pas significatif,
     *  lorsque des opérations modifiant les objets transportés par ce Joueur
     *  surviennent, il n'est pas garanti que plusieurs appels successifs à cette
     *  méthode renvoyent les objets dans le même ordre, y compris pour ce qui est
     *  des objets non concernés par ces modifications. Cependant, si, entre deux
     *  appels à cette méthode, aucune modification n'est intervenue sur les
     *  objets transportés par ce {@code Joueur}, il est garanti que les objets sont
     *  renvoyés dans le même ordre.
     *
     * @ensures \result != null;
     * @ensures \result.length == getNbObjets();
     * @ensures (\forall int i; i >= 0 && i < getNbObjets();
     *     \result[i] != null
     *     && contient(\result[i])
     *     && (contientCombienDe(\result[i])
     *         == (\num_of int j; j >= 0 && j < getNbObjets();
     *                 \result[i].equals(\result[j]))));
     *
     * @return    Un tableau contenant tous les objets transportés par ce Joueur.
     *
     * @pure
     */
   /* public ObjetZork[] getTabObjets() {
   	return getTabObjets();
   }
   */
   
    /**
     *  Renvoie le nombre d'ObjetZork transportés par ce Joueur.
     *
     * @return    Le nombre d'ObjetZork de ce Joueur.
     *
     * @pure
     */
    /*
    public int getNbObjets() {
    	return super.getNbObjets();
    }
    */
 
}
