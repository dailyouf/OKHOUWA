/**
 * @author Youcef GHEDAMSI 12302243
 * Je déclare qu'il s'agit de mon propre travail
 */
 
 package minebayd1;

 import java.util.ArrayList;
 import java.util.Optional;
 
 import static minebayd1.Category.*;
 
 /**
  * Gestion d'une liste de ClassifiedAd triée selon la date de création (de la
  * plus récente à la plus ancienne). Une CategorizedAdList ne peut pas contenir
  * d'éléments dupliqués, plus formelement, pour tout couple d'entiers (i, j)
  * tels que: <br/>
  * i >= 0 && j >= 0 && i != j && i < size() && j < size() on a
  * !get(i).equals(get(j)). Une CategorizedAdList prend en compte les catégoriesjava
  * des annonces en permettant:
  * <ul>
  * <li>soit un parcours des annonces de toutes les catégories</li>
  * <li>soit un parcours des seules annonces d'une catégorie sélectionnée</li>
  * </ul>
  * Dans ce but, CategorizedAdList utilise une liste distincte (une ArrayList)
  * pour chaque catégorie. Les méthodes selectCategory, getSelectedCategory et
  * clearCatégory permettent de sélectionner ou déselectionner une catégorie
  * particulière. Lorsqu'une catégorie est sélectionnée, toutes les opérations
  * relatives aux itérations (startIteration, next, previous, ...) agissent
  * uniquement sur les annonces de cette catégorie.
  * 
  * Pour les autres méthodes, celles possédant un paramètre de type Category
  * agissent uniquement sur cette catégorie, les autres méthodes agissant sur
  * toutes les annonces.
  * 
  * Les méthodes modifiant le contenu de cette liste (add et remove), entraine
  * une réinitialisation de l'itération en cours (même effet qu'un appel à la
  * méthode startIteration).
  * 
  * @invariant \var Optional&lt;Category&gt; optCat = getSelectedCategory();
  * @invariant getSelectedCategory() != null;
  * @invariant (\forall int i, j; i >= 0 && i < j && j < size();
  *            get(i).isAfter(get(j)));
  * @invariant (\forall Category cat;true; <br/>
  *            (\forall int i, j; i >= 0 && i < j && j < size(cat); <br/>
  *            get(cat, i).isAfter(get(cat, j))));
  * @invariant size() == (\sum Category cat;true;size(cat));
  * @invariant nextIndex() >= 0 && previousIndex() >= -1;
  * @invariant nextIndex() <= size();
  * @invariant previousIndex() < size();
  * @invariant optCat.isPresent() ==> nextIndex() <= size(optCat.get());
  * @invariant optCat.isPresent() ==> previousIndex() < size(optCat.get());
  * @invariant nextIndex() == previousIndex() + 1;
  * @invariant lastIndex() == nextIndex() || lastIndex() == previousIndex();
  * @invariant !hasPrevious() <==> previousIndex() == -1;
  * @invariant optCat.isEmpty()	 ==> (!hasNext() <==> nextIndex() == size());
  * @invariant optCat.isPresent() ==> <br/>
  *            (!hasNext() <==> nextIndex() == size(optCat.get()));
  * @invariant !contains(null);
  * @invariant (\forall int i, j; i >= 0 && i < j && j < size();
  *            !get(i).equals(get(j)));
  * 
  * @author Marc Champesme
  * @since 27/09/2024
  * @version 20/10/2024
  */
 public class CategorizedAdList implements Cloneable {
     
     private ArrayList<ClassifiedAd> clothes, shoes, books, games, computers;
     
     private Optional<ArrayList<ClassifiedAd>> selectedCat;
     
     private ClassifiedAd index;
     
     private int lastCalled;
     
     
     /**
      * Initialise une nouvelle instance ne contenant aucune annonce.
      * 
      * @ensures size() == 0;
      * @ensures SelectedCategory() != null;
      * @ensures getSelectedCategory().isEmpty();
      * @ensures !hasPrevious();
      * @ensures !hasNext();
      * @ensures previousIndex() == -1;
      * @ensures nextIndex() == 0;
      * @ensures lastIndex() == -1;
      */
     public CategorizedAdList() {
         
         clothes = new ArrayList<ClassifiedAd>();
         shoes  = new ArrayList<ClassifiedAd>();
         books = new ArrayList<ClassifiedAd>();
         games = new ArrayList<ClassifiedAd>();
         computers = new ArrayList<ClassifiedAd>();
         
         selectedCat = Optional.empty();
         
         index = null;
         
         clearSelectedCategory();
         
     }
 
     /**
      * Sélectionne la catégorie sur laquelle sera effectuée la prochaine itération.
      * Effectue les initialisations nécessaire pour démarrer une nouvelle itération
      * de la même manière qu'un appel à startIteration().
      * 
      * @param cat la catégorie d'annonce à sélectionner
      * 
      * @requires cat != null;
      * @ensures getSelectedCategory().isPresent();
      * @ensures getSelectedCategory().get().equals(cat);
      * @ensures !hasPrevious();
      * @ensures previousIndex() == -1;
      * @ensures nextIndex() == 0;
      * @ensures lastIndex() == -1;
      */
     public void selectCategory(Category cat) {
     
         clearSelectedCategory();
         
         switch (cat) {
             
             case CLOTHES:
                 selectedCat = Optional.of(clothes);
                 break;	
                 
             case SHOES:
                 selectedCat = Optional.of(shoes);
                 break;	
                 
             case BOOKS:
                 selectedCat = Optional.of(books);
                 break;	
                 
             case GAMES:
                 selectedCat = Optional.of(games);	
                 break;
         
             case COMPUTERS:
                 selectedCat = Optional.of(computers);	
                 break;
             
         }
         
     }
 
     /**
      * Renvoie un Optional pour la catégorie sélectionnée. Si une catégorie a été
      * sélectionnée \result.isPresent() est true; sinon \result.isEmpty() est true.
      * 
      * @return un Optional pour la catégorie sélectionnée
      * 
      * @ensures \result != null;
      * 
      * @pure
      */
     public Optional<Category> getSelectedCategory() {
         
         Optional<Category> tmp = Optional.empty();
         
         if (selectedCat.isPresent()) {
             
             if (selectedCat.get() == clothes) {
                 tmp = Optional.of(Category.CLOTHES);	
             }
             
             if (selectedCat.get() == shoes) {
                 tmp = Optional.of(Category.SHOES);	
             }
             
             if (selectedCat.get() == books) {
                 tmp = Optional.of(Category.BOOKS);	
             }
             
             if (selectedCat.get() == games) {
                 tmp = Optional.of(Category.GAMES);	
             }
             
             if (selectedCat.get() == computers) {
                 tmp = Optional.of(Category.COMPUTERS);	
             }
 
         }
         
         return tmp;
     }
 
     /**
      * Déselectionne la catégorie sélectionnée et effectue les initialisations
      * nécessaire pour démarrer une nouvelle itération (cf.startIteration()). Si
      * aucune catégorie n'était sélectionnée l'appel à cette méthode est équivalent
      * à un appel à startIteration.
      * 
      * @ensures getSelectedCategory().isEmpty();
      * @ensures !hasPrevious();
      * @ensures previousIndex() == -1;
      * @ensures nextIndex() == 0;
      * @ensures lastIndex() == -1;
      */
     public void clearSelectedCategory() {
     
         selectedCat = Optional.empty();
         
         startIteration();
     
     }
 
     /**
      * Initialise cette liste pour le démarrage d'une nouvelle itération sur les
      * annonces de cette liste. Cette itération s'effectue à partir de l'annonce la
      * plus récente, de sorte que chaque appel à next() renvoie une annonce plus
      * ancienne.
      * 
      * Si une catégorie est sélectionnée, l'itération ne concernera que les annonces
      * de cette catégorie; sinon l'itération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @ensures !hasPrevious();
      * @ensures previousIndex() == -1;
      * @ensures nextIndex() == 0;
      * @ensures lastIndex() == -1;
      */
     public void startIteration() {
         
         lastCalled = 0;
         
         index = null;
         
         
     }
 

     /**
      * Renvoie true si cette liste possède une annonce plus ancienne pour
      * l'itération en cours.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return true si cette liste possède une annonce plus ancienne pour
      *         l'itération en cours
      * 
      * @ensures \var Optional&lt;Category&gt; optCat = getSelectedCategory();
      * @ensures optCat.isEmpty() ==> (\result <==> nextIndex() < size());
      * @ensures optCat.isEmpty() ==> (!\result <==> nextIndex() == size());
      * @ensures optCat.isPresent() ==> (\result <==> nextIndex() <
      *          size(optCat.get()));
      * @ensures optCat.isPresent() ==> (!\result <==> nextIndex() ==
      *          size(optCat.get()));
      * 
      * @pure
      */
     public boolean hasNext() {

        if (index == null ){
            if (selectedCat.isPresent()) {
                return !selectedCat.get().isEmpty();
            }
            else {
                return !clothes.isEmpty() || !shoes.isEmpty() || !books.isEmpty() || !games.isEmpty() || !computers.isEmpty(); 
            }
        }

        if (selectedCat.isPresent()) {
        
             if (selectedCat.get().size() == 0 ) {
                 return false;
             }
             
       	     return selectedCat.get().get(selectedCat.get().size() - 1).isBefore(index);
        }
         
        else {
             if (clothes.size() != 0 && (clothes.get(clothes.size() - 1).isBefore(index))){
                 return true;
             }
             
             if (shoes.size() != 0 && (shoes.get(shoes.size() - 1).isBefore(index))) {
                 return true;
             }
             
             if (books.size() != 0 && (books.get(books.size() - 1).isBefore(index))) {
                 return true;
             }
             
             if (games.size() != 0 && (games.get(games.size() - 1).isBefore(index))) {
                 return true;
             }
             
             if (computers.size() != 0 && (computers.get(computers.size() - 1).isBefore(index))) {
                 return true;
             }
             
             return false;
             
        }
     }
 
     /**
      * Renvoie l'annonce suivante (plus ancienne) dans l'itération en cours et
      * avance d'un élément dans l'itération.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return l'annonce suivante (plus ancienne) dans l'itération en cours
      * 
      * @requires hasNext();
      * @ensures \var Optional&lt;Category&gt; optCat = getSelectedCategory();
      * @ensures \result != null;
      * @ensures optCat.isEmpty() ==> \result.equals(\old(get(nextIndex())));
      * @ensures optCat.isPresent() ==> \result.equals(\old(get(optCat.get(),
      *          nextIndex())));
      * @ensures optCat.isPresent() ==> \result.getCategory().equals(optCat.get());
      * @ensures nextIndex() == \old(nextIndex()) + 1;
      * @ensures previousIndex() == \old(previousIndex()) + 1;
      * @ensures previousIndex() == \old(nextIndex());
      * @ensures lastIndex() == \old(nextIndex());
      * @ensures lastIndex() == previousIndex();
      */
     public ClassifiedAd next() {
         
         ClassifiedAd next = null;
         
         lastCalled = 1;

         if (index == null) {
            if (selectedCat.isPresent() && !selectedCat.get().isEmpty()) {
                index = selectedCat.get().get(0);
            }
            
            else {
        
                index = clothes.isEmpty() ? null : clothes.get(0);
                
                if ((index == null) || (!shoes.isEmpty() && index.isBefore(shoes.get(0)))) {
                    index = shoes.isEmpty() ? null : shoes.get(0);
                }
                
                if ((index == null) || (!books.isEmpty() && index.isBefore(books.get(0)))) {
                    index = books.isEmpty() ? null : books.get(0);
                }
                
                if ((index == null) || (!games.isEmpty() && index.isBefore(games.get(0)))) {
                    index = games.isEmpty() ? null : games.get(0);
                }
                
                if ((index == null) || (!computers.isEmpty() && index.isBefore(computers.get(0)))) {
                    index = computers.isEmpty() ? null : computers.get(0);
                }
                
            }
            
            return index;
        }


         if (selectedCat.isPresent()) {
             next = selectedCat.get().get(selectedCat.get().indexOf(index) + 1);
         }
         
         else {
         
             int i;
             
                 ClassifiedAd pClothes = clothes.isEmpty() ? null : clothes.get(0);
             if (pClothes != null) {
                 i=0;
                 while ((i < clothes.size()) && (index.isBefore(pClothes) || (index == pClothes))) {
                     pClothes = clothes.get(i++);
                 }
             }
             
                 ClassifiedAd pShoes = shoes.isEmpty() ? null : shoes.get(0);
                 if (pShoes != null) {
                 i=0;
                 while ((i < shoes.size()) && (index.isBefore(pShoes) || (index == pShoes))) {
                     pShoes = shoes.get(i++);
                 }
             }
             
                 ClassifiedAd pBooks = books.isEmpty() ? null : books.get(0);
                 if (pBooks != null) {
                 i=0;
                 while ((i < books.size()) && (index.isBefore(pBooks) || (index == pBooks))) {
                     pBooks = books.get(i++);
                 }
             }
             
                 ClassifiedAd pGames = games.isEmpty() ? null : games.get(0);
                 if (pGames != null) {
                 i=0;
                 while ((i < games.size()) && (index.isBefore(pGames) || (index == pGames))) {
                     pGames = games.get(i++);
                 }
             }
             
                    ClassifiedAd pComputers = computers.isEmpty() ? null : computers.get(0);
             if (pComputers != null) {
                 i=0;
                 while ((i < computers.size()) && (index.isBefore(pComputers) || (index == pComputers))) {
                     pComputers = computers.get(i++);
                 }
                 
             }
             
             if (pClothes != null) {
                 next = (pClothes.isBefore(index)) ? pClothes : null;			
             }
             
             if (pShoes != null) {
                 if ((next==null || next.isBefore(pShoes)) && (pShoes.isBefore(index))) {
                     next = pShoes;
                 }
             }
             
             if (pBooks != null) {
                 if ((next==null || next.isBefore(pBooks)) && (pBooks.isBefore(index))){
                     next = pBooks;
                 }
             }
             
             if (pGames != null) {
                 if ((next==null || next.isBefore(pGames)) && (pGames.isBefore(index))){
                     next = pGames;
                 }
             }
         
             if (pComputers != null) {
                 if ((next==null || next.isBefore(pComputers)) && (pComputers.isBefore(index))){
                     next = pComputers;
                 }
             }
 
         }
                     
         index = next;
         return next;
             
     }
 
     /**
      * Renvoie l'index de l'annonce qui sera renvoyée par le prochain appel à
      * next(). Si l'itération est arrivée à la fin la valeur renvoyée est size() (ou
      * size(getSelectedCategory().get()) si une catégorie est sélectionnée).
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return l'index de l'annonce qui sera renvoyé par le prochain appel à next();
      *         ou size() s'il n'y a pas d'élément suivant
      * 
      * @ensures \var Optional&lt;Category&gt; optCat = getSelectedCategory();
      * @ensures optCat.isEmpty() ==> (\result == size() <==> !hasNext());
      * @ensures optCat.isPresent() ==> (\result == size(optCat.get()) <==>
      *          !hasNext());
      * @ensures optCat.isEmpty() ==> (hasNext() <==> \result >= 0 && \result <
      *          size());
      * @ensures optCat.isPresent() ==> (hasNext() <==> \result >= 0 && \result <
      *          size(optCat.get()));
      * 
      * @pure
      */
     public int nextIndex() {
         
        if (index == null) {
            return 0;
        }

         if (selectedCat.isPresent()) {

            if (selectedCat.get().isEmpty()) {
                return size(getSelectedCategory().get());
            }

             return selectedCat.get().indexOf(index) + 1;
         }
     
         if (!hasNext()) {
             return clothes.size() + shoes.size() + books.size() + games.size() + computers.size();	
         }
         
         int iClothes=0, iShoes=0, iBooks=0, iGames=0, iComputers=0;
    	
    	 ClassifiedAd pClothes = clothes.isEmpty() ? null : clothes.get(0);     
         if (pClothes != null) {
             while ((iClothes < clothes.size() - 1) && (index.isBefore(pClothes) || (index.equals(pClothes)))) {
                 pClothes = clothes.get(++iClothes);
             }
             
             if (index.isBefore(pClothes) || (index.equals(pClothes))) {
                 ++iClothes;
             }
         }
             
         ClassifiedAd pShoes = shoes.isEmpty() ? null : shoes.get(0);
         if (pShoes != null) {
             while ((iShoes < shoes.size() - 1) && (index.isBefore(pShoes) || (index.equals(pShoes)))) {
                 pShoes = shoes.get(++iShoes);
             }
             
             if (index.isBefore(pShoes) || (index.equals(pShoes))) {
                 ++iShoes;	
             }
         }
             
         ClassifiedAd pBooks = books.isEmpty() ? null : books.get(0);
         if (pBooks != null) {
             while ((iBooks < books.size() - 1) && (index.isBefore(pBooks) || (index.equals(pBooks)))) {
                 pBooks = books.get(++iBooks);
             }
             
             if (index.isBefore(pBooks) || (index.equals(pBooks))) {
                 ++iBooks;	
             }
         }
             
         ClassifiedAd pGames = games.isEmpty() ? null : games.get(0);
         if (pGames != null) {
             while ((iGames < games.size() - 1) && (index.isBefore(pGames) || (index.equals(pGames)))) {
                 pGames = games.get(++iGames);
             }
             if (index.isBefore(pGames) || (index.equals(pGames))) { 
                 ++iGames;
             }	
         }
             
         ClassifiedAd pComputers = computers.isEmpty() ? null : computers.get(0);
         if (pComputers != null) {
             while ((iComputers < computers.size() - 1) && (index.isBefore(pComputers) || (index.equals(pComputers)))) {
                 pComputers = computers.get(++iComputers);
             }
             if (index.isBefore(pComputers) || (index.equals(pComputers))) {
                 ++iComputers;
             }	
         }
         
         return iClothes + iShoes + iBooks + iGames + iComputers;
         
     }
 
     /**
      * Renvoie true si cette liste possède une annonce plus récente pour l'itération
      * en cours.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return true si cette liste possède une annonce plus récente pour l'itération
      *         en cours
      * 
      * @ensures \result <==> previousIndex() >= 0;
      * @ensures !\result <==> previousIndex() == -1;
      * 
      * @pure
      */
     public boolean hasPrevious() {
	     
	     if (previousIndex() >= 0) {
	     	return true;
	     }
	     
	     return false;
        
     }
 
     /**
      * Renvoie l'annonce précedente (plus récente) dans l'itération en cours et
      * recule d'un élément dans l'itération.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return l'annonce précedente (plus récente) dans l'itération en cours
      * 
      * 
      * @requires hasPrevious();
      * @ensures \var Optional&lt;Category&gt; optCat = getSelectedCategory();
      * @ensures optCat.isEmpty() ==> \result.equals(\old(get(previousIndex())));
      * @ensures optCat.isPresent() ==> \result.equals(\old(get(optCat.get(),
      *          previousIndex())));
      * @ensures optCat.isPresent() ==> \result.getCategory().equals(optCat.get());
      * @ensures nextIndex() == \old(nextIndex()) - 1;
      * @ensures previousIndex() == \old(previousIndex()) - 1;
      * @ensures nextIndex() == \old(previousIndex());
      * @ensures lastIndex() == \old(previousIndex());
      * @ensures lastIndex() == nextIndex();
      * 
      */
     public ClassifiedAd previous() {
     
         ClassifiedAd previous = null;

         ClassifiedAd lastIndex = index;
         
         lastCalled = 2;
         
         if (selectedCat.isPresent()) {
         
         	if (selectedCat.get().indexOf(index) == 0) {
			previous = null;
         	}
         	else {
         		previous = selectedCat.get().get(selectedCat.get().indexOf(index) - 1);
         	}
         }
         
         else {
         
             int i;
             
                 ClassifiedAd pClothes = (clothes.size() == 0) ? null : clothes.get(clothes.size() - 1);
             
             if (pClothes != null) {
             
                 i = clothes.size() - 1;
                 while ((i > 0) && (index.isAfter(pClothes) || (index == pClothes))) {
                     pClothes = clothes.get(--i);
                 }
             }
 
                 ClassifiedAd pShoes = shoes.isEmpty() ? null : shoes.get(shoes.size() - 1);
                 if (pShoes != null){
                 i = shoes.size() - 1;
                 while ((i > 0) && (index.isAfter(pShoes) || (index == pShoes))) {
                     pShoes = shoes.get(--i);
                 }
             }
             
                 ClassifiedAd pBooks = books.isEmpty() ? null : books.get(books.size() - 1);
             if (pBooks != null){
                 i = books.size() - 1;
                 while ((i > 0) && (index.isAfter(pBooks) || (index == pBooks))) {
                     pBooks = books.get(--i);
                 }
             }
             
                 ClassifiedAd pGames = games.isEmpty() ? null : games.get(games.size() - 1);
             if (pGames != null){
                 i = games.size() - 1;
                 while ((i > 0) && (index.isAfter(pGames) || (index == pGames))) {
                     pGames = games.get(--i);
                 }
             }
             
                    ClassifiedAd pComputers = computers.isEmpty() ? null : computers.get(computers.size() - 1);
             if (pComputers != null) {
                 i = computers.size() - 1;
                 while ((i > 0) && (index.isAfter(pComputers) || (index == pComputers))) {
                     pComputers = computers.get(--i);
                 }
             }
             
             if (pClothes != null) {
                 previous = (pClothes.isAfter(index)) ? pClothes : null;			
             }
             
             if (pShoes != null) {
                 if ((previous==null || previous.isAfter(pShoes)) && (pShoes.isAfter(index))) {
                     previous = pShoes;
                 }
             }
             
             if (pBooks != null) {
                 if ((previous==null || previous.isAfter(pBooks)) && (pBooks.isAfter(index))){
                     previous = pBooks;
                 }
             }
             
             if (pGames != null) {
                 if ((previous==null || previous.isAfter(pGames)) && (pGames.isAfter(index))){
                     previous = pGames;
                 }
             }
             
             if (pComputers != null) {
                 if ((previous==null || previous.isAfter(pComputers)) && (pComputers.isAfter(index))){
                     previous = pComputers;
                 }
             }
             
         }
         
         index = previous;
         
         return lastIndex;
     }
 
     /**
      * Renvoie l'index de l'annonce qui sera renvoyée par le prochain appel à
      * previous(). Si l'itération est arrivée au début la valeur renvoyée est -1.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return l'index de l'annonce qui sera renvoyé par le prochain appel à
      *         previous(); ou -1
      * 
      * @ensures \var Optional&lt;Category&gt; optCat = getSelectedCategory();
      * @ensures \result == -1 <==> !hasPrevious();
      * @ensures optCat.isEmpty() ==> (hasPrevious() <==> \result >= 0 && \result <
      *          size());
      * @ensures optCat.isPresent() ==> (hasPrevious() <==> \result >= 0 && \result <
      *          size(optCat.get()));
      * 
      * @pure
      */
     public int previousIndex() {
     
         if (nextIndex() == 0) {
             return -1;	
         }
         
         if (nextIndex() == 1) {
             return 0;	
         }
         
         int res;
         
         if (selectedCat.isPresent()) {
		res = selectedCat.get().indexOf(index);	
		return res;   
         }

         
         ClassifiedAd pClothes = (clothes.size() == 0) ? null : clothes.get(clothes.size() - 1);
         
         int iClothes=clothes.size()-1, iShoes=shoes.size()-1, iBooks=books.size()-1, iGames=games.size()-1, iComputers=computers.size()-1;
         
         if (pClothes != null) {
             while ((iClothes > 0) && (index.isAfter(pClothes) || (index.equals(pClothes)))) {
                 pClothes = clothes.get(--iClothes);
             }
             
             if (index.isAfter(pClothes) || (index.equals(pClothes))) {
                 --iClothes;
             }
         }
             
             ClassifiedAd pShoes = shoes.isEmpty() ? null : shoes.get(shoes.size() - 1);
             if (pShoes != null) {
             while ((iShoes > 0) && (index.isAfter(pShoes) || (index.equals(pShoes)))) {
                 pShoes = shoes.get(--iShoes);
             }
             
             if (index.isAfter(pShoes) || (index.equals(pShoes))) {
                 --iShoes;	
             }
         }
         
             ClassifiedAd pBooks = books.isEmpty() ? null : books.get(books.size() - 1);
             if (pBooks != null) {
             while ((iBooks > 0) && (index.isAfter(pBooks) || (index.equals(pBooks)))) {
                 pBooks = books.get(--iBooks);
             }
             
             if (index.isAfter(pBooks) || (index.equals(pBooks))) {
                 --iBooks;	
             }
         }
         
             ClassifiedAd pGames = games.isEmpty() ? null : games.get(games.size() - 1);
                if (pGames != null) {
             while ((iGames > 0) && (index.isAfter(pGames) || (index.equals(pGames)))) {
                 pGames = games.get(--iGames);
             }
             if (index.isAfter(pGames) || (index.equals(pGames))) { 
                 --iGames;
             }	
         }
         
                ClassifiedAd pComputers = computers.isEmpty() ? null : computers.get(computers.size() - 1);
         if (pComputers != null) {
             while ((iComputers > 0) && (index.isAfter(pComputers) || (index.equals(pComputers)))) {
                 pComputers = computers.get(--iComputers);
             }
             if (index.isAfter(pComputers) || (index.equals(pComputers))) {
                 --iComputers;
             }	
         }
         
         
         
         res = iClothes + iShoes + iBooks + iGames + iComputers + 4;
		
		
	return res + 1;
                      
 
     }
  
     /**
      * Renvoie l'index de l'annonce qui a été renvoyée par le dernier appel à
      * previous() ou next(). Si next() ou previous() n'ont pas été appelé depuis le
      * dernier appel à startIteration() la valeur renvoyée est -1.
      * 
      * Si une catégorie est sélectionnée, l'opération ne concernera que les annonces
      * de cette catégorie; sinon l'opération concerne toutes les annonces, quelque
      * soit leur catégorie.
      * 
      * @return l'index de l'annonce qui a été renvoyé par le dernier appel à
      *         previous() ou next(); ou -1
      * 
      * @ensures \result == nextIndex() || \result == previousIndex();
      * 
      * @pure
      */
      public int lastIndex() {
         
        switch (lastCalled) {
            
            case 1: 
                return previousIndex();
                
            case 2:
                return nextIndex();
            
            default:
                return -1;
        
        }
    }

    /**
     * Renvoie l'élément d'index spécifié dans la liste des annonces de la catégorie
     * spécifiée. À la différence de la méthode get(int i), cette implémentation
     * effectue un accès direct au ième élément et peut donc être utilisée sans
     * pénalité pour effectuer une itération sur les éléments de la catégorie
     * spécifiée.
     * 
     * @param cat catégorie dans la quelle l'élement est recherché
     * @param i   rang de l'élément cherché dans la liste des éléments de la
     *            catégorie spécifiée
     * @return l'élément d'index spécifié dans la liste des annonces de la catégorie
     *         spécifiée
     * 
     * @requires cat != null;
     * @requires i >= 0 && i < size(cat);
     * @ensures contains(\result);
     * @ensures \result.getCategory().equals(cat);
     * 
     * @pure
     */
    public ClassifiedAd get(Category cat, int i) {
    
        switch (cat) {
            
            case CLOTHES:
                return clothes.get(i);	
                
            case SHOES:
                return shoes.get(i);	
                
            case BOOKS:
                return books.get(i);	
                
            case GAMES:
                return games.get(i);	
        
            case COMPUTERS:
                return computers.get(i);	
            
            default:
                return null;
        }

    }

    /**
     * Renvoie l'élément d'index spécifié dans la liste des annonces. Cette
     * implémentation n'est pas adaptée à une utilisation pour effectuer des
     * itérations sur l'ensemble de cette liste. Pour effectuer une itération, il
     * est fortement recommandé d'utiliser les méthodes prévues à cet effet
     * (startIteration, hasNext, next, hasPrevious, previous, ...).
     * 
     * @param i rang de l'élément cherché dans la liste des éléments
     * @return l'élément d'index spécifié dans la liste des annonces
     * 
     * @requires i >= 0 && i < size();
     * @ensures contains(\result);
     * @ensures (\exists int i; i >= 0 && i < size(\result.getCategory());
     *          \result.equals(get(\result.getCategory(), i)));
     * 
     * @pure
     */
    public ClassifiedAd get(int i) {
    
        ClassifiedAd tmpIndex = index;
        int tmpLast = lastCalled; 
        Optional<ArrayList<ClassifiedAd>> tmpSelectedCat = selectedCat;
        
        clearSelectedCategory();
            
        for (int j=0; j<=i; j++) {
            next();
        }
        
        ClassifiedAd tmpIndex2 = index;
        
        index = tmpIndex;
        
        lastCalled = tmpLast;
        
        selectedCat = tmpSelectedCat;
        
        return tmpIndex2;
    
    }

    /**
     * Ajoute l'élement spécifié dans cette liste. L'élement est inséré dans la
     * liste de manière à ce que la liste reste triée. L'itération en cours est
     * réinitialisée.
     * 
     * @param elt l'élement à ajouter
     * 
     * @requires elt != null;
     * @requires !contains(elt);
     * @ensures contains(elt);
     * @ensures size() == \old(size()) + 1;
     * @ensures size(elt.getCategory()) == \old(size(elt.getCategory())) + 1;
     * @ensures (\forall Category cat; !cat.equals(elt.getCategory()); size(cat) ==
     *          \old(size(cat)));
     * @ensures !hasPrevious();
     * @ensures previousIndex() == -1;
     * @ensures nextIndex() == 0;
     * @ensures lastIndex() == -1;
     */
    public void add(ClassifiedAd elt) {
    
        int i;
        ClassifiedAd curr;

        switch (elt.getCategory()) {
            
            case CLOTHES:
                
                i=0;
                
                if (clothes.size() == 0) {
                    clothes.add(i, elt);
                    break;
                }
                
                curr = clothes.get(0);
                while ((i < clothes.size()) && elt.isBefore(curr)) {
                    curr = clothes.get(i++);
                }
                
                clothes.add(i, elt);
                
                break;
                
                
            case SHOES:
            
                i=0;
                
                if (shoes.size() == 0) {
                    shoes.add(i, elt);
                    break;
                }
                
                curr = shoes.get(0);
                while ((i < shoes.size()) && elt.isBefore(curr)) {
                    curr = shoes.get(i++);
                }
                
                shoes.add(i, elt);
                break;
               
            case BOOKS:
            
                i=0;
                
                if (books.size() == 0) {
                    books.add(i, elt);
                    break;
                }
                
                curr = books.get(0);
                while ((i < books.size()) && elt.isBefore(curr)) {
                    curr = books.get(i++);
                }
                
                books.add(i, elt);
                break;
                
                
            case GAMES:
                i=0;
                if (games.size() == 0) {
                    games.add(i, elt);
                    break;
                }
                curr = games.get(0);
                while ((i < games.size()) && elt.isBefore(curr)) {
                    curr = games.get(i++);
                }
                
                games.add(i, elt);
                break;
        
            case COMPUTERS:
                i=0;
                if (computers.size() == 0) {
                    computers.add(i, elt);
                    break;
                }
                curr = computers.get(0);
                while ((i < computers.size()) && elt.isBefore(curr)) {
                    curr = computers.get(i++);
                }
                
                computers.add(i, elt);
                break;
            
        }
        
        startIteration();
    }

    /**
     * Retire une occurence de l'élement spécifié de cette liste s'il y était
     * présent. Renvoie true si l'élement a effectivement été retiré de cette liste.
     * Si l'élément spécifié est effectivement retiré, l'itération en cours est
     * réinitialisée.
     * 
     * @param o l'élement à retirer de cette liste
     * 
     * @return true si l'élement a effectivement été retiré de cette liste; false
     *         sinon
     * 
     * @ensures !contains(o);
     * @ensures \result <==> \old(contains(o));
     * @ensures \result <==> (size() == \old(size()) - 1);
     * @ensures !\result <==> (size() == \old(size());
     * @ensures \result <==> (o instanceof ClassifiedAd) <br/>
     *          && (size(((ClassifiedAd) o).getCategory()) <br/>
     *          == \old(size(((ClassifiedAd) o).getCategory())) - 1);
     * @ensures (o instanceof ClassifiedAd) ==> (\forall Category cat;<br/>
     *          !cat.equals(((ClassifiedAd) o).getCategory()); <br/>
     *          size(cat) == \old(size(cat)));
     * @ensures \result ==> !hasPrevious();
     * @ensures \result ==> previousIndex() == -1;
     * @ensures \result ==> nextIndex() == 0;
     * @ensures \result ==> lastIndex() == -1;
     * @ensures !\result ==> (hasPrevious() == \old(hasPrevious()));
     * @ensures !\result ==> (previousIndex() == \old(previousIndex()));
     * @ensures !\result ==> (nextIndex() == \old(nextIndex()));
     * @ensures !\result ==> (lastIndex() == \old(lastIndex()));
     * 
     */
    public boolean remove(Object o) {
        
        if (! ( o instanceof ClassifiedAd)) {
        
            return false;
        }
        
        ClassifiedAd rm = (ClassifiedAd) o;
        
        if (clothes.remove(rm) || shoes.remove(rm) || books.remove(rm) || games.remove(rm) || computers.remove(rm)) {
            clearSelectedCategory();
            return true;
        }
        
        return false;
    }

    /**
     * Renvoie true si et seulement si l'argument spécifié est présent dans cette
     * liste.
     * 
     * @param o l'objet dont on veut tester la présence dans cette liste
     * 
     * @return true si l'argument spécifié est présent dans cette liste; false sinon
     * 
     * @ensures \result <==> (\exists int i; i >= 0 && i < size();
     *          get(i).equals(o));
     * @ensures \result <==> (o instanceof ClassifiedAd) <br/>
     *          && (\exists int i; i >= 0 && i < size((ClassifiedAd)
     *          o).getCategory()); <br/>
     *          get(((ClassifiedAd) o).getCategory(), i).equals(o));
     * 
     * @pure
     */
    public boolean contains(Object o) {
        
        if (! (o instanceof ClassifiedAd)) {
            return false;
        }
        
        ClassifiedAd rm = (ClassifiedAd) o;
    
        return (clothes.contains(rm) || shoes.contains(rm) || books.contains(rm) || games.contains(rm) || computers.contains(rm));
    }

    /**
     * Renvoie le nombre total d'éléments de cette liste.
     * 
     * @return le nombre total d'éléments de cette liste
     * 
     * @ensures \result >= 0;
     * @ensures \result == (\sum Category cat;true;size(cat));
     * 
     * @pure
     */
    public int size() {
        
        return clothes.size() + shoes.size() + books.size() + games.size() + computers.size();
    }

    /**
     * Renvoie le nombre d'annonces de cette liste appartenant à la catégorie
     * spécifiée.
     * 
     * @param cat catégorie dont on souhaite connaître le nombre d'éléments
     * 
     * @return le nombre d'annonces de cette liste appartenant à la catégorie
     *         spécifiée
     * 
     * @requires cat != null;
     * @ensures \result >= 0 && \result <= size();
     * @ensures \result == (\sum int i; i >= 0 && i < size() &&
     *          get(i).getCategory().equals(cat); 1);
     * 
     * @pure
     */
    public int size(Category cat) {
        
        switch (cat) {
            
            case CLOTHES:
                return clothes.size();	
                
            case SHOES:
                return shoes.size();	
                
            case BOOKS:
                return books.size();	
                
            case GAMES:
                return games.size();	
        
            case COMPUTERS:
                return computers.size();
                
            default:
                return 0;	
            
        }
    }

    /**
     * Renvoie true si et seulement si l'argument spécifié est une CategorizedAdList
     * contenant les mêmes éléments dans le même ordre que cette CategorizedAdList,
     * et que la CategorizedAdList spécifiée est dans le même état que cette liste
     * concernant l'itération en cours et la catégorie sélectionnée.
     * 
     * @param obj l'objet à comparer à cette liste
     * 
     * @return true si l'argument spécifié contient les mêmes éléments et est dans
     *         le même état que cette liste
     * 
     * @ensures !(obj instanceof CategorizedAdList) ==> !\result;
     * @ensures \result ==> ((CategorizedAdList) obj).size() == size();
     * @ensures \result ==> ((CategorizedAdList) obj).previousIndex() ==
     *          previousIndex();
     * @ensures \result ==> ((CategorizedAdList) obj).nextIndex() == nextIndex();
     * @ensures \result ==> ((CategorizedAdList) obj).lastIndex() == lastIndex();
     * @ensures \result ==> ((CategorizedAdList)
     *          obj).getSelectedCategory().equals(getSelectedCategory());
     * @ensures \result ==> (\forall int i; i >= 0 && i < size();
     *          ((CategorizedAdList) obj).get(i).equals(get(i)));
     * @ensures \result ==> ((CategorizedAdList) obj).hashCode() == hashCode();
     * 
     * @pure
     */
    @Override
    public boolean equals(Object obj) {
        
        if (! (obj instanceof CategorizedAdList)) {
            return false;
        }
        
        CategorizedAdList liste = (CategorizedAdList) obj;
        
        
        if (liste.size() != size()) {
            return false;
        }
        
        
        for (int i=0; i<size(); i++) {		
            if (! liste.get(i).equals(get(i))) {
                return false;
            }
        }
        
        if (liste.previousIndex() != this.previousIndex() || liste.nextIndex() != this.nextIndex() || liste.lastIndex() != this.lastIndex()) {
                return false;
            }
        
        if (!this.getSelectedCategory().equals(liste.getSelectedCategory())) {
                   return false;
            }
        
        return (liste.hashCode() == hashCode());
        
    }

    /**
     * Renvoie un clone de cette liste.
     * 
     * @return un clone de cette liste
     * 
     * @ensures \result != null;
     * @ensures \result != this;
     * @ensures \result.equals(this);
     * @ensures \result.getClasse() == this.getClass();
     * 
     * @pure
     */
    @Override
    public CategorizedAdList clone() {
    
        CategorizedAdList clone;
        
        try {
            clone = (CategorizedAdList) super.clone();
        }
        
        catch (CloneNotSupportedException e) {
            throw new InternalError("Erreur impossible" + "en th´eorie !");	
        }
        
        return clone;
        
    }

    /**
     * Renvoie un code de hashage pour cette liste.
     * 
     * @return un code de hashage pour cette liste
     * 
     * @pure
     */
    @Override
    public int hashCode() {
        return clothes.hashCode() + shoes.hashCode() + books.hashCode() + games.hashCode() + computers.hashCode();
    }

    /**
     * Renvoie une représentation de cette liste sous forme d'une chaîne de caractères.
     * 
     * @return une représentation de cette liste sous forme d'une chaîne de caractères
     * 
     * @ensures \result != null;
     * @ensures \result.contains("" + lastIndex());
     * @ensures \result.contains("" + nextIndex());
     * @ensures \result.contains("" + previousIndex());
     * @ensures \result.contains(getSelectedCategory().toString());
     * @ensures (\forall ClassifiedAd ad; contains(ad); \result.contains(ad.toString())); 
     * 
     * @pure
     */
    @Override
    public String toString() {
        
        int i;
        
        String s = " ";
        
        s += "Clothes: ";
        for (i=0; i<clothes.size(); i++) {
            s += " " + clothes.get(i).toString() + " \n";
        }
        
        s += "\n Shoes: ";
        for (i=0; i<shoes.size(); i++) {
            s += " " + shoes.get(i).toString() + " \n";
        }
        
        
        s += "\n Books: ";
        for (i=0; i<books.size(); i++) {
            s += " " + books.get(i).toString() + " \n";
        }
        
        s += "\n Games: ";
        for (i=0; i<games.size(); i++) {
            s += " " + games.get(i).toString() + " \n";
        }
        
        
        s += "\n Computers : ";
        for (i=0; i<computers.size(); i++) {
            s += " " + computers.get(i).toString() + " \n";
        }
    
    
    
        return "LastIndex: " + lastIndex() + "\t nextIndex: " + nextIndex() + "\t previousIndex: " + lastIndex() + " \n Catégorie choisie: " + getSelectedCategory().toString() + " \n" + s;
    }
}
