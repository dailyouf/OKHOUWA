import java.util.Map;
import java.util.EnumMap;
import java.util.ArrayList;

/**
 *  Une piece dans un jeu d'aventure. <p>
 *
 *  Cette classe fait partie du logiciel Zork, un jeu d'aventure simple en mode
 *  texte.</p> <p>
 *
 *  Une "Piece" represente un des lieux dans lesquels se déroule l'action du
 *  jeu. Elle est reliée a au plus quatre autres "Piece" par des sorties. Les
 *  sorties sont étiquettées "nord", "est", "sud", "ouest". Pour chaque
 *  direction, la "Piece" possède une référence sur la piece voisine ou null
 *  s'il n'y a pas de sortie dans cette direction.</p>
 *
 * @author     Michael Kolling
 * @author     Marc Champesme (pour la traduction francaise)
 * @version    1.2
 * @since      August 2000
 */

public class Piece {
 	private String description;
	// mémorise les sorties de cette piece.
	private EnumMap<Direction, Piece> sorties;
	
	private ArrayList<ObjetZork> l;
	
	private int tailleMax; 

	/**
	 *  Initialise une piece décrite par la chaine de caractères spécifiée.
	 *  Initialement, cette piece ne possède aucune sortie. La description fournie
	 *  est une courte phrase comme "la bibliothèque" ou "la salle de TP".
	 *
	 * @param  description  Description de la piece.
	 * @param  taille Nombre d'objet dans notre piece.
	 */
	public Piece(String description, int taille) {
		this.description = description;
		sorties = new EnumMap<Direction, Piece>(Direction.class);
		
		tailleMax = taille;
		l = new ArrayList<ObjetZork>();
		
	}
	
	/**
	 * Ajoute un objet dans la piece
	 * @param l'objet à ajouter
	 * 
	*/
	public void ajouterObjet(ObjetZork objet) {
		if (l.size() < this.tailleMax) {
			l.add(objet);
		}
	}
	
	/**
	 * Ajoute une liste d'objets dans la piece
	 * @param la liste d'objets à ajouter
	 * 
	*/
	public void ajouterObjets(ArrayList<ObjetZork> l2) {
		if ((l.size() + l2.size()) < this.tailleMax) {
			l.addAll(l2);
		}
	}
	/**
	 * Retirer un objet dans la piece
	 * @param l'objet à retirer
	 * 
	*/
	public void retirerObjet(ObjetZork objet) {
		l.remove(objet);
	}
	
	/**
	 * Revoie si notre pièce contient un objet
	 * @param l'objet dont en vérifie l'appartenance
	 * 
	*/
	public boolean contientObjet(ObjetZork objet) {
		return l.contains(objet);
	}
	
	/**
	 * Retourne le nombre d'objets dans la piece
	 * 
	 * @return le nombre d'objets dans de la piece
	*/
	public int getNb() {
		return l.size();
	}
	
	/**
	 * Retourne un tableau contenant les objets dans la piece
	 * 
	 * @return un tableau contenant les objets de la piece
	*/
	public ObjetZork[] geList() {
		ObjetZork[] tab = new ObjetZork[l.size()];
		return l.toArray(tab);
	}

	/**
	 * Retourne le nombre maximal d'objets qui peuvent être contenu dans la piece
	 * 
	 * @return <code>tailleMax</code> le nombre maximal d'objets qui peuvent être contenu dans la piece
	*/
	public int getTailleMax() {
		return this.tailleMax;
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
	 */
	public void setSorties(Piece nord, Piece est, Piece sud, Piece ouest) {
		if (nord != null) {
			sorties.put(Direction.NORD, nord);
		}
		if (est != null) {
			sorties.put(Direction.EST, est);
		}
		if (sud != null) {
			sorties.put(Direction.SUD, sud);
		}
		if (ouest != null) {
			sorties.put(Direction.OUEST, ouest);
		}
	}


	/**
	 *  Renvoie la description de cette piece (i.e. la description spécifiée lors
	 *  de la création de cette instance).
	 *
	 * @return    Description de cette piece
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
	 */
	public String descriptionLongue() {
		return "Vous etes dans " + description + ".\n" + descriptionSorties();
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
		for (Direction sortie :  sorties.keySet()) {
			resulString += " " + sortie;
		}
		return resulString;
	}


	/**
	 *  Renvoie la piece atteinte lorsque l'on se déplace a partir de cette piece
	 *  dans la direction spécifiée. Si cette piece ne possède aucune sortie dans cette direction,
	 *  renvoie null.
	 *
	 * @param  direction  La direction dans laquelle on souhaite se déplacer
	 * @return            Piece atteinte lorsque l'on se déplace dans la direction
	 *      spécifiée ou null.
	 */
	public Piece pieceSuivante(Direction direction) {
		return sorties.get(direction);
	}
}
