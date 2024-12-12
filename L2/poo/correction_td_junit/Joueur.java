import java.util.Collection;
import java.util.ArrayList;

/**
 *  <p>Un joueur dans un jeu d'aventure.</p> 
 *
 *  <p>Cette classe fait partie du logiciel Zork, un jeu d'aventure simple en mode
 *  texte.</p> 
 *
 *  <p>Un joueur peut transporter des objets avec lui. Chaque objet a un poids. 
 *	Le joueur ne peut transporter des objets que dans la mesure où le poids 
 *	total des objets transportés ne dépasse pas une certaine limite ﬁxée à 
 *	l’avance. Le joueur peut transporter plusieurs occurences d'un même
 *	objet (les objets sont distingués en utilisant la méthode equals).
 *	Un joueur est caractérisé par:
 *	<ul>
 *		<li>son nom</li>
 *		<li>son score (supérieur ou égal à 0 et inférieur ou égal à un 
 *			score maximal)</li>
 * 		<li>un score maximal</li>
 *		<li>les objets qu'il transporte</li>
 *		<li>le poids total maximal des objets que le joueur peut 
 *			transporter</li>
 *	</ul>
 * </p>
 *
 * @invariant getNom() != null;
 * @invariant getScoreMax() >= 0;
 * @invariant getScore() >= 0 && getScore() <= getScoreMax();
 * @invariant getPoidsMax() >= 0;
 * @invariant getPoids() >= 0 && getPoids() <= getPoidsMax();
 * @invariant getNbObjets() >= 0;
 * @invariant (\forall int i; i >= 0 && i < getNbObjets();
 *				getTabObjets()[i].estTransportable());
 *
 * @author Sujeevan ASEERVATHAM, Marc Champesme
 * @since 31 janvier 2007
 * @version 28 février 2010
 */
public class Joueur {
	private String nom;
	private int score;
	private int scoreMax;
	private int poids;
	private int poidsMax;
	private Collection<ObjetZork> lesObjets;

	/**
	 * Initalise un joueur avec le nom spécifié.
	 *
	 * @param nom Le nom du joueur
	 *
	 * @requires nom != null;
	 * @ensures getNom().equals(nom);
	 * @ensures getScore() == 0;
	 * @ensures getScoreMax() == 100;
	 * @ensures getNbObjets() == 0;
	 * @ensures getPoids() == 0;
	 * @ensures getPoidsMax() == 50;
	 */
	public Joueur(String nom) {
		this.nom = nom;
		scoreMax = 100;
		poidsMax = 50;
		lesObjets = new ArrayList<ObjetZork>();
	}


	/**
	 * Initialise un joueur.
	 *
	 * @param nom Le nom du joueur.
	 * @param scoreMax Le score maximum autorisé pour ce joueur.
	 *
	 * @requires nom != null;
	 * @requires scoreMax > 0;
	 * @ensures getNom().equals(nom);
	 * @ensures getScore() == 0;
	 * @ensures getScoreMax() == scoreMax;
	 * @ensures getPoids() == 0;
	 * @ensures getNbObjets() == 0;
	 * @ensures getPoidsMax() == 50;
	 */
	public Joueur (String nom, int scoreMax) {
		this.nom = nom;
		this.scoreMax = scoreMax;
		poidsMax = 50;
		lesObjets = new ArrayList<ObjetZork>();
	}


	/**
	 * Initialise un nouveau joueur.
	 *
	 * @param nom le nom du joueur.
	 * @param scoreMax Le score max autorisé pour le joueur.
	 * @param poidsMax Le poids max autorisé pour le joueur.
	 * @param objets les objets en possession du joueur.
	 * @param nbObjets Le nombre d'objet non null dans le tableau objets.
	 *
	 * @requires nom != null;
	 * @requires scoreMax > 0;
	 * @requires poidsMax > 0;
	 * @requires objets != null;
	 * @requires objets.length >= nbObjets;
	 * @requires nbObjets >= 0;
	 * @requires (\forall int i; i >= 0 && i < nbObjets;
	 *			objets[i] != null);
	 * @requires (\forall int i; i >= 0 && i < nbObjets;
	 *			objets[i].estTransportable());
	 * @requires (\sum int i; i >= 0 && i < nbObjets; objets[i].getPoids()) 
	 *							<= poidsMax;
	 * @ensures getNom().equals(nom);
	 * @ensures getScore() == 0;
	 * @ensures getScoreMax() == scoreMax;
	 * @ensures getNbObjets() == nbObjets;
	 * @ensures (\forall int i; i >= 0 && i < nbObjets;
	 *			contient(objets[i]));
	 * @ensures getPoids() == (\sum int i; i >= 0 && i < nbObjets; objets[i].getPoids());
	 * @ensures getPoidsMax() == poidsMax;
	 */
	public Joueur(String nom, int scoreMax, int poidsMax, ObjetZork[] objets, int nbObjets) {
		this.nom = nom;
		this.scoreMax = scoreMax;
		this.poidsMax = poidsMax;
		lesObjets = new ArrayList<ObjetZork>(nbObjets);
		poids = 0;
		for (int i = 0; i < nbObjets; i++) {
			lesObjets.add(objets[i]);
			poids = poids + objets[i].getPoids();
		}
	}

