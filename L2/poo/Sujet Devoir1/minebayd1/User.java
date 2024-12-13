/**
 * @author Youcef GHEDAMSI 12302243
 * Je déclare qu'il s'agit de mon propre travail
 */

package minebayd1;

import java.time.Instant;
import java.util.Optional;
import static minebayd1.AdState.*;


import java.util.ArrayList;

/**
 * Un utilisateur de l'application MinEbay.
 * 
 * <p>
 * Un User est caractérisé par:
 * <ul>
 * 	<li>son nom et son mot de passe</li>
 * 	<li>le montant disponible sur son compte bancaire</li>
 * 	<li>sa date d'inscription sur MinEbay (= date de création de l'instance de l'User)</li>
 * 	<li>la liste des annonces qu'il a posté et pour lesquelles il n'a pas trouvé d'acheteur (open ads)</li>
 * 	<li>la liste des annonces qu'il a posté et pour lesquelles il a vendu l'objet concerné (closed ads)</li>
 	<li>la liste des annonces (d'autres utilisateurs) pour lesquelles il a acheté l'objet concerné (puchases)</li>
 * </ul>
 * </p>
 * 
 * <p>
 * Chacune des trois listes d'annonces d'un User est représentée en utilisant une instance de CategorizedAdList.
 * </p>
 * 
 * <p>
 * Les méthodes ne possédant pas de paramètre de type AdState ou Category agissent uniquement sur les listes d'annonces dont l'état et, le cas échéant,
 * la catégorie a été sélectionnée.
 * </p>
 * 
 * Un ensemble complet de méthodes permet d'effectuer des itérations bidirectionnelles sur les listes d'annonces de l'User. 
 * Ce sont les méthodes: startIteration(), hasNext(), nextIndex(), next(), hasPrevious(), previousIndex(), previous() et lastIndex(). 
 * 
 * 
 * Un exemple d'utilisation de ces méthodes est sonné ci-après:
 * 
 * <pre>{@code
 * aUser.startIteration(); // Initialisation d'une nouvelle itération
 * // Affichage des annonces du plus récent au plus ancien:
 * while (aUser.hasNext()) {
 * 	System.out.println("Annonce suivante (plus ancienne):" + aUser.next());
 * }
 * // Affichage des annonces du plus ancien au plus récent:
 * while (aUser.hasPrevious()) {
 * 	System.out.println("Annonce précédente (plus récente):" + aUser.previous());
 * }
 * }</pre>
 * 
 * @invariant getName() != null && !getName().isBlank();
 * @invariant getPassword() != null && !getPassword().isBlank();
 * @invariant getRegistrationDate() != null;
 * @invariant (\forall AdState state; true; !contains(state, null));
 * @invariant (\forall int i, j; i >= 0 && i < j && j < size();
 *            get(i).isAfter(get(j)));
 * @invariant (\forall AdState state, Category cat;true; <br/>
 *            (\forall int i, j; <br/>
 *            i >= 0 && i < j && j < size(state, Optional<Category>.of(cat));
 *            get(state, Optional<Category>.of(cat), i).isAfter(get(state,
 *            Optional<Category>.of(cat), j))));
 * @invariant size() == asList().size();
 * @invariant previousIndex() >= -1 && previousIndex() < size();
 * @invariant nextIndex() >= 0 && nextIndex() <= size();
 * @invariant nextIndex() == previousIndex() + 1;
 * @invariant lastIndex() >= -1 && lastIndex() < size();
 * @invariant lastIndex() == previousIndex() || lastIndex() == nextIndex();
 * 
 * @author Marc Champesme
 * @since 27/09/2024
 * @version 20/10/2024
 * 
 */
public class User {
	
	public static final int DEFAULT_CASH_AMMOUNT = 100;
	
	private String name, pswd;
	private int solde;
	private Instant date;
	
	private CategorizedAdList openAds, closedAds, purchases;
	
	private AdState selectedState;
	
