import java.util.Map;
import java.util.HashMap;
import java.util.Collection;
import java.util.ArrayList;

/**
 *  Une piece dans un jeu d'aventure. <p>
 *
 *  Cette classe fait partie du logiciel Zork, un jeu d'aventure simple en mode
 *  texte.</p> <p>
 *
 *  Une "Piece" represente un des lieux dans lesquels se déroule l'action du
 *  jeu. Elle est reliée à au plus quatre autres "Piece" par des sorties. Les
 *  sorties sont étiquettées "nord", "est", "sud", "ouest". Pour chaque
 *  direction, la "Piece" possède une référence sur la piece voisine ou null
 *  s'il n'y a pas de sortie dans cette direction.</p>
 *
 * @invariant descriptionCourte() != null;
 * @invariant getNbObjets() >= 0;
 *
 * @author     Michael Kolling
 * @author     Marc Champesme (pour la traduction francaise et ajout de la gestion des objets)
 * @since      August 2000
 * @version    28 février 2010
 */

public class Piece {
	private String description;
	private Map<String, Piece> sorties;
	private Collection<ObjetZork> lesObjets;

	/**
	 *  Initialise une piece décrite par la chaine de caractères spécifiée.
	 * Initialement, cette piece ne possède aucune sortie et ne contient 
	 * aucun objet. La description fournie est une courte phrase comme
	 * "la bibliothèque" ou "la salle de TP".
	 *
	 * @param  description  Description de la piece.
	 *
	 * @requires description != null;
	 * @ensures descriptionCourte().equals(description);
	 * @ensures getNbObjets() = 0;
	 */
	public Piece(String description) {
		this.description = description;
		sorties = new HashMap<String, Piece>(4);
		lesObjets = new ArrayList<ObjetZork>();

	}


	/**
	 *  Initialise une piece décrite par la chaine de caractères spécifiée et
	 *  contenant les nbObjets premiers objets contenu dans le tableau spécifié. Le
	 *  tableau spécifié doit etre non <code>null</code> et contenir au moins
	 *  nbObjets (i.e. les nbObjets premiers éléments du tableau doivent etre non
	 *  <code>null</code>). Initialement, cette piece ne possède aucune sortie. La
	 *  description fournie est une courte phrase comme "la bibliothèque" ou "la
	 *  salle de TP".
	 *
	 * @param  description  Description de la piece.
	 * @param  tabObjets    Tableau contenant les objets à ajouter à cette pièce
	 * @param  nbObjets     Nombre d'objets du tableau spécifié à placer dans
	 *			cette pièce.
	 *
	 * @requires description != null;
	 * @requires tabObjets != null;
	 * @requires nbObjets >= 0;
	 * @requires tabObjets.length >= nbObjets;
	 * @requires (\forall int i; i >= 0 && i < nbObjets;
	 *  			tabObjets[i] != null);
	 * @ensures descriptionCourte().equals(description);
	 * @ensures getNbObjets() == nbObjets;
	 * @ensures (\forall int i; i >= 0 && i < nbObjets;
	 *  		contientCombienDe(tabObjets[i])
	 *  		== (\num_of int j; j >= 0 && j < nbObjets;
	 *  			tabObjets[j].equals(tabObjets[i])));
	 *
	 */
	public Piece(String description, ObjetZork[] tabObjets, int nbObjets) {
		this.description = description;
		sorties = new HashMap<String, Piece>(4);
		lesObjets = new ArrayList<ObjetZork>(nbObjets + 10);
		for (int i = 0; i < nbObjets; i++) {
			lesObjets.add(tabObjets[i]);
		}
	}


