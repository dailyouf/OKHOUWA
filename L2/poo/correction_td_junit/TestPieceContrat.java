/**
 * Deuxième approche d'une classe de test unitaire de la classe Piece.
 * Cette fois-ci les tests sont basés directement sur le contrat.
 *
 * <p>Pour chaque méthode XXX (et constructeur) de la classe à tester les méthodes suivantes doivent être définnies:
 * <ul>
 * 		<li><code>boolean testPreXXX()</code> pour tester les pré-conditions de la méthode</li>
 *  	<li><code>boolean testPostXXX()</code> pour tester les post-conditions de la méthode</li>
 *		<li><code>boolean testContratXXX()</code> appelant les deux méthodes précédentes ainsi que la
 *			méthode testInvariantPiece pour tester la satisfaction du contrat lors de l'exécution de la méthode à tester
 *			sur une instance de la classe et un jeu de paramètres</li>
 *		<li><code>boolean testNContratXXX()</code> crée un jeu de données (instances de Piece + plusieurs jeux de
 *			paramètres, et appelle la méthode testContratXXX pour tester la méthode sur le jeu de données créé</li>
 * </ul>
 * </p>
 *
 * @author Marc Champesme
 * @since 18 février 2007
 * @version 28 février 2010 (passage au codage UTF-8)
 * @version 7 octobre 2019
 */
import java.util.List;
import java.util.ArrayList;
import java.util.Random;

public class TestPieceContrat {
    public static void main(String[] args) {
        TestPiece tp = new TestPiece();
        boolean retVal;

        int nbErreurs = tp.testNContratRetirer();

        if (nbErreurs != 0) {
            System.out.println("Echec test contrat méthode retirer():" + nbErreurs + " violation(s) du contrat.");
        } else {
            System.out.println("Réussite test contrat méthode retirer()");
        }

    }

    private Random randomGenerator = new Random();

    /**
     * Crée nbObj/2 instances distinctes de ObjetZork et renvoie
     * une liste de taille nbObj consituée à partir des instances créées.
     *
     * @param nbObj taille de la liste renvoyée
     *
     * @return une nouvelle liste constituée de nbObj instances (non null)
     */
	public List<ObjetZork> creationObjetZorks(int nbObj) {
    	List<ObjetZork> resultat = new ArrayList<ObjetZork>(nbObj);
    	int nbDistinctObj = nbObj / 2;

    	for (int i = 0; i < nbDistinctObj; i++) {
    		resultat.add(new ObjetZork("objet" + i, 10 + i));
    	}

    	for (int i = nbDistinctObj; i < nbObj; i++) {
    		resultat.add(resultat.get(i - nbDistinctObj));
    	}

    	return resultat;
    }

    /**
     * Crée nbPieces instances distinctes de Piece et ajoute à chaque
     * piece un nombre tiré aléatoirement d'ObjetZork appartenant à
     * la liste spécifiée. Renvoie une liste consituée des instances de Piece créées.
     *
     * @param nbPieces nombre d'instances de Piece à créer
     * @param lOz liste des ObjetZork parmi lesquels choisir les objets à ajouter dans chaque piece
     *
     * @return liste des pieces créées.
     */
    public List<Piece> creationPieces(int nbPieces, List<ObjetZork> lOz) {
    	Collections.shuffle(lOz);
    	List<Piece> lPieces = new ArrayList<Piece>(nbPieces);

    	for (int i = 0; i < nbPieces; i++) {
    		Piece p = new Piece("piece" + i);
    		int nbOz = randomGenerator.nextInt(lOz.size());
    		// Ajout de nbOz objets à la pièce
    		for (int j = 0; j < nbOz; j++) {
    			p.ajouter(lOz.get(j));
    		}
    		lPieces.add(p);
    	}
    	return lPieces;
    }

    /**
     * Teste si le contrat de la méthode retirer est respecté sur plusieurs
     * instances de la classe Piece pour différents ObjetZork. Renvoie le nombre
     * de tests qui ont provoqué une violation du contrat (invariant ou post-conditions
     * uniquement).
     *
     * @return le nombre de tests qui ont provoqué une violation du contrat
     */
    public int testNContratRetirer() {
    	int nbEchecs = 0;
    	List<ObjetZork> lOz = creationObjetZorks(25);
    	Collections.shuffle(lOz);
    	List<Piece> lp = creationPieces(100, lOz);
    	int indexOz = 0;
    	System.out.print("P.retirer() [" + lp.size() + "]:");
    	for (Piece p : lp) {
    		ObjetZork oz = lOz.get(indexOz);

    		RetourTest retVal = testContratRetirer(p, oz);
    		switch(retVal) {
				case ERR_PRECONDITION: System.out.print("."); // Non testé
						break;
				case SUCCES: System.out.print("+"); // Succès
						break;
				default: System.out.print("E"); nbEchecs++; // Violation contrat
			}

			indexOz = (indexOz + 1) % lOz.size();
		}
		System.out.println("/");
		return nbEchecs;
    }

