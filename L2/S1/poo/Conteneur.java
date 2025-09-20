import java.util.ArrayList;

/**
 * <p>
 * Implémentation d'un conteneur d'objets utilisant une <code>ArrayList</code> comme
 * structure de données. Les éléments contenus ne sont pas ordonnés et un
 * <code>ConteneurE</code> peut contenir plusieurs exemplaires d'un même objets (au sens de
 * equals). Un <code>ConteneurE</code> ne peut pas contenir la valeur <code>null</code>.
 * </p>
 *
 * <p>
 * Le bon fonctionnement de cette classe nécessite impérativement que les
 * éléments mémorisés ne soient pas modifiés durant l'utilisation du conteneur
 * (ce qui est le cas si ces éléments appartiennent à des classes non
 * modifiables/immutable) ou bien que la méthode <code>equals</code> utilisée pour comparer
 * les éléments entre eux n'ait pas été redéfinie (i.e. implémentation
 * équivalente à == comme dans la classe Object).
 * </p>
 *
 * @invariant getNbObjets() >= 0;
 * @invariant !contient(null);
 * @invariant estVide() <==> (getNbObjets() == 0);
 * @invariant (\forall E obj; ; contient(obj) <==> (contientCombienDe(obj) > 0));
 *
 * @see java.util.ArrayList
 *
 * @author Marc Champesme
 * @version 1 mars 2012
 * @since mars 2012
 */
public class Conteneur<E> implements Cloneable {
        /*@
	  @ invariant getNbObjets() >= 0;
	  @ invariant !contient(null);
	  @ invariant estVide() <==> (getNbObjets() == 0);
	  @ invariant (\forall E obj; ; contient(obj) <==> (contientCombienDe(obj) > 0));
        @*/
        private ArrayList<E> contenu;

        /**
         * Initialise un <code>ConteneurE</code> vide.
         *
         * @ensures estVide();
         */
        /*@
          @ ensures estVide();
        @*/
        public Conteneur() {
                contenu = new ArrayList<E>();
        }

        /**
         * Initialise un <code>ConteneurE</code> de même contenu que la
         * liste spécifiée. La liste spécifiée ainsi que tous ses éléments
         * doivent être non <code>null</code>.
         *
         * @requires liste != null;
         * @requires (\forall int i; i >= 0 && i < liste.size(); liste.get(i) != null);
         * @ensures getNbObjets() == liste.size();
         * @ensures (\forall int i; i >= 0 && i < liste.size(); contient(liste.get(i)));
         *
         * @param liste La liste contenant les éléments à placer dans ce
         *            <code>ConteneurE</code>.
         *
         */
        /*@
          @ requires liste != null;
          @ requires (\forall int i; i >= 0 && i < liste.size(); liste.get(i) != null);
          @ ensures getNbObjets() == liste.size();
          @ ensures (\forall int i; i >= 0 && i < liste.size(); contient(liste.get(i)));          
        @*/
        public Conteneur(ArrayList<E> liste) {
                this.contenu = new ArrayList<E>(liste);
        }

        /**
         * Initialise un <code>ConteneurE</code> contenant les
         * <code>nbObjets</code> premiers <code>E</code> du
         * tableau spécifié. Le tableau spécifiée doit être non <code>null</code>,
         * les <code>nbObjets</code> premiers éléments du tableau doivent être
         * non <code>null</code> et le nombre d'éléments spécifié doit être
         * supérieur ou égal à zéro et inférieur ou égal à la taille du tableau.
         *
         * @requires tab != null;
         * @requires (nbObjets >= 0) && (nbObjets <= tab.length);
         * @requires (\forall int i; i >= 0 && i < nbObjets; tab[i] != null);
         * @ensures getNbObjets() == nbObjets;
         * @ensures (\forall int i; i >= 0 && i < nbObjets; contient(tab[i]));
         *
         * @param tab Le tableau contenant les éléments à placer dans ce
         *            <code>ConteneurE</code>.
         * @param nbObjets Le nombre d'éléments du tableau à ajouter à ce
         *		<code>ConteneurE</code>.
         */
        /*@
          @ requires tab != null;
          @ requires (nbObjets >= 0) && (nbObjets <= tab.length);
          @ requires (\forall int i; i >= 0 && i < nbObjets; tab[i] != null);
          @ ensures getNbObjets() == nbObjets;
          @ ensures (\forall int i; i >= 0 && i < nbObjets; contient(tab[i]));          
        @*/
        public Conteneur(E[] tab, int nbObjets) {
                contenu = new ArrayList<E>(nbObjets);
                for (int i = 0; i < nbObjets; i++) {
                        contenu.add(tab[i]);
                }
        }
        /**
         * Ajoute l'objet specifié à ce <code>ConteneurE</code>. Si
         * l'objet est déjà présent, un exemplaire supplémentaire de cet objet
         * y est ajouté. La presence d'un objet est testée en utilisant la
         * methode <code>equals</code>. L'argument doit être non <code>null</code>.
         *
         * @requires obj != null;
         * @ensures contient(obj);
         * @ensures contientCombienDe(obj) == \old(contientCombienDe(obj)) + 1;
         *
         * @param obj  L'objet à ajouter dans ce conteneur
         *
         */
        /*@
          @ requires obj != null;
          @ ensures contient(obj);
          @ ensures contientCombienDe(obj) == \old(contientCombienDe(obj)) + 1;          
        @*/
        public void ajouter(E obj) {
                contenu.add(obj);
        }