	/**
	 *  Définie les sorties de cette piece. A chaque direction correspond ou bien
	 *  une piece ou bien la valeur null signifiant qu'il n'y a pas de sortie dans
	 *  cette direction.
	 *
	 * @param  nord   La sortie nord
	 * @param  est    La sortie est
	 * @param  sud    La sortie sud
	 * @param  ouest  La sortie ouest
	 *
	 * @ensures pieceSuivante("nord") == nord
	 * @ensures pieceSuivante("est") == est
	 * @ensures pieceSuivante("sud") == sud
	 * @ensures pieceSuivante("ouest") == ouest
	 *
	 */
	public void setSorties(Piece nord, Piece est, Piece sud, Piece ouest) {
		if (nord != null) {
			sorties.put("nord", nord);
		}
		else {
			sorties.remove("nord");
		}

		if (est != null) {
			sorties.put("est", est);
		}
		else {
			sorties.remove("est");
		}

		if (sud != null) {
			sorties.put("sud", sud);
		}
		else {
			sorties.remove("sud");
		}

		if (ouest != null) {
			sorties.put("ouest", ouest);
		}
		else {
			sorties.remove("ouest");
		}
	}
	
	
	/**
	 *  Renvoie la piece atteinte lorsque l'on se déplace a partir de cette piece
	 *  dans la direction spécifiée. Si cette piece ne possède aucune sortie dans
	 *  cette direction, renvoie null.
	 *
	 * @param  direction  La direction dans laquelle on souhaite se déplacer
	 * @return La Piece atteinte lorsque l'on se déplace dans la direction
	 *      spécifiée ou null.
	 */
	public Piece pieceSuivante(String direction) {
		return sorties.get(direction);
	}	


	/**
	 *  Renvoie une description des sorties de cette piece, de la forme: <pre>
	 *  Sorties: nord ouest</pre> Cette description est utilisée dans la
	 *  description longue d'une piece.
	 *
	 * @return    Une description des sorties de cette pièce.
	 */
	public String descriptionSorties() {
		String resulString = "Sorties:";
		for (String str : sorties.keySet()) {
			resulString += " " + str;
		}
		return resulString;
	}


	/**
	 *  Renvoie la description de cette piece (i.e. la description spécifiée lors
	 *  de la création de cette instance).
	 *
	 * @return    Description de cette piece
	 *
	 * @ensures \result != null;
	 *
	 * @pure
	 */
	public String descriptionCourte() {
		return description;
	}


	/**
	 *  Renvoie une description de cette piece mentionant ses sorties et
	 *  directement formatée pour affichage, de la forme: <pre>
	 *  Vous etes dans la bibliothèque.
	 *  Sorties: nord ouest</pre> Cette description utilise la chaine de caractères
	 *  renvoyée par la méthode descriptionSorties pour décrire les sorties de
	 *  cette piece.
	 *
	 * @return    Description affichable de cette piece
	 *
	 * @ensures \result != null;
	 * @ensures \result.indexOf(descriptionCourte()) != -1;
	 * @ensures \result.indexOf(descriptionSorties()) != -1;
	 *
	 * @pure
	 */
	public String descriptionLongue() {
		return "Vous etes dans " + description + ".\n" + descriptionSorties();
	}


	
	/**
	 *  Renvoie le nombre d'ObjetZork présents dans cette piece.
	 *
	 * @return    Le nombre d'ObjetZork présents dans cette piece
	 *
	 * @ensures \result >= 0;
	 * @ensures \result >= (\max ObjetZork oz; contient(oz); contientCombienDe(oz));
	 *  
	 * @pure
	 */
	 
	public int getNbObjets() {
		return lesObjets.size();
	}