	/**
	 * Initialise une nouvelle instance ayant les nom et mot de passe spécifiés. La
	 * date d'inscription du nouvel utilisateur est la date au moment de l'exécution
	 * de ce constructeur. Une nouvelle itération est initialisée sur les annonces
	 * OPEN de ce User.
	 * 
	 * @param userName nom de la nouvelle instance de User
	 * @param password mot de passe de la nouvelle instance de User
	 * 
	 * @requires userName != null && !userName.isBlank();
	 * @requires password != null && !password.isBlank();
	 * @ensures getName().equals(userName);
	 * @ensures getPassword().equals(password);
	 * @ensures getRegistrationDate() != null;
	 * @ensures \old(Instant.now()).isBefore(getRegistrationDate());
	 * @ensures getRegistrationDate().isBefore(Instant.now());
	 * @ensures getAvailableCash() = DEFAULT_CASH_AMMOUNT;
	 * @ensures getSelectedAdState().equals(OPEN);
	 * @ensures getSelectedCategory().isEmpty();
	 * @ensures !hasPrevious();
	 * @ensures !hasNext();
	 * @ensures previousIndex() == -1;
	 * @ensures nextIndex() == 0;
	 * @ensures lastIndex() == -1;
	 */
	public User(String userName, String password) {
	
		this.name = userName;
		this.pswd = password;
       		this.date = Instant.now();
       		
       		this.solde = DEFAULT_CASH_AMMOUNT;
       		
       		openAds = new CategorizedAdList();
		closedAds = new CategorizedAdList();
       		purchases = new CategorizedAdList();
        	
        	selectedState = OPEN;
        	
        	clearSelectedCategory();
	
	}
	

	/**
	 * Renvoie l'état actuellement sélectionné pour les annonces.
	 * 
	 * @return l'état actuellement sélectionné pour les annonces
	 * 
	 * @ensures \result != null;
	 * 
	 * @pure
	 */
	public AdState getSelectedAdState() {
		return selectedState;
	}

	/**
	 * Sélectionne l'état spécifié. Une nouvelle itération est initialisée pour les
	 * annonces dans cet état et le cas échéant la catégorie sélectionnée.
	 * 
	 * @param state état à sélectionner pour les annonces
	 * 
	 * @requires state != null;
	 * @ensures getSelectedAdState().equals(state);
	 * @ensures getSelectedCategory().equals(\old(getSelectedCategory()));
	 * @ensures !hasPrevious();
	 * @ensures previousIndex() == -1;
	 * @ensures nextIndex() == 0;
	 * @ensures lastIndex() == -1;
	 */
	public void selectAdState(AdState state) {
		
		Optional<Category> cat = getSelectedCategory();
		
		switch (selectedState) {
			
				case OPEN:
					openAds.startIteration();
					break;
					
				case CLOSED:
					closedAds.startIteration();
					break;
				
				case PURCHASE:
					purchases.startIteration();
					break;
			
		}
		
		
		selectedState = state;
		
		switch (selectedState) {
			
				case OPEN:
					openAds.startIteration();
					break;
					
				case CLOSED:
					closedAds.startIteration();
					break;
				
				case PURCHASE:
					purchases.startIteration();
					break;
			
		}
		
		
		if (cat.isPresent()) {
			selectCategory(cat.get());
		}
		else {
			clearSelectedCategory();
		}
		
		
	}

	/**
	 * Sélectionne la catégorie spécifiée. Une nouvelle itération est initialisée
	 * pour les annonces de cette catégorie et dans l'état spécifié.
	 * 
	 * @param cat catégorie à sélectionner pour les annonces
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
		
		switch (selectedState) {
			
				case OPEN:
					openAds.selectCategory(cat);
					break;
					
				case CLOSED:
					closedAds.selectCategory(cat);
					break;
				
				case PURCHASE:
					purchases.selectCategory(cat);
					break;
			
		}
	}

	/**
	 * Renvoie un {@code Optional<Category>} représentant la catégorie actuellement
	 * sélectionnée. Si aucun catégorie n'est sélectionnée, renvoie un
	 * Optional.empty().
	 * 
	 * @return un {@code Optional<Category>} de la catégorie actuellement
	 *         sélectionnée ou Optional.empty()
	 * 
	 * @ensures \result != null;
	 * 
	 * @pure
	 */
	public Optional<Category> getSelectedCategory() {
		
		switch (selectedState) {
			
				case OPEN:
					return openAds.getSelectedCategory();
					
				case CLOSED:
					return closedAds.getSelectedCategory();
				
				case PURCHASE:
					return purchases.getSelectedCategory();
			
		}
		
		return Optional.empty();
		
	}