        /**
         * <p>Ajoute <code>nCopies</code> exemplaires de l'objet specifié à ce
         * <code>ConteneurE</code>. Si l'objet est déjà présent, <code>nCopies</code>
         * exemplaires supplémentaires de cet objet sont ajoutés. La presence d'un
         * objet est testée en utilisant la methode <code>equals</code>.</p>
         * <p>
         * L'objet doit être non <code>null</code> et <code>nCopies</code> doit
         * être strictement positif.
         * </p>
         *
         * @requires nCopies > 0;
         * @requires obj != null;
         * @ensures contient(obj);
         * @ensures contientCombienDe(obj) == (\old(contientCombienDe(obj)) + nCopies);
         * @ensures getNbObjets() == (\old(getNbObjets()) + nCopies);
         *
         * @param obj L'objet à ajouter dans ce conteneur
         * @param nCopies Le nombre d'exemplaires de l'objet à ajouter à ce 
         *			<code>ConteneurE</code>.
         *
         */
        /*@
          @ requires nCopies > 0;
          @ requires obj != null;
          @ ensures contient(obj);
          @ ensures contientCombienDe(obj) == (\old(contientCombienDe(obj)) + nCopies);          
          @ ensures getNbObjets() == (\old(getNbObjets()) + nCopies);          
        @*/
        public void ajouter(E obj, int nCopies) {
                for (int i = 1; i <= nCopies; i++) {
                        contenu.add(obj);
                }
        }

        /**
         * Renvoie <code>true</code> si ce <code>ConteneurE</code> contient au moins un
         * exemplaire de l'objet specifié. La présence d'un objet est testée en
         * utilisant la méthode <code>equals</code>. Renvoie <code>false</code>
         * si l'argument est <code>null</code>.
         *
         * @ensures (obj == null) ==> !\result;
         * @ensures \result <==> contientCombienDe(obj) > 0;
         * @ensures estVide() ==> !\result;
         *
         * @param obj Objet dont on cherche à savoir s'il est present dans ce conteneur.
         * @return <code>true</code> si ce conteneur possede au moins un exemplaire de l'objet
         *         specifié ; <code>false</code> sinon.
         * @pure
         */
        /*@
          @ ensures (obj == null) ==> !\result;
          @ ensures \result <==> contientCombienDe(obj) > 0;          
          @ ensures estVide() ==> !\result;
          @ pure
        @*/
        public boolean contient(E obj) {
                return contenu.contains(obj);
        }

        /**
         * Renvoie le nombre d'exemplaires de l'objet spécifié présents dans ce
         * <code>ConteneurE</code>. La présence d'un objet est testée en utilisant la méthode
         * <code>equals</code>. Renvoie 0 si l'argument est <code>null</code>.
         *
         * @ensures \result >= 0;
         * @ensures (obj == null) ==> (\result == 0);
         * @ensures contient(obj) <==> (\result > 0);
         * @ensures !contient(obj) <==> (\result == 0);
         * @ensures \result <= getNbObjets();
         *
         * @param obj Objet dont on cherche à connaitre le nombre d'exemplaires.
         * @return le nombre d'exemplaires de l'objet specifié.
         *
         * @pure
         */
        /*@
          @ ensures \result >= 0;
          @ ensures (obj == null) ==> (\result == 0);          
          @ ensures contient(obj) <==> \result > 0;
          @ ensures !contient(obj) <==> \result == 0;
          @ ensures \result <= getNbObjets();
          @ pure
        @*/
        public int contientCombienDe(E obj) {
                int cpt = 0;
                for (E elt : contenu) {
                        if (elt.equals(obj)) {
                                cpt++;
                        }
                }
                return cpt;
        }