    /**
     * Teste si l'invariant de la classe Piece est vérifié pour l'argument spécifié.
     *
     * @requires p != null;
     *
     * @return true si l'invariant est satisfait; false sinon.
     */
    public boolean testInvariantPiece(Piece p) {
    	// l'invariant de la classe Piece est:
    	// @invariant descriptionCourte() != null;
    	// @invariant  getNbObjets() >= 0;
    	return (p.descriptionCourte() != null) && (p.getNbObjets() >= 0);
    }

    /**
     * Teste si le contrat de la méthode retirer de la classe Piece est vérifié
     * lorsque la méthode est appelée sur l'instance spécifiée avec pour argument l'ObjetZork
     * spécifié. Renvoie un code indiquant le résultat du test:
     * <ul>
     * 		<li> SUCCES en cas de succès</li>
     *		<li> ERR_PRECONDITION si le test n'a pas pu être effectué en raison d'une violation
     *			de précondition</li>
     *		<li> ERR_INVARIANT en cas de violation de l'invariant</li>
     *		<li> ERR_POSTCONDITION en cas de violation d'une postcondition</li>
     * </ul>
     *
     * @requires p != null;
     * @requires oz != null;
     * @ensures \result != null;
     *
     * @param p instance sur laquelle la méthode retirer doit être testée
     * @param oz paramètre utilisé pour le test
     *
     * @return SUCCES si le test a réussi; sinon un code indiquant la nature de l'échec
     */
	public RetourTest testContratRetirer(Piece p, ObjetZork oz) {
        // Test invariant avant exécution de la méthode:
		if (!testInvariantPiece(p)) {
			System.out.println("Piece.retirer(): Violation invariant avant execution pour Piece: " + p);
			return RetourTest.ERR_INVARIANT;
		}

        // Test des pré-conditions:
        if (!testPreRetirer(p, oz)) {
			return RetourTest.ERR_PRECONDITION;
		}

        // Sauvegarde des valeurs des expressions \old(...):
		int oldNbObjets = p.getNbObjets();
		boolean oldContient = p.contient(oz);
		int oldNboz = p.contientCombienDe(oz);

        // Exécution de la méthode à tester:
		boolean retVal = p.retirer(oz);

		// Test des post-conditions:
		if (!testPostRetirer(p, oz, retVal, oldNbObjets, oldContient, oldNboz)) {
			return RetourTest.ERR_POSTCONDITION;
		}

        // Test de l'invariant après exécution de la méthode:
        if (!testInvariantPiece(p)) {
			System.out.println("Piece.retirer(): Violation invariant après execution pour Piece: " + p);
			return RetourTest.ERR_INVARIANT;
		}

		return RetourTest.SUCCES;
	}

	/**
	 * Teste si les préconditions de la méthode retirer sont satisfaites
	 * (après exécution) pour l'instance de Piece et l'ObjetZork spécifié.
	 *
	 * @param p piece sur laquelle la méthode doit être testée
	 * @param oz paramètre avec lequel la méthode doit être testée
	 *
	 * @return true si les pré-conditions sont satisfaites ; false sinon.
	 */
    public boolean testPreRetirer(Piece p, ObjetZork oz) {
    	// Une seule pré-condition: oz != null
    	return oz != null;
    }

    /**
     * Teste si les post-conditions de la méthode retirer sont satisfaites
	 * (après exécution) pour l'instance de Piece et l'ObjetZork spécifié.
     *
     * @param p piece sur laquelle la méthode a été exécutée
     * @param oz argument utilisé lors de l'exécution
     * @param retVal valeur de retour après exécution
     * @param oldNbObjets nombre d'objetZork présents dans la piece avant exécution
     * @param oldContient indique si l'objetZork était présent dans la piece avant exécution
     * @param oldNboz nombre d'occurences de l'ObjetZork spécifié présents dans la piece avant exécution
     *
     */
    public boolean testPostRetirer(Piece p, ObjetZork oz, boolean retVal, int oldNbObjets, boolean oldContient, int oldNboz) {
    	// \result <==> (getNbObjets() == \old(getNbObjets()) - 1);
    	if (!(retVal == (p.getNbObjets() == (oldNbObjets -1)))) {
    		return false;
    	}

    	// !\result <==> (getNbObjets() == \old(getNbObjets()));
    	if (!(!retVal ==  (p.getNbObjets() == oldNbObjets))) {
    		return false;
    	}

    	// \old(contient(oz)) <==> \result;
    	if (!(retVal == oldContient)) {
    		return false;
    	}

    	// \old(contient(oz)) <==> (contientCombienDe(oz) == \old(contientCombienDe(oz)) - 1);
    	if (!(oldContient == (p.contientCombienDe(oz) == (oldNboz - 1)))) {
    		return false;
    	}

    	// !\old(contient(oz)) <==> (contientCombienDe(oz) == \old(contientCombienDe(oz)));
    	if (!(!oldContient == (p.contientCombienDe(oz) == oldNboz))) {
    		return false;
    	}

    	// \old(contientCombienDe(oz) == 1) ==> !contient(oz);
    	if (oldNboz == 1) {
    		if (p.contient(oz)) {
    			return false;
    		}
    	}

    	// \old(contientCombienDe(oz) > 1) <==> contient(oz);
    	if (!((oldNboz > 1) == p.contient(oz))) {
    		return false;
    	}
    	return true;
    }
}
