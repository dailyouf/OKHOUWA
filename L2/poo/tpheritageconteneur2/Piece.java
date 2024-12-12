import java.util.Map;
import java.util.EnumMap;

/**
 *  Une piece dans un jeu d'aventure. <p>
 *
 *  Cette classe fait partie du logiciel Zork, un jeu d'aventure simple en mode
 *  texte.</p>
 *
 *  <p>Une "Piece" represente un des lieux dans lesquels se déroule l'action du
 *  jeu. Elle est reliée a au plus quatre autres "Piece" par des sorties. Les
 *  sorties sont étiquettées "nord", "est", "sud", "ouest". Pour chaque
 *  direction, la "Piece" possède une référence sur la piece voisine ou null
 *  s'il n'y a pas de sortie dans cette direction.</p>
 *
 *  <p>Une Piece est aussi un conteneur d'ObjetZork possédant les propriétés
 *  suivantes:
 * <ul>
 *  <li>Un nombre non borné d'ObjetZork peut être ajouté dans la Piece.</li>
 *  <li>La Piece peut contenir plusieurs exemplaires d'un même ObjetZork</li>
 *  <li>La valeur null n'est pas autorisée parmi les ObjetZork présents dans
 *  la Piece</li>
 *  <li>Les objets contenus dans la Piece ne sont pas ordonnés</li>
 *  <li>La méthode equals de ObjetZork est utilisée pour toutes les opérations
 *  nécessitant de tester la présence d'un ObjetZork</li>
 * </ul>
 * </p>
 *
 * @invariant !contient(null);
 * @invariant descriptionCourte() != null;
 * @invariant descriptionLongue() != null;
 * @invariant descriptionSorties() != null;
 * @invariant getNbObjets() >= 0;
 *
 * @author     Michael Kolling
 * @author     Marc Champesme (pour la traduction francaise)
 * @since      August 2000
 * @version    23 mai 2009
 */

public class Piece extends ArrayConteneur{
    private String description;

    // mémorise les sorties de cette piece.
    private Map<Direction, Piece> sorties;

    /**
     *  Initialise une piece décrite par la chaine de caractères spécifiée.
     *  Initialement, cette piece ne possède aucune sortie. La description fournie
     *  est une courte phrase comme "la bibliothèque" ou "la salle de TP".
     *
     * @requires description != null;
     * @ensures descriptionCourte() == description;
     * @ensures getNbObjets() == 0;
     * @ensures pieceSuivante("nord") == null;
     * @ensures pieceSuivante("est") == null;
     * @ensures pieceSuivante("sud") == null;
     * @ensures pieceSuivante("ouest") == null;
     *
     * @param  description  Description de la piece.
     * @throws NullPointerException si le paramètre est null
     */
    public Piece(String description) {
    	super();
    	if (description == null) {
    		throw new NullPointerException("La description d'une Piece ne peut-être null");
    	}
        this.description = description;
        sorties = new EnumMap<Direction, Piece>(Direction.class);
    }