	/**
	 * Déselectionne la catégorie sélectionnée et effectue les initialisations
	 * nécessaire pour démarrer une nouvelle itération (cf.startIteration()). Si
	 * aucune catégorie n'était sélectionnée l'appel à cette méthode est équivalent
	 * à un appel à startIteration.
	 * 
	 * @ensures getSelectedCategory().isEmpty();
	 * @ensures getSelectedAdState().equals(\old(getSelectedAdState()));
	 * @ensures !hasPrevious();
	 * @ensures previousIndex() == -1;
	 * @ensures nextIndex() == 0;
	 * @ensures lastIndex() == -1;
	 */
	public void clearSelectedCategory() {
		/*
		openAds.clearSelectedCategory();
		closedAds.clearSelectedCategory();
		purchases.clearSelectedCategory();
		*/
		switch (selectedState) {
			
			case OPEN:
				openAds.clearSelectedCategory();
				break;
					
			case CLOSED:
				closedAds.clearSelectedCategory();
				break;
				
			case PURCHASE:
				purchases.clearSelectedCategory();
				break;
			
		}
	}

	/**
	 * Renvoie le nom de cet utilisateur.
	 * 
	 * @return le nom de cet utilisateur
	 * 
	 * @pure
	 */
	public String getName() {
		return name;
	}

	/**
	 * Renvoie le mot de passe de cet utilisateur.
	 * 
	 * @return le mot de passe de cet utilisateur
	 * 
	 * @pure
	 */
	public String getPassword() {
		return pswd;
	}

	/**
	 * Renvoie l'Instant représentant la date d'inscription de cet utilisateur.
	 * 
	 * @return la date d'inscription de cet utilisateur
	 * 
	 * @pure
	 */
	public Instant getRegistrationDate() {
		return date;
	}

	/**
	 * Renvoie la somme d'argent disponible pour cet utilisateur pour acheter des objets.
	 * 
	 * @return la somme d'argent disponible pour cet utilisateur
	 * 
	 * @ensures \result >= 0;
	 * 
	 * @pure
	 */
	public int getAvailableCash() {
		return solde;
	}

	/**
	 * Achète à l'utilisateur spécifié l'objet présenté dans l'annonce spécifiée.
	 * Pour le vendeur l'annonce passe de la liste des annonces OPEN à la liste des
	 * annonces CLOSED et il reçoit le montant du prix de l'objet présenté dans
	 * l'annonce. Pour ce User, l'annonce est ajoutée à la liste des annonces
	 * PURCHASE et sa somme d'argent disponible est diminuée du prix de l'objet.
	 * Pour l'acheteur et le vendeur les itérations en cours sont réinitialisées
	 * comme par un appel à startIteration.
	 * 
	 * @param vendor l'utilisateur auteur de l'annonce spécifiée
	 * @param ad     l'annonce de l'objet à acheter
	 * 
	 * 
	 * @requires vendor != null;
	 * @requires !this.equals(vendor);
	 * @requires ad != null;
	 * @requires vendor.containsInState(OPEN, ad);
	 * @requires getAvailableCash() >= ad.getPrice();
	 * @ensures containsInState(PURCHASE, ad);
	 * @ensures size(PURCHASE, Optional.of(ad.getCategory()))<br/>
	 *          == \old(size(PURCHASE, Optional.of(ad.getCategory()))) + 1;
	 * @ensures !vendor.containsInState(OPEN, ad);
	 * @ensures vendor.size(OPEN, Optional.of(ad.getCategory())) ==
	 *          \old(vendor.size(OPEN, Optional.of(ad.getCategory()))) - 1;
	 * @ensures vendor.containsInState(CLOSED, ad);
	 * @ensures vendor.size(CLOSED, Optional.of(ad.getCategory())) ==
	 *          \old(vendor.size(CLOSED, Optional.of(ad.getCategory()))) + 1;
	 * @ensures getAvailableCash() == \old(getAvailableCash()) - ad.getPrice();
	 * @ensures vendor.getAvailableCash() == \old(vendor.getAvailableCash()) +
	 *          ad.getPrice();
	 * @ensures !hasPrevious();
	 * @ensures previousIndex() == -1;
	 * @ensures nextIndex() == 0;
	 * @ensures lastIndex() == -1;
	 * @ensures vendor.!hasPrevious();
	 * @ensures vendor.previousIndex() == -1;
	 * @ensures vendor.nextIndex() == 0;
	 * @ensures vendor.lastIndex() == -1; }
	 */
	public void buy(User vendor, ClassifiedAd ad) {
		
		purchases.add(ad);
		
		vendor.closedAds.add(ad);
    		vendor.openAds.remove(ad);

   		solde -= ad.getPrice();
   		vendor.solde += ad.getPrice();
   		
		/*
		openAds.startIteration();
		vendor.openAds.startIteration();
		
		closedAds.startIteration();
		vendor.closedAds.startIteration();


		purchases.startIteration();
		vendor.purchases.startIteration();
		
		selectedState = OPEN;
		vendor.selectedState = OPEN;
		
		*/

		switch (selectedState) {
			
				case OPEN:
					openAds.startIteration();
					vendor.openAds.startIteration();
					break;
					
				case CLOSED:
					closedAds.startIteration();
					vendor.closedAds.startIteration();
					break;
				
				case PURCHASE:
					purchases.startIteration();
					vendor.purchases.startIteration();
					break;
			
		}
				
	
	}