	/**
	 * Retourne le nom de ce joueur.
	 *
	 * @return Le nom de ce joueur.
		 *
	 * @pure
	 */
	public String getNom() {
		return nom;
	}


	/**
	 * Retourne le score de ce joueur.
	 *
	 * @return Le score.
	 *
	 * @ensures \result >= 0;
	 * @ensures \result < scoreMax;
	 *
	 * @pure
	 */
	public int getScore() {
		return score;
	}


	/**
	 * Positionne le score de ce joueur.
	 *
	 * @param score Le nouveau score a fixer.
	 *
	 * @ensures ((score >= 0) && (score <= getScoreMax()))
	 *	==> (getScore() == score);
	 * @ensures ((score < 0) || (score > getScoreMax()))
	 *	==> (getScore() == \old(getScore()));
	 */
	public void setScore(int score) {
		if (score >= 0 && score < scoreMax) {
			this.score = score;
		}
	}


	/**
	 * Retourne le score maximum possible de ce joueur.
	 *
	 * @return Le score maximum possible.
	 *
	 * @ensures \result > 0;
	 *
	 * @pure
	 */
	public int getScoreMax() {
		return scoreMax;
	}
	
	/**
	 * Renvoie le poids total des objets portés par ce joueur.
	 *
	 * @return Le poids total des objets portés par ce joueur.
	 *
	 * @pure
	 */
	public int getPoids() {
		return poids;
	}

	/**
	 * Retourne le poids max des objets que ce joueur peut porter.
	 *
	 * @return le poids max.
	 *
	 * @pure
	 */
	public int getPoidsMax() {
		return poidsMax;
	}

	/**
	  *  Renvoie le nombre d'exemplaires de l'ObjetZork spécifié en possession 
	  * de cette personne. La présence d'un objet est testée en utilisant la 
	  * méthode equals de la classe ObjetZork. L'argument doit etre non 
	  * <code>null</code>.
	  *
	  * @param  oz  Objet dont on cherche a savoir en combien d'exemplaires le joeur possede l'objet.
	  * @return     le nombre d'exemplaires de l'objet spécifié en possession de ce joueur.
	  *
	  * @requires oz != null;
	  * @ensures \result >= 0;
	  * @ensures result <= getNbObjets();
	  * @ensures \result == (\num_of int i; i >= 0 && i < getNbObjets();
	  *				getTabObjets()[i].equals(oz));
	  * @ensures contient(oz) <==> \result > 0;
	  * @ensures !contient(oz) <==> \result == 0;
	  *
	  * @pure
	  */
	public int contientCombienDe(ObjetZork oz) {
		int n = 0;
		for (ObjetZork thisoz : lesObjets) {
			if (thisoz.equals(oz))
				n++;
		}
		return n;
	}




	/**
	 *  Ajoute l'objet spécifié aux objets possedés par ce joueur. Si l'objet
	 *  est déja possédé par ce joueur, un exemplaire supplémentaire de cet objet
	 *  y est ajouté. La présence d'un objet est testé en utilisant la méthode
	 *  equals de la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 * Si le poids total des objets depasse le poids max autorisé, l'objet n'est pas ajouté.
	 *
	 * @param  oz  L'objet a ajouter dans cette piece
	 *
	 * @requires oz != null;
	 * @requires oz.estTransportable();
	 * @ensures ((getPoids() + oz.getPoids()) <= getPoidsMax()) 
	 *			==> (getNbObjets() == \old(getNbObjets() + 1));
	 * @ensures ((getPoids() + oz.getPoids()) <= getPoidsMax()) 
	 *			==> contient(oz);
	 * @ensures ((getPoids() + oz.getPoids()) <= getPoidsMax()) 
	 *	==> contientCombienDe(oz) == \old(contientCombienDe(oz)) + 1;
	 * @ensures ((getPoids() + oz.getPoids()) > getPoidsMax()) 
	 *			==> (getNbObjets() == \old(getNbObjets()));
	 * @ensures ((getPoids() + oz.getPoids()) > getPoidsMax()) 
	 *			==> (contient(oz) == \old(contient(oz)));
	 * @ensures ((getPoids() + oz.getPoids()) > getPoidsMax()) 
	 *	==> (contientCombienDe(oz) == \old(contientCombienDe(oz)));
	 */
	public void ajouter(ObjetZork oz) {
		//on calcule le nouveau poids
		int nouveauPoids = poids + oz.getPoids();

		if (nouveauPoids > poidsMax) {
			return ;
		}

		lesObjets.add(oz);
		poids = nouveauPoids;
	}