    /**
     *  Initialise une piece décrite par la chaine de caractères spécifiée et
     *  contenant les nbObjets premiers objets contenu dans le tableau spécifié. Le
     *  tableau spécifié doit etre non <code>null</code> et contenir au moins
     *  nbObjets (i.e. les nbObjets premiers éléments du tableau doivent être
     *  des instances non <code>null</code> de la classe ObjetZork. Initialement,
     *  cette piece ne possède aucune sortie. La description fournie est une courte
     *  phrase comme "la bibliothèque" ou "la salle de TP".
     *
     * @requires description != null;
     * @requires tabObjets != null;
     * @requires nbObjets >= 0;
     * @requires tabObjets.length >= nbObjets;
     * @requires (\forall int i; i >= 0 && i < nbObjets;
     *         tabObjets[i] != null);
     * @ensures descriptionCourte() == description;
     * @ensures getNbObjets() == nbObjets;
     * @ensures (\forall int i; i >= 0 && i < nbObjets;
     *     contientCombienDe(tabObjets[i])
     *     == (\num_of int j; j >= 0 && j < nbObjets;
     *         tabObjets[j].equals(tabObjets[i])));
     * @ensures pieceSuivante("nord") == null;
     * @ensures pieceSuivante("est") == null;
     * @ensures pieceSuivante("sud") == null;
     * @ensures pieceSuivante("ouest") == null;
     *
     * @param  description  Description de la piece.
     * @param  tabObjets    Tableau contenant les nbObjets à placer dans cette Piece
     * @param  nbObjets     Nombre d'ObjetZork à placer dans cette Piece
     *
     * @throws NullPointerException si l'un des paramètres ou l'un des nbObjets premiers
     * éléments de tabObjets est null.
     * @throws IllegalArgumentException si le nombre d'objets spécifié est strictement
     * supérieur à la taille du tableau spécifié
     */
    public Piece(String description, ObjetZork[] tabObjets, int nbObjets) {
        this(description);
        
        if (nbObjets > tabObjets.length) {
            throw new IllegalArgumentException("Le nombre d'objets spécifié doit être inférieur à la taille du tableau");
        }
        
        for (int i = 0; i < nbObjets; i++) {
            if (tabObjets[i] == null) {
                throw new NullPointerException("Les " + nbObjets
                                + " premiers éléments du tableau doivent être non null");
            }
            super.ajouter(tabObjets[i]);
        }
    }

    /**
     *  Renvoie le nombre d'exemplaires de l'objet spécifié présents dans cette
     *  piece. La présence d'un objet est testé en utilisant la méthode equals de
     *  la classe ObjetZork. Renvoie 0 si l'argument est null.
     *
     * @ensures \result >= 0;
     * @ensures contient(oz) <==> \result > 0;
     * @ensures !contient(oz) <==> \result == 0;
     * @ensures (oz == null) ==> (\result == 0);
     *
     * @param  oz  Objet dont on cherche a savoir en combien d'exemplaires il est
     *      présent dans cette piece
     * @return     le nombre d'exemplaires de l'objet spécifié présents dans cette
     *      piece
     * @pure
     */
   // public int contientCombienDe(Object oz) 



    /**
     *  Ajoute l'objet spécifié aux objets présents dans cette pièce. Si l'objet
     *  est déja présent dans cette piece un exemplaire supplémentaire de cet objet
     *  y est ajouté. La présence d'un objet est testé en utilisant la méthode
     *  equals de la classe ObjetZork. L'argument doit etre non <code>null</code>.
     *
     * @requires oz != null;
     * @ensures contient(oz);
     * @ensures contientCombienDe(oz) == \old(contientCombienDe(oz)) + 1;
     *
     * @param  oz  L'objet a ajouter dans cette piece
     * @throws NullPointerException si le paramètre est null
     */
    // public void ajouter(ObjetZork oz) 



    /**
     *  Retire un exemplaire de l'objet spécifié de cette piece si cet objet y est
     *  présent. Renvoie true si cet objet était effectivement présent dans la
     *  pièce et que l'objet a pu etre effectivement retiré ; renvoie false sinon.
     *  La présence d'un objet est testé en utilisant la méthode equals de la
     *  classe ObjetZork. L'argument doit etre non <code>null</code>.
     *
     * @ensures \old(contient(oz)) <==> \result;
     * @ensures \old(contient(oz)) <==> (contientCombienDe(oz)
     *                 == \old(contientCombienDe(oz)) - 1);
     * @ensures \old(contientCombienDe(oz) == 1) ==> !contient(oz);
     * @ensures \old(contientCombienDe(oz) > 1) <==> contient(oz);
     *
     * @param  oz  Objet dont un exemplaire doit etre retirer de cette piece
     * @return     true si cet objet était effectivement présent ; false sinon.
     */
   // public boolean retirer(Object oz) 



