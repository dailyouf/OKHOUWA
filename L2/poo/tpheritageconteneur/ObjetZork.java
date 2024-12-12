/**
 *  Un objet dans un jeu d'aventure. <p>
 *
 *  Cette classe fait partie du logiciel Zork, un jeu d'aventure simple en mode
 *  texte. Dans le logiciel Zork un objet peut se trouver dans une pièce ou etre
 *  transporté par un joueur s'il est transportable. </p>
 *
 *  <p>Un ObjetZork est complètement caractérisé par une description, un poids et le fait
 *  qu'il soit ou non transportable. Tous les ObjetZork (transportables ou non) possèdent 
 *  un poids supérieur ou égal à zéro, mais les ObjetZork transportables doievnt avoir un
 *  un poids strictement positif. Les ObjetZork sont non modifiables (immutable):
 *  leurs proriétés ne peuvent pas être modifiées après création de l'instance.</p>
 *
 * @invariant descriptionCourte() != null;
 * @invariant descriptionLongue() != null;
 * @invariant getPoids() >= 0;
 * @invariant estTransportable() ==> (getPoids() > 0);
 *
 * @author     Marc Champesme
 * @since      4 mars 2006
 * @version    23 mai 2009
 */
public class ObjetZork {
	private String description;
	private int poids;
	private boolean transportable;


	/**
	 *  Initialise un objet non transportable identifié par la chaine de caractères
	 *  spécifiée et de poids nul. La chaine de caractères spécifiée doit être différente 
	 *  de null.
	 *
	 * @requires description != null;
	 * @ensures descriptionCourte() == description;
	 * @ensures getPoids() == 0;
	 * @ensures !estTransportable();
	 *
	 * @param  description  La chaine de caractères qui identifie cet objet
	 * @throws NullPointerException si la chaîne de caractères spécifiée est null.
	 */
	public ObjetZork(String description) {
	    if (description == null) {
	        throw new NullPointerException("La description doit être non null");
        }
		this.description = description;
	}


	/**
	 *  Initialise un objet transportable identifié par la chaine de caractères
	 *  spécifiée et dont le poids est l'entier spécifié. La chaine de caractères
	 *  spécifiée doit être différente de null et le poids doit etre strictement 
	 *  supérieur à 0.
	 *
	 * @requires description != null;
	 * @requires poids > 0;
	 * @ensures descriptionCourte() == description;
	 * @ensures getPoids() == poids;
	 * @ensures estTransportable();
	 *
	 * @param  description  La chaine de caractères qui identifie cet objet
	 * @param  poids        Le poids de l'objet
	 * @throws NullPointerException si la chaîne de caractères spécifiée est null.
	 * @throws IllegalArgumentException si le poids spécifié est stictement négatif
	 */
	public ObjetZork(String description, int poids) {
		this(description, poids, true);
	}

	/**
	 *  Initialise un ObjetZork identifié par la chaine de caractères
	 *  spécifiée et dont le poids est l'entier spécifié. L'objet est transportable si
	 *  le paramètre estTransportable a la valeur true. La chaine de caractères
	 *  spécifiée doit être différente de null et le poids doit etre supérieur ou
	 *  égal a 0.
	 *
	 * @requires description != null;
	 * @requires poids >= 0;
	 * @requires estTransportable ==> (poids != 0);
	 * @ensures descriptionCourte() == description;
	 * @ensures getPoids() == poids;
	 * @ensures estTransportable() == estTransportable;
	 *
	 * @param  description  La chaine de caractères qui identifie cet objet
	 * @param  poids        Le poids de l'objet
	 * @param estTransportable Indique si l'ObjetZork est transportable
	 * @throws NullPointerException si la chaîne de caractères spécifiée est null.
	 * @throws IllegalArgumentException si le poids spécifié est stictement négatif
	 */
	public ObjetZork(String description, int poids, boolean estTransportable) {
		this(description);
		if (poids < 0) {
		    throw new IllegalArgumentException("Le poids d'un ObjetZork doit être positif");
        }
		if (estTransportable && (poids == 0)) {
		    throw new IllegalArgumentException("Le poids d'un ObjetZork transportable doit être strictement positif");
		}
		transportable = estTransportable;
		this.poids = poids;
	}

	/**
	 *  Renvoie la description de cet objet (i.e. la description spécifiée lors de
	 *  la création de cette instance).
	 *
	 * @return    Description de cet objet
	 *
	 * @pure
	 */
	public String descriptionCourte() {
		return description;
	}


	/**
	 *  Renvoie une description de cet objet contenant l'ensemble de ses
	 *  caractéristiques. Cette description est destinée a fournir une description
	 *  complète de cet objet formatée pour un affichage présenté a l'utilisateur.
	 *
	 * @return    Renvoie une description de cet objet contenant l'ensemble de ses
	 *      caractéristiques
	 *
	 * @pure
	 */
	public String descriptionLongue() {
		String descriptionLongue = description + "(";
		if (transportable) {
			descriptionLongue += poids + "kgs";
		} else {
			descriptionLongue += "non transportable";
		}
		return descriptionLongue + ")";
	}


	/**
	 *  Renvoie le poids de cet objet. Si cet objet n'est pas transportable, la
	 *  valeur retournée n'est pas significative.
	 *
	 * @return    Le poids de cet objet.
	 *
	 * @pure
	 */
	public int getPoids() {
		return poids;
	}


	/**
	 *  Renvoie true si cet objet est transportable ; false sinon.
	 *
	 * @return    true si cet objet est transportable ; false sinon
	 *
	 * @pure
	 */
	public boolean estTransportable() {
		return transportable;
	}


	/**
	 *  Renvoie true si et seulement si l'objet spécifié est un ObjetZork, que les
	 *  deux objets sont tous les deux non transportables, ou bien tous
	 *  les deux transportables et s'ils sont de même poids.
	 *
	 * @param  o  L'objet a comparer avec cet objet.
	 * @return    true si et seulement si l'objet spécifié est un ObjetZork
	 *      possédant les memes propriétés ; false sinon
	 */
	public boolean equals(Object o) {
		if (!(o instanceof ObjetZork)) {
			return false;
		}

		ObjetZork oz = (ObjetZork) o;
		if (estTransportable() != oz.estTransportable()) {
				return false;
        }
		if (getPoids() != oz.getPoids()) {
			return false;
		}
		return description.equals(oz.description);
	}


	/**
	 *  Renvoie un code de hashage pour cet ObjetZork
	 *
	 * @return    un code de hashage pour cet ObjetZork
	 */
	public int hashCode() {
		if (estTransportable()) {
			return poids + 31 * description.hashCode();
		}
		return description.hashCode() + 31 * poids;
	}


	/**
	 *  Renvoie une description succincte sous forme de chaîne de caractères
	 *  de cet ObjetZork.
	 *
	 * @return    Une description succincte de cet ObjetZork
	 */
	public String toString() {
		return description + "(" + poids + ", " + transportable + ")";
	}
}

