/**
 * Classe ObjetZork représentant les objets de notre logiciel Zork
 * Chaque objet est caractérisé par:
 * - Un nom de longueur strictement positive
 * - Un poids strictement positif
 * - Sa transportabilité qui dépend de son poids 
 *   (sera vrai uniquement si le poids est inférieur à poids_max)
*/
public class ObjetZork {
	
	/** Constante représentant le poids maximal que peut avoir un objet transportable */
	public static final int poids_max = 100;
	
	private String nom;

	private int poids;
	
	/**
	 * Constructeur pour créer un objet Zork avec un nom et un poidss spécifiés.
	 *
	 * @param nom 	le nom de l'objet et dont la longueur doit être strictement positive
	 * @param poids 	le poids de l'objet et qui doit être strictement positif
	 */
	public ObjetZork(String nom, int poids) {
	
		if (nom.length() > 0)
			this.nom = nom;
		else
			this.nom = "";
			
		if (poids > 0) 
			this.poids = poids;
	
	}
	

	/**
	 * Retourne le nom de l'objet
	 
	 * @return <code>this.nom</code>
	 */
	public String getNom() {
		return this.nom;
	}
	
	/**
	 * Retourne le poids de l'objet
	 
	 * @return <code>this.poids</code>
	 */
	public int getPoids() {
		return this.poids;
	}
	
	/**
	 * Retourne la transportabilité de l'objet
	 
	 * @return <code>true</code> si l'objet est transportable;
	 * 	<code>false</code> sinon.	
	 */
	public boolean isTransp() {
		if (poids < poids_max)	
			return true;
			
		return false;
	}
	
	/**
	 * Retroune si deux objets sont eguax; 
	 * C'est le cas uniquement si ils ont le même nom et le même poids
	 * 
	 * @return <code>true</code> si les objets sont egaux;
	 * 	<code>false</code> sinon. 
	 */
	public boolean equals(Object obj) {
	
		if (!(obj instanceof ObjetZork))
			return false;
		
		// ça c'est ce qu'on appelle un cast
		ObjetZork oz = (ObjetZork) obj;
		
		return this.nom.equals(oz.nom) && this.poids  == oz.poids;	
	}	
	/**
	 * Retroune un code hash
	 * 
	 * @return <code>int</code> qui correspond à la somme entre le hash code correspondant au nom avec le poids
	 */
	public int hashCode() {
		
		return this.nom.hashCode() + this.poids;	
		
	}
	
	
	
	/* 	
	  GROSSE ERREUR À NE SURTOUT PAS FAIRE CAR CETTE CLASSE EST NON MODIFIBLE 😅😅😅	
	*/
	public Object clone() {
		
		Object clone;
		
		try {
			clone = super.clone();	
		}
		catch (CloneNotSupportedException e) {
			throw new InternalError("Erreur impossible" + "en th´eorie !");	
		}
		
		return clone;
		
	}
	
}