    /**
     *  Renvoie true si cette piece contient au moins un exemplaire de l'objet
     *  spécifié. La présence d'un objet est testé en utilisant la méthode equals
     *  de la classe ObjetZork. Renvoie false si l'argument est <code>null</code>.
     *
     * @ensures \result <==> (contientCombienDe(oz) > 0);
     *
     * @param  oz  Objet dont on cherche a savoir s'il est présent dans cette piece
     * @return     true si cette piece contient au moins un exemplaire de l'objet
     *      spécifié ; false sinon.
     * @pure
     */
    // public boolean contient(Object oz)

    /**
     *  Renvoie le nombre d'ObjetZork présents dans cette piece.
     *
     * @ensures \result >= 0;
     *
     * @return    Le nombre d'ObjetZork présents dans cette piece.
     *
     * @pure
     */
    // public int getNbObjets() 

    /**
     *  Renvoie une nouvelle instance de tableau contenant tous les objets présents
     *  dans cette piece. Le tableau renvoyé contient, pour chaque objet, autant
     *  d'exemplaires de cet objet que la piece en contient. La taille du tableau
     *  renvoyé est identique au nombre d'objets présents dans cette piece. L'ordre
     *  dans lequel les objets sont placé dans le tableau n'est pas significatif,
     *  lorsque des opérations modifiant les objets présents dans cette pièce
     *  surviennent, il n'est pas garanti que plusieurs appels successifs à cette
     *  méthode renvoyent les objets dans le même ordre, y compris pour ce qui est
     *  des objets non concernés par ces modifications. Cependant, si entre deux
     *  appels à cette méthode, aucune modification n'est intervenue sur les
     *  objets présents dans cette piece, il est garanti que les objets sont
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
     * @return    Un tableau contenant tous les objets présents dans cette piece
     *
     * @pure
     */
    // public ObjetZork[] getTabObjets() 


    /**
     *  Définie les sorties de cette piece. A chaque direction correspond ou bien
     *  une piece ou bien la valeur null signifiant qu'il n'y a pas de sortie dans
     *  cette direction.
     *
     * @ensures (nord != null) ==> (pieceSuivante(NORD) == nord);
     * @ensures (est != null) ==> (pieceSuivante(EST) == est);
     * @ensures (sud != null) ==> (pieceSuivante(SUD) == sud);
     * @ensures (ouest != null) ==> (pieceSuivante(OUEST) == ouest);
     * @ensures (nord == null) ==> (pieceSuivante(NORD) == \old(pieceSuivante(NORD)));
     * @ensures (est == null) ==> (pieceSuivante(EST) == \old(pieceSuivante(EST));
     * @ensures (sud == null) ==> (pieceSuivante(SUD) == \old(pieceSuivante(SUD)));
     * @ensures (ouest == null) ==> (pieceSuivante(OUEST) == \old(pieceSuivante(OUEST)));
     *
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
     *  Renvoie la piece atteinte lorsque l'on se déplace a partir de cette piece
     *  dans la direction spécifiée. Si cette piece ne possède aucune sortie dans
     *  cette direction, renvoie null.
     *
     * @requires direction != null;
     *
     * @param  direction  La direction dans laquelle on souhaite se déplacer
     * @return            Piece atteinte lorsque l'on se déplace dans la direction
     *      spécifiée ou null.
     *
     * @pure
     */
    public Piece pieceSuivante(Direction direction) {
        return sorties.get(direction);
    }

    /**
     *  Renvoie la description de cette piece (i.e. la description spécifiée lors
     *  de la création de cette instance).
     *
     * @return    Description de cette piece
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
     * @return    Description affichable de cette piece.
     *
     * @pure
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
     *
     * @pure
     */
    public String descriptionSorties() {
        String resulString = "Sorties:";
        for (Direction sortie : sorties.keySet()) {
            resulString += " " + sortie;
        }
        return resulString;
    }
}