	/**
	 *  Renvoie une nouvelle instance de tableau contenant tous les objets présents
	 *  dans cette piece. Le tableau renvoyé contient, pour chaque objet, autant
	 *  d'exemplaires de cet objet que la piece en contient. La taille du tableau
	 *  renvoyé est identique au nombre d'objets présents dans cette piece. L'ordre
	 *  dans lequel les objets sont placé dans le tableau n'est pas significatif,
	 *  lorsque des opérations modifiant les objets présents dans cette pièce
	 *  surviennent, il n'est pas garanti que plusieurs appels successifs a cette
	 *  méthode renvoyent les objets dans le meme ordre, y compris pour ce qui est
	 *  des objets non concernés par ces modifications. Cependant, si, entre deux
	 *  appels a cette méthodes, aucune modification n'est intervenue sur les
	 *  objets présents dans cette piece, il est garanti que les objets sont
	 *  renvoyés dans le même ordre.
	 *
	 * @return    Un tableau contenant tous les objets présents dans cette piece
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
		ObjetZork[] result = new ObjetZork[lesObjets.size()];
		int i = 0;
		for (ObjetZork oz : lesObjets) {
			result[i] = oz;
			i++;
		}
		return result;
	}



	/**
	 *  Renvoie le nombre d'exemplaires de l'objet spécifié présents dans cette
	 *  piece. La présence d'un objet est testé en utilisant la méthode equals de
	 *  la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  Objet dont on cherche a savoir en combien d'exemplaires il est
	 *      présent dans cette piece
	 * @return     le nombre d'exemplaires de l'objet spécifié présents dans cette
	 *      piece.
	 *
	 * @requires oz != null;
	 * @ensures \result >= 0;
	 * @ensures \result == (\num_of int i; i >= 0 && i < getNbObjets();
	 *  				\old(getTabObjets()[i]).equals(oz));
	 * @ensures contient(oz) <==> \result > 0;
	 * @ensures !contient(oz) <==> \result == 0;
	 *  
	 * @pure
	 */
	public int contientCombienDe(ObjetZork oz) {
		int n = 0;
		for (ObjetZork thisoz : lesObjets) {
			if (thisoz.equals(oz)) {
				n++;
			}
		}
		return n;
	}



	/**
	 *  Ajoute l'objet spécifié aux objets présents dans cette pièce. Si l'objet
	 *  est déja présent dans cette pièce un exemplaire supplémentaire de cet objet
	 *  y est ajouté. La présence d'un objet est testé en utilisant la méthode
	 *  equals de la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  L'objet à ajouter dans cette piece
	 *
	 * @requires oz != null;
	 * @ensures contient(oz);
	 * @ensures contientCombienDe(oz) == \old(contientCombienDe(oz)) + 1;	 * @ensures getNbObjets(oz) == \old(getNbObjets(oz)) + 1;
	 */
	public void ajouter(ObjetZork oz) {
		lesObjets.add(oz);
	}



	/**
	 *  Retire un exemplaire de l'objet spécifié de cette piece si cet objet y est
	 *  présent. Renvoie true si cet objet était effectivement présent dans la
	 *  pièce et que l'objet a pu etre effectivement retiré ; renvoie false sinon.
	 *  La présence d'un objet est testé en utilisant la méthode equals de la
	 *  classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  Objet dont un exemplaire doit etre retirer de cette piece
	 * @return     true si cet objet était effectivement présent ; false sinon.
	 *
	 * @requires oz != null;
	 * @ensures \result <==> (getNbObjets() == \old(getNbObjets()) - 1);
	 * @ensures !\result <==> (getNbObjets() == \old(getNbObjets()));
	 * @ensures \old(contient(oz)) <==> \result;
	 * @ensures \old(contient(oz)) <==> (contientCombienDe(oz)
	 *  					== \old(contientCombienDe(oz)) - 1);
	 * @ensures !\old(contient(oz)) <==> (contientCombienDe(oz)
	 *  					== \old(contientCombienDe(oz)));
	 * @ensures \old(contientCombienDe(oz) == 1) ==> !contient(oz);
	 * @ensures \old(contientCombienDe(oz) > 1) <==> contient(oz);
	 */
	public boolean retirer(ObjetZork oz) {
		return lesObjets.remove(oz);
	}



	/**
	 *  Renvoie true si cette piece contient au moins un exemplaire de l'objet
	 *  spécifié. La présence d'un objet est testé en utilisant la méthode equals
	 *  de la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @param  oz  Objet dont on cherche a savoir s'il est présent dans cette piece
	 * @return     true si cette piece contient au moins un exemplaire de l'objet
	 *      spécifié ; false sinon.
	 *
	 * @requires oz != null;
	 * @ensures \result <==> (\exists int i; i >= 0 && i < getNbObjets();
	 *  				\old(getTabObjets()[i]).equals(oz));
	 * @pure
	 */
	public boolean contient(ObjetZork oz) {
		return lesObjets.contains(oz);
	}

}