	/**
	 * Crée et renvoie une nouvelle instance de ClassifiedAd dont les
	 * caractéristiques sont les arguments spécifiés et l'ajoute à la liste des
	 * annonces ouvertes (open ads) de cet utilisateur. La date de cette annonce est
	 * la date d'exécution de cette méthode. Si l'état sélectionné des annonces est
	 * OPEN, l'itération en cours est réinitialisée, comme par un appel à
	 * startIteration.
	 * 
	 * @param cat   la catégorie de la nouvelle annonce
	 * @param msg   la description de la nouvelle annonce
	 * @param price le prix de l'objet décrit dans la nouvelle annonce
	 * 
	 * @return la nouvelle annonce de cet utilisateur
	 * 
	 * @old oldDate = Instant.now();
	 * @requires cat != null;
	 * @requires msg != null;
	 * @requires price > 0;
	 * @ensures get(OPEN, Optional.of(cat), 0).equals(\result);
	 * @ensures \result.getCategory().equals(cat);
	 * @ensures \result.getDescription().equals(msg);
	 * @ensures \result.getPrice() == price;
	 * @ensures size(OPEN, Optional.of(cat)) == \old(size(OPEN, Optional.of(cat))) +
	 *          1;
	 * @ensures oldDate.isBefore(\result.getDate());
	 * @ensures \result.getDate().isBefore(Instant.now());
	 * @ensures getSelectedAdState().equals(OPEN) ==> !hasPrevious();
	 * @ensures getSelectedAdState().equals(OPEN) ==> previousIndex() == -1;
	 * @ensures getSelectedAdState().equals(OPEN) ==> nextIndex() == 0;
	 * @ensures getSelectedAdState().equals(OPEN) ==> lastIndex() == -1;
	 */
	 public ClassifiedAd add(Category cat, String msg, int price) {
		
		ClassifiedAd res = new ClassifiedAd(cat, msg, price);
		
		openAds.add(res);
		
		openAds.startIteration();
		
		/*
		if (getSelectedAdState().equals(OPEN)) {
			openAds.clearSelectedCategory();
		}
		*/
		return res;
		
		 
	}

	/**
	 * Renvoie le nombre d'annonces de cet utilisateur dans l'état sélectionné
	 * (open, closed ou purchase). Si une catégorie est sélectionnée seules les
	 * annonces de cette catégorie sont comptées.
	 * 
	 * @return le nombre d'annonces de cet utilisateur dans l'état et la catégorie
	 *         sélectionnés.
	 * 
	 * @ensures \result == size(getSelectedAdState(), getSelectedCategory());
	 * 
	 * @pure
	 */
	public int size() {
		
		if (getSelectedCategory().isPresent()) {
		
			switch (selectedState) {
			
				case OPEN:
					return openAds.size(getSelectedCategory().get());
					
				case CLOSED:
					return closedAds.size(getSelectedCategory().get());
				
				case PURCHASE:
					return purchases.size(getSelectedCategory().get());
			
			}
			
		}
		
		else {
			
			switch (selectedState) {
			
				case OPEN:
					return openAds.size();
					
				case CLOSED:
					return closedAds.size();
				
				case PURCHASE:
					return purchases.size();
			
			}
			
			
		}
		
		return 0;
		

	}