        /**
         * Renvoie <code>true</code> si ce <code>ConteneurE</code> ne contient aucun objet.
         *
         * @ensures \result <==> (getNbObjets() == 0);
         *
         * @return <code>true</code> si ce <code>ConteneurE</code> ne
         *		contient aucun objet ; <code>false</code> sinon.
         * @pure
         */
        /*@
          @ ensures \result <==> (getNbObjets() == 0);
          @ pure
        @*/
        public boolean estVide() {
                return contenu.isEmpty();
        }

        /**
         * Renvoie le nombre d'objets présents dans ce <code>ConteneurE</code>. Chaque occurence de chaque
         * objet est comptée.
         *
         * @ensures \result >= 0;
         *
         * @return Le nombre d'objets dans ce <code>ConteneurE</code>.
         *
         * @pure
         */
        /*@
          @ ensures \result >= 0;
          @ pure
        @*/
        public int getNbObjets() {
                return contenu.size();
        }

        /**
         * Retire un exemplaire de l'objet specifié de ce <code>ConteneurE</code> si cet objet y
         * est présent. Renvoie <code>true</code> si cet objet était effectivement présent dans
         * ce conteneur et que l'objet a pu être effectivement retiré ; renvoie
         * <code>false</code> sinon. La présence d'un objet est testée en utilisant la méthode
         * <code>equals</code>. Renvoie <code>false</code> si l'argument est <code>null</code>.
         *
         * @ensures (obj == null) ==> !\result;
         * @ensures \old(contient(obj)) <==> \result;
         * @ensures \old(contient(obj))
         * 		<==> (contientCombienDe(obj)
         *			== \old(contientCombienDe(obj)) - 1);
         * @ensures \old(contientCombienDe(obj) <= 1) <==> !contient(obj);
         * @ensures \old(contientCombienDe(obj) > 1) <==> contient(obj);
         *
         * @param obj Objet dont un exemplaire doit être retirer de ce conteneur
         * @return <code>true</code> si cet objet était effectivement présent ; <code>false</code> sinon.
         */
        /*@
          @ ensures (obj == null) ==> !\result;
          @ ensures \old(contient(obj)) <==> \result;         
          @ ensures \old(contient(obj)) 
          @		<==> (contientCombienDe(obj)
          @			== \old(contientCombienDe(obj)) - 1);
          @ ensures \old(contientCombienDe(obj) <= 1) <==> !contient(obj);
          @ ensures \old(contientCombienDe(obj) > 1) <==> contient(obj);
        @*/
        public boolean retirer(E obj) {
        	return (retirer(obj, 1) == 1);
        }

        /**
         * Retire de la ArrayList, l'élément présent à l'index spécifié en le
         * remplaçant par le dernier élement. Cette opération s'effectue en temps
         * constant mais ne préserve pas l'ordre des éléments.
         */
        /*@
          @ requires (index >= 0) && (index < contenu.size());
          @ ensures contenu.size() == (\old(contenu.size()) - 1);
          @ ensures (index < contenu.size())
          @	==> (contenu.get(index) == \old(contenu.get(contenu.size() - 1)));
        @*/
        private void fastRemove(int index) {
                int lastIndex = contenu.size() - 1;
                contenu.set(index, contenu.get(lastIndex));
                contenu.remove(lastIndex);
        }

        /**
         * Retire <code>nCopies</code> exemplaires de l'objet spécifié de ce
         * <code>ConteneurE</code> si cet objet y est present. Renvoie le nombre d'exemplaires de
         * l'objet effectivement retirés. La présence d'un objet est testée en
         * utilisant la méthode <code>equals</code>. Renvoie 0 si l'argument est
         * <code>null</code>
         * ou si <code>nCopies</code> est égal à 0. <code>nCopies</code> doit
         * être supérieur ou égal à 0.
         *
         * @requires nCopies >= 0;
         * @ensures ((obj == null) || (nCopies == 0)) ==> (\result == 0);
         * @ensures (\old(contient(obj)) && (nCopies > 0)) <==> (\result > 0);
         * @ensures \result == (\old(contientCombienDe(obj)) - contientCombienDe(obj));
         * @ensures contientCombienDe(obj)
         *		== Math.max(0, \old(contientCombienDe(obj)) - nCopies);
         * @ensures \old(contientCombienDe(obj) <= nCopies) ==> !contient(obj);
         * @ensures \old(contientCombienDe(obj) > nCopies) <==> contient(obj);
         *
         * @param obj Objet dont des exemplaires doivent être retirés de ce conteneur
         * @param nCopies Nombre d'exemplaires de l'objet spécifié à retirer de ce
         *            conteneur.
         * @return Le nombre d'exemplaires de l'objet effectivement retirés de ce
         *         <code>ConteneurE</code>.
         */
        /*@
          @ requires nCopies >= 0;
          @ ensures ((obj == null) || (nCopies == 0)) ==> (\result == 0);
          @ ensures (\old(contient(obj)) && (nCopies > 0)) <==> (\result > 0);
          @ ensures \result == (\old(contientCombienDe(obj)) - contientCombienDe(obj));
          @ ensures contientCombienDe(obj) 
          @		== Math.max(0, \old(contientCombienDe(obj)) - nCopies);
          @ ensures \old(contientCombienDe(obj) <= nCopies) <==> !contient(obj);
          @ ensures \old(contientCombienDe(obj) > nCopies) <==> contient(obj);
        @*/
        public int retirer(Object obj, int nCopies) {
                if (obj == null || nCopies == 0) {
                        return 0;
                }
                int nbRetraits = 0;
                int i = 0;
                while ((i < contenu.size()) && (nbRetraits < nCopies)) {
                        if (contenu.get(i).equals(obj)) {
                                fastRemove(i);
                                nbRetraits++;
                        } else {
                        	i++;
                        }
                }

                return nbRetraits;
        }