	/**
	 *  Retire un exemplaire de l'objet spécifié du joueur si cet objet y est
	 *  présent. Renvoie true si cet objet était effectivement présent chez le
	 *  joueur et que l'objet a pu etre effectivement retiré ; renvoie false sinon.
	 *  La présence d'un objet est testé en utilisant la méthode equals de la
	 *  classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  Objet dont un exemplaire doit etre retirer de cette piece
	 * @return     true si cet objet était effectivement présent ; false sinon.
	 *
	 * @requires oz != null;
	 * @ensures \old(contient(oz)) <==> \result;
	 * @ensures \old(contient(oz)) <==> (contientCombienDe(oz)
	 *					== \old(contientCombienDe(oz)) - 1);
	 * @ensures \old(contientCombienDe(oz) == 1) ==> !contient(oz);
	 * @ensures \old(contientCombienDe(oz) > 1) <==> contient(oz);
	 */
	public boolean retirer(ObjetZork oz) {
		boolean result;
		result = lesObjets.remove(oz);
		if (result) {
			poids = poids - oz.getPoids();
		}
		return result;
	}



	/**
	 *  Renvoie true si la personne possede au moins un exemplaire de l'objet
	 *  spécifié. La présence d'un objet est testé en utilisant la méthode equals
	 *  de la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  Objet dont on cherche a savoir s'il est présent dans cette piece
	 * @return     true si ce joueur possede au moins un exemplaire de l'objet
	 *      spécifié ; false sinon.
	 *
	 * @requires oz != null;
	 * @ensures \result <==> (\exists int i; i >= 0 && i < getNbObjets();
	 *				\old(getTabObjets()[i]).equals(oz));
	 * @pure
	 */
	public boolean contient(ObjetZork oz) {
		return lesObjets.contains(oz);
	}

	/**
	 *  Renvoie une nouvelle instance de tableau contenant tous les objets portés
	 *  par ce joueur. Le tableau renvoyé contient, pour chaque objet, autant
	 *  d'exemplaires de cet objet que le joueur en possède. La taille du tableau
	 *  renvoyé est identique au nombre d'objets portés par ce joueur. L'ordre
	 *  dans lequel les objets sont placé dans le tableau n'est pas significatif,
	 *  lorsque des opérations modifiant les objets portés par ce joueur
	 *  surviennent, il n'est pas garanti que plusieurs appels successifs a cette
	 *  méthode renvoyent les objets dans le meme ordre, y compris pour ce qui est
	 *  des objets non concernés par ces modifications. Cependant, si, entre deux
	 *  appels a cette méthodes, aucune modification n'est intervenue sur les
	 *  objets portés par ce joueur, il est garanti que les objets sont
	 *  renvoyés dans le même ordre.
	 *
	 * @return    Un tableau contenant tous les objets portés par ce joueur.
	 *
	 * @ensures \result != null;
	 * @ensures \result.length == getNbObjets();
	 * @ensures (\forall int i; i >= 0 && i < getNbObjets();
	 *  		\result[i] != null
	 *  		&& contient(\result[i])
	 * 		&& (contientCombienDe(\result[i])
	 *  		    == (\num_of int j; j >= 0 && j < getNbObjets();
	 *  					\result[i].equals(\result[j]))));
	 * @pure
	 */
	public ObjetZork[] getTabObjets() {
		ObjetZork[] result = new ObjetZork[getNbObjets()];
		int i = 0;
		for (ObjetZork thisoz : lesObjets) {
			result[i] = thisoz;
			i++;
		}
		return result;
	}

	/**
	 *  Renvoie le nombre d'ObjetZork du joueur.
	 *
	 * @return    Le nombre d'ObjetZork du joueur.
	 *
	 * @pure
	 */
	public int getNbObjets() {
		return lesObjets.size();
	}


}