	/**
	 * Renvoie le nombre d'annonces de cet utilisateur dans l'état spécifié et
	 * appartenant à la catégorie spécifiée.
	 * 
	 * @param state état des annonces
	 * @param cat   catégorie des annonces
	 * 
	 * @requires state != null;
	 * @requires cat != null;
	 * @ensures \result >= 0;
	 * @ensures getSelectedAdState().equals(state) &&
	 *          getSelectedCategory().equals(cat) <br/>
	 *          ==> \result == size();
	 * 
	 * @return le nombre d'annonces de cet utilisateur dans l'état spécifié et
	 *         appartenant à la catégorie spécifiée
	 * @pure
	 */
	public int size(AdState state, Optional<Category> cat) {
	
		
		if (cat.isPresent()) {
		
			switch (state) {
			
				case OPEN:
					return openAds.size(cat.get());
					
				case CLOSED:
					return closedAds.size(cat.get());
				
				case PURCHASE:
					return purchases.size(cat.get());
			
			}
			
		}
		
		else {
			
			switch (state) {
			
				case OPEN:
					return openAds.size();
					
				case CLOSED:
					return closedAds.size();
				
				case PURCHASE:
					return purchases.size();
			
			}
			
			
		}
		
		return 0;
			
	}

	/**
	 * Renvoie la ième plus récente annonce de ce User dans l'état et la catégorie
	 * sélectionnée.
	 * 
	 * Cette opération ne concerne les annonces dans l'état sélectionné (open,
	 * closed ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette opération ne concerne que les
	 * annonces de cette catégorie, pour les annonces dans l'état sélectionné.
	 * 
	 * @param i index de l'annonce cherchée
	 * 
	 * @return la ième plus récente annonce de ce User
	 * 
	 * @requires i >= 0 && i < size();
	 * @ensures \result != null;
	 * @ensures \result.equals(get(getSelectedAdState(), getSelectedCategory(), i);
	 * 
	 * @pure
	 */
	public ClassifiedAd get(int i) {
	
		return get(selectedState, getSelectedCategory(), i);
		/*
	
		switch (selectedState) {
			
				case OPEN:
					return openAds.get(i);
					
				case CLOSED:
					return closedAds.get(i);
				
				case PURCHASE:
					return purchases.get(i);
			
		}
		
		return null;
		
		*/
	}

	/**
	 * Renvoie le ième élément de la liste des annonces étant dans l'état spécifié
	 * et appartenant à la catégorie spécifiée.
	 * 
	 * @param state l'état des annonces
	 * @param cat   catégorie des annonces
	 * @param i     index de l'élément dans la liste
	 * 
	 * @return le ième élément de la liste des annonces étant dans l'état spécifié
	 *         et appartenant à la catégorie spécifiée
	 * 
	 * @requires state != null;
	 * @requires cat != null;
	 * @requires i >= 0 && i < size(state, cat);	
	 * @ensures \result != null;
	 * @ensures containsInState(state, \result);
	 * @ensures cat.isPresent() ==> \result.getCategory().equals(cat.get());
	 * 
	 * @pure
	 */
	public ClassifiedAd get(AdState state, Optional<Category> cat, int i) {
		
		switch (state) {
			case OPEN: 
			    if (cat.isPresent()) {
				return openAds.get(cat.get(), i);
			    } else {
				return openAds.get(i);
			    }
			case CLOSED: 
			    if (cat.isPresent()) {
				return closedAds.get(cat.get(), i);
			    } else {
				return closedAds.get(i);
			    }
			case PURCHASE: 
			    if (cat.isPresent()) {
				return purchases.get(cat.get(), i);
			    } else {
				return purchases.get(i);
			    }
			default: 
			    throw new IllegalArgumentException("Invalid AdState: " + state);
		}
		
	}

	/**
	 * Renvoie true si ce User possède parmi les annonces dans l'état spécifié,
	 * l'objet spécifié.
	 * 
	 * @param state état des annonces parmi lesquelles l'objet est recherché
	 * @param obj   annonce cherchée
	 * @return true si ce User possède parmi les annonces dans l'état spécifié,
	 *         l'objet spécifié; false sinon
	 * 
	 * @requires state != null;
	 * @ensures !(obj instanceof ClassifiedAd) ==> !\result;
	 * @ensures \result <==> (\exists int i; <br/>
	 *          i >= 0 && i < size(state, Optional.empty()); <br/>
	 *          get(state, Optional.empty(), i).equals(obj));
	 * @pure
	 */
	public boolean containsInState(AdState state, Object obj) {
		
		switch (state) {
			
				case OPEN:
					return openAds.contains(obj);
					
				case CLOSED:
					return closedAds.contains(obj);
				
				case PURCHASE:
					return purchases.contains(obj);
			
		}
		
		return false;
	}