        /**
         * Retire tous les exemplaires de l'objet specifié de ce
         * <code>ConteneurE</code> si cet objet y est présent. Renvoie le nombre d'exemplaires de
         * l'objet effectivement retirés. La présence d'un objet est testée en
         * utilisant la méthode <code>equals</code>.
         *
         * @ensures !contient(obj);
         * @ensures (obj == null) ==> (\result == 0);
         * @ensures \old(contient(obj)) <==> (\result > 0);
         * @ensures \result == \old(contientCombienDe(obj));
         *
         * @param obj Objet dont tous les exemplaires doivent être retirés de ce conteneur
         * @return Le nombre d'exemplaires de l'objet effectivement retirés de ce
         *         <code>ConteneurE</code>.
         */
        /*@
          @ ensures !contient(obj);
          @ ensures (obj == null) ==> (\result == 0);
          @ ensures \old(contient(obj)) <==> (\result > 0);
          @ ensures \result == \old(contientCombienDe(obj));
        @*/
        public int retirerTout(Object obj) {
        	return retirer(obj, getNbObjets());
        }

        /**
         * Renvoie une nouvelle instance de tableau contenant tous les objets
         * présents dans ce <code>ConteneurE</code>. Le tableau renvoyé
         * contient, pour chaque objet, autant d'exemplaires de cet objet que ce
         * <code>ConteneurE</code> en contient. La taille du tableau
         * renvoyé est identique au nombre d'objets présents dans ce
         * <code>ConteneurE</code>.
         *
         * <p>L'ordre dans lequel les objets sont placés dans le tableau n'est
         * pas significatif: lorsque des opérations modifiant les objets
         * présents dans ce <code>ConteneurE</code> surviennent, il n'est pas garanti que
         * plusieurs appels successifs à cette méthode renvoyent les objets dans
         * le  même ordre, y compris pour ce qui est des objets non concernés
         * par ces modifications. Cependant, si, entre deux appels à cette
         * méthode, aucune modification n'est intervenue sur les objets
         * présents dans ce <code>ConteneurE</code>, il est garanti que les objets sont
         * renvoyés dans le même ordre.</p>
         *
         * @ensures \result != null;
         * @ensures \result.length == getNbObjets();
         * @ensures (\forall int i; i >= 0 && i < getNbObjets();
         *		(\result[i] != null)
         *		&& contient(\result[i])
         *		&& (contientCombienDe(\result[i])
         *	    		== (\num_of int j; j >= 0 && j < getNbObjets();
         *				\result[i].equals(\result[j]))));
         *
         * @return Un tableau contenant tous les objets présents dans ce
         * <code>ConteneurE</code>.
         *
         * @pure
         */
        /*@
          @ ensures \result != null;
          @ ensures \result.length == getNbObjets();
          @ ensures (\forall int i; i >= 0 && i < getNbObjets();
          @		(\result[i] != null)
          @		&& contient(\result[i])
          @		&& (contientCombienDe(\result[i])
          @	    		== (\num_of int j; j >= 0 && j < getNbObjets();
          @				\result[i].equals(\result[j]))));
          @ pure 
        @*/
        @SuppressWarnings("unchecked")
        public E[] getTabObjets() {
                return (E[]) this.contenu.toArray();
        }

        /**
         * Retire de ce <code>ConteneurE</code> tous les objets qu'il contient.
         *
         * @ensures estVide();
         *
         */
         
