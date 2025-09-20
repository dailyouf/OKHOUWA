
/**
 * Première approche (à compléter) d'une classe de tests unitaires pour la classe Piece.
 * 
 * <p>Pour chaque méthode (et constructeur) de la classe à tester une méthode <code>boolean testXXX()</code>
 * doit être définnie
 * (i.e. une méthode <code>boolean testRetirer()</code> correspond à la 
 * méthode <code>retirer</code> ...). Chacune de ces méthodes:
 * <ul>
 *      <li>crée et initialise les instances nécessaires aux tests de 
 *      cette méthode (i.e. les données de test).</li>
 *      <li>exécute la méthode à tester pour chaque instance et les différents 
 *		paramètres disponibles</li>
 *      <li>vérifie que les résultats prévus sont bien obtenus, affiche 
 *      un message d'erreur et renvoye la valeur <code>false</code> en 
 *      cas d'erreur, renvoye la valeur <code>true</code> sinon.
 * </ul></p>
 * <p>A titre d'illustration, la version de cette classe téléchargeable depuis l'ENT possède
 * une méthode testRetirer() permettant de tester partiellement la méthode retirer
 * 
 * @author Marc Champesme 
 * @since 18 février 2007
 * @version 28 février 2010 (passage au codage UTF-8)
 * @version 7 octobre 2019
 */

public class TestPieceSimple {
    public static void main(String[] args) {
        TestPiece tp = new TestPiece();
        boolean retVal;
        
        // Tests
        retVal = tp.testRetirer();
        
        if (!retVal) {
            System.out.println("Echec test méthode retirer()");
        } else {
            System.out.println("Réussite test méthode retirer()");
        }        
    }

    /**
     * Test de la méthode retirer.
     * 
     * @return <code>false</code> en cas d'erreur, <code>true</code> sinon
     */
    public boolean testRetirer() {
        boolean reussite = true;
        boolean retVal;
        
        // Création et initialisation des données tests
        Piece p1 = new Piece("Chambre");        
        Piece p2 = new Piece("Cuisine");
        Piece p3 = new Piece("Salon");
        ObjetZork oz1 = new ObjetZork("Parchemin", 1);
        ObjetZork oz2 = new ObjetZork("Tapis", 10);
        ObjetZork oz3 = new ObjetZork("Tapis", 10);
        ObjetZork oz4 = new ObjetZork("Tapis", 10);
        ObjetZork oz5 = new ObjetZork("Vase", 5);  
        
        p2.ajouter(oz1);
        p3.ajouter(oz2);        
        p3.ajouter(oz3);
        p3.ajouter(oz4);        
        
        // execution retirer
        retVal = p1.retirer(oz5);
        
        // Tests post exec
        if (retVal) {
            System.out.println(p1 + ":valeur de retour devrait etre false");
            reussite = false;
        }
        if (p1.getNbObjets() != 0) {
            System.out.println(p1 + ":nb objets devrait etre 0");
            reussite = false;
        }
        if (p1.contientCombienDe(oz5) != 0) {
            System.out.println(p1 + ":devrait contenir 0" + oz5);
            reussite = false;
        }
        if (p1.contient(oz5)) {
            System.out.println(p1 + ":ne devrait pas contenir" + oz5);
            reussite = false;
        }

        // execution retirer
        retVal = p2.retirer(oz1);
        
        // Tests post exec
        if (!retVal) {
            System.out.println(p2 + ":valeur de retour devrait etre true");
            reussite = false;
        }
        if (p2.getNbObjets() != 0) {
            System.out.println(p2 + ":nb objets devrait etre 0");
            reussite = false;
        }
        if (p2.contientCombienDe(oz1) != 0) {
            System.out.println(p2 + ":devrait contenir 0" + oz1);
            reussite = false;
        }
        if (p2.contient(oz1)) {
            System.out.println(p2 + ":ne devrait pas contenir" + oz1);
            reussite = false;
        }        
        
        // execution retirer
        retVal = p3.retirer(oz3);
        
        // Tests post exec
        if (!retVal) {
            System.out.println(p3 + ":valeur de retour devrait etre true");
            reussite = false;
        }
        if (p3.getNbObjets() != 2) {
            System.out.println(p2 + ":nb objets devrait etre 2");
            reussite = false;
        }
        if (p3.contientCombienDe(oz3) != 2) {
            System.out.println(p3 + ":devrait contenir 2" + oz3);
            reussite = false;
        }
        if (!p3.contient(oz3)) {
            System.out.println(p3 + ":devrait contenir" + oz3);
            reussite = false;
        }                
        return reussite;
    }
}