	/**
	 * Initialise ce User pour le démarrage d'une nouvelle itération sur les
	 * annonces de ce User. Cette itération s'effectue à partir des annonces les
	 * plus récentes, de sorte que chaque appel à next() renvoie une annonce plus
	 * ancienne.
	 * 
	 * Cette itération ne concerne que les annonces dans l'état sélectionné (open,
	 * closed ou purchase).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @ensures !hasPrevious();
	 * @ensures previousIndex() == -1;
	 * @ensures nextIndex() == 0;
	 * @ensures lastIndex() == -1;
	 */
	public void startIteration() {
		
		switch (selectedState) {
			
				case OPEN:
					openAds.startIteration();
					break;
					
				case CLOSED:
					closedAds.startIteration();
					break;
				
				case PURCHASE:
					purchases.startIteration();
					break;
			
		}
	}

	/**
	 * Renvoie true si ce User possède une annonce plus ancienne pour l'itération en
	 * cours.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * 
	 * 
	 * @return true si ce User possède une annonce plus ancienne pour l'itération en
	 *         cours
	 * 
	 * @ensures \result <==> nextIndex() < size();
	 * 
	 * @pure
	 */
	public boolean hasNext() {
		
		switch (selectedState) {
			
				case OPEN:
					return openAds.hasNext();
					
				case CLOSED:
					return closedAds.hasNext();
				
				case PURCHASE:
					return purchases.hasNext();
			
		}
		
		return false;
	}

	/**
	 * Renvoie l'annonce suivante (plus ancienne) dans l'itération en cours et
	 * avance d'un élément dans l'itération.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @return l'annonce suivante (plus ancienne) dans l'itération en cours
	 * 
	 * @requires hasNext();
	 * @ensures \result != null;
	 * @ensures \result.equals(\old(get(nextIndex())));
	 * @ensures \result.equals(get(lastIndex()));
	 * @ensures getSelectedCategory().isPresent() ==><br/>
	 *          \result.getCategory().equals(getSelectedCategory().get());
	 * @ensures containsInState(getSelectedAdState(), \result);
	 * @ensures nextIndex() == \old(nextIndex()) + 1;
	 * @ensures previousIndex() == \old(previousIndex()) + 1;
	 * @ensures previousIndex() == \old(nextIndex());
	 * @ensures lastIndex() == \old(nextIndex());
	 * @ensures lastIndex() == previousIndex();
	 */
	public ClassifiedAd next() {
	
		switch (selectedState) {
			
			case OPEN:
				return openAds.next();
				
			case CLOSED:
				return closedAds.next();
			
			case PURCHASE:
				return purchases.next();
			
		}
		
		return null;
	}

	/**
	 * Renvoie l'index de l'annonce qui sera renvoyée par le prochain appel à
	 * next(). Si l'itération est arrivée à la fin la valeur renvoyée est size().
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @return l'index de l'annonce qui sera renvoyée par le prochain appel à
	 *         next(); ou size()
	 * 
	 * @ensures \result == size() <==> !hasNext();
	 * @ensures hasNext() <==> \result >= 0 && \result < size();
	 * 
	 * @pure
	 */
	public int nextIndex() {
		
		switch (selectedState) {
			
			case OPEN:
				return openAds.nextIndex();
					
			case CLOSED:
				return closedAds.nextIndex();
				
			case PURCHASE:
				return purchases.nextIndex();
			
		}
		
		return 0;
	}

	/**
	 * Renvoie true si ce User possède une annonce plus récente pour l'itération en
	 * cours.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @return true si ce User possède une annonce plus récente pour l'itération en
	 *         cours
	 * 
	 * @ensures \result <==> previousIndex() >= 0;
	 * @ensures !\result <==> previousIndex() == -1;
	 * 
	 * @pure
	 */
	public boolean hasPrevious() {
		
		switch (selectedState) {
			
			case OPEN:
				return openAds.hasPrevious();
					
			case CLOSED:
				return closedAds.hasPrevious();
				
			case PURCHASE:
				return purchases.hasPrevious();
			
		}
		
		return false;
	}