        /*@
          @ ensures estVide();
        @*/
        public void vider() {
                contenu.clear();
        }

        /**
         * Teste si l'objet spécifié est <code>equals</code> à ce <code>ConteneurE</code>. Pour qu'il y ait
         * égalité entre ce conteneur et l'objet spécifié, il est nécessaire
         * que l'objet spécifié soit un <code>ConteneurE</code>
         * contenant les mêmes objets en autant d'exemplaires que ce
         * <code>ConteneurE</code>.
         *
         *
         * @ensures !(o instanceof ConteneurE) ==> !\result;
         * @ensures (o instanceof ConteneurE)
         *	==> (\result <==>
         *		(\forall E oz; this.contient(oz);
         *		    this.contientCombienDe(oz)
         *		    == ((ConteneurE) o).contientCombienDe(oz))
         *	    );
         * @ensures \result ==> (this.hashCode() == o.hashCode());
         *
         * @param o L'objet à comparer à ce <code>ConteneurE</code>
         * @return <code>false</code> si l'objet spécifié n'est pas un
         *	<code>ConteneurE</code> ou bien est un
         *      <code>ConteneurE</code> ne contenant pas les mêmes objets en autant
         *      d'exemplaires ; <code>true</code> si et seulement si
         *      l'objet spécifié est un <code>ConteneurE</code>
         *	contenant les mêmes objets en autant d'exemplaires.
         *
         * @pure
         *
         * @see Object#equals(Object)
         */
        /*@
          @ ensures !(o instanceof ConteneurE) ==> !\result;
          @ ensures (o instanceof ConteneurE)
          @	==> (\result <==>
          @		(\forall E oz; this.contient(oz);
          @		  this.contientCombienDe(oz)
          @		  == ((ConteneurE) o).contientCombienDe(oz))
          @	     );
          @ ensures \result ==> (this.hashCode() == o.hashCode());
          @ pure 
        @*/
        public boolean equals(Object o) {
                if (! (o instanceof Conteneur<?>)) {
                        return false;
                }
                
                Conteneur<?> c = (Conteneur<?>) o;
                if (this.getNbObjets() != c.getNbObjets()) {
                        return false;
                }
                Conteneur<E> thisClone = (Conteneur<E>) this.clone();
                Conteneur<?> otherClone = (Conteneur<?>) c.clone();
                while (!thisClone.estVide()) {
                	E elt = thisClone.contenu.get(0);
                        if (thisClone.retirerTout(elt) != otherClone.retirerTout(elt)) {
                                return false;
                        }
                }
                return otherClone.estVide();
        }

        /**
         * Renvoie un clone de ce <code>ConteneurE</code>.
         * L'implémentation fournie par cette classe respecte le contrat défini
         * dans la classe <code>Object</code> relativement à l'implémentation 
         * de <code>equals</code> fournie par cette classe.
         *
         * @return Un clone de ce conteneur.
         *
         * @ensures \result != null;
         * @ensures \result != this;
         * @ensures this.equals(\result);
         *
         * @pure
         */
        /*@
          @ ensures \result != null;
          @ ensures \result != this;
          @ ensures this.equals(\result);
          @ pure 
        @*/
        @SuppressWarnings("unchecked")
        public Conteneur<E> clone() {
                Conteneur<E> leClone = null;
                try {
                        leClone = (Conteneur<E>) super.clone();
                } catch (CloneNotSupportedException e) {
                        throw new InternalError("Ne devrait pas se produire");
                }
                // Unchecked cast inévitable:
                leClone.contenu = (ArrayList<E>) new ArrayList<E>(contenu);

                return leClone;
        }

        /**
         * Renvoie un code de hashage pour ce <code>ConteneurE</code>.
         * L'implémentation fournie par cette classe respecte le contrat défini
         * dans la classe <code>Object</code> relativement à l'implémentation 
         * de <code>equals</code> fournie par cette classe.
         *
         * @return Un code de hashage pour ce <code>ConteneurE</code>.
         *
         * @pure
         */
        //@ pure
        public int hashCode() {
                int code = 0;
                for (E elt : contenu) {
                        code += elt.hashCode();
                }
                return code;
        }

        /**
         * Renvoie une représentation succincte de ce <code>ConteneurE</code>
         * sous forme de chaîne de caractères.
         *
         * @ensures \result != null;
         *
         * @return Une représentation succincte de ce <code>ConteneurE</code>
         *
         * @pure
         */
        /*@ 
          @ ensures \result != null;
          @ pure
          @*/
        public String toString() {
                return "ConteneurE:" + contenu.toString();
        }
}