	/**
	 * Renvoie l'annonce précedente (plus récente) dans l'itération en cours et
	 * recule d'un élément dans l'itération.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @return l'annonce précedente (plus récente) dans l'itération en cours
	 * 
	 * @requires hasPrevious();
	 * @ensures \result.equals(\old(get(previousIndex())));
	 * @ensures \result.equals(get(lastIndex()));
	 * @ensures getSelectedCategory().isPresent() ==><br/>
	 *          \result.getCategory().equals(getSelectedCategory().get());
	 * @ensures containsInState(getSelectedAdState(), \result);
	 * @ensures nextIndex() == \old(nextIndex()) - 1;
	 * @ensures previousIndex() == \old(previousIndex()) - 1;
	 * @ensures nextIndex() == \old(previousIndex());
	 * @ensures lastIndex() == \old(previousIndex());
	 * @ensures lastIndex() == nextIndex();
	 */
	public ClassifiedAd previous() {
		
		switch (selectedState) {
			
			case OPEN:
				return openAds.previous();
					
			case CLOSED:
				return closedAds.previous();
				
			case PURCHASE:
				return purchases.previous();
			
		}
		
		return null;
	}

	/**
	 * Renvoie l'index de l'annonce qui sera renvoyée par le prochain appel à
	 * previous(). Si l'itération est arrivée au début la valeur renvoyée est -1.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 * 
	 * @return l'index de l'annonce qui sera renvoyé par le prochain appel à previous();
	 *         ou -1
	 * 
	 * @ensures \result == -1 <==> !hasPrevious();
	 * @ensures hasPrevious() <==> \result >= 0 && \result < size();
	 * 
	 * @pure
	 */
	public int previousIndex() {
	
		switch (selectedState) {
			
			case OPEN:
				return openAds.previousIndex();
					
			case CLOSED:
				return closedAds.previousIndex();
				
			case PURCHASE:
				return purchases.previousIndex();
			
		}
		
		return 0;
	}
	
	/**
	 * Renvoie l'index de l'annonce qui a été renvoyée par le dernier appel à
	 * previous() ou next(). Si next() ou previous() n'ont pas été appelé depuis le
	 * dernier appel à startIteration() la valeur renvoyée est -1.
	 * 
	 * Cette itération ne concerne que le type d'annonces sélectionné (open ads,
	 * closed ads ou purchases).
	 * 
	 * Si une catégorie est sélectionnée, cette itération ne concerne que les
	 * annonces de cette catégorie.
	 *  
	 * @return l'index de l'annonce qui a été renvoyé par le dernier appel à
	 *         previous() ou next(); ou -1
	 * 
	 * @ensures \result == nextIndex() || \result == previousIndex();
	 * 
	 * @pure
	 */
	public int lastIndex() {
		
		switch (selectedState) {
			
			case OPEN:
				return openAds.lastIndex();
					
			case CLOSED:
				return closedAds.lastIndex();
				
			case PURCHASE:
				return purchases.lastIndex();
			
		}
		
		return 0;
	}
	
	/**
	 * Renvoie une chaîne de caractères contenant le nom de ce User ainsi que le
	 * nombre d'annonces de cet utilisateur dans les toirs états possibles (OPEN,
	 * CLOSED, PURCHASE).
	 * 
	 * @return une chaîne de caractères contenant le nom de ce User ainsi que le
	 *         nombre d'annonces de cet utilisateur
	 * 
	 * @ensures \result != null;
	 * @ensures \result.contains(getName());
	 * @ensures \result.contains("" + size(OPEN, Optional.empty()));
	 * @ensures \result.contains("" + size(CLOSED, Optional.empty()));
	 * @ensures \result.contains("" + size(PURCHASE, Optional.empty()));
	 * 
	 * @pure
	 */
	@Override
	public String toString() {
		return name + " a " + size(AdState.OPEN, Optional.empty()) + " annonces ouvertes, " + size(AdState.CLOSED, Optional.empty()) + " annonces fermées et " + size(AdState.PURCHASE, Optional.empty()) + " achats \n";
	}
	
}