/**
* @author Youcef GHEDAMSI 12302243
* Je déclare qu'il s'agit de mon propre travail
*/

package minebay;


/**
 * Un utilisateur de l'application MinEbay.
 * 
 * <p>
 * Un User est caractérisé par:
 * <ul>
 * <li>son nom et son mot de passe</li>
 * <li>le montant disponible sur son compte bancaire</li>
 * <li>sa date d'inscription sur MinEbay (= date de création de l'instance de
 * l'User)</li>
 * <li>la liste des annonces qu'il a posté et pour lesquelles il n'a pas trouvé
 * d'acheteur (annonces dans l'état OPEN)</li>
 * <li>la liste des annonces qu'il a posté et pour lesquelles il a vendu l'objet
 * concerné (annonces dans l'état CLOSED)</li>
 * <li>la liste des annonces (d'autres utilisateurs) pour lesquelles il a acheté
 * l'objet concerné (annonces dans l'état PURCHASE)</li>
 * </ul>
 * </p>
 * 
 * <p>
 * Chacune des trois listes d'annonces d'un User est représentée en utilisant
 * une instance de MultiEnumList. Cela permet d'effectuer des itérations portant
 * uniquement sur des annonces appartenant à un sous-ensemble de catégories,
 * sans qu'il soit besoin de créer des listes intermédiaires contenant ces
 * annonces. Comme pour les MultiEnumList, il est fortement déconseillé
 * d'utiliser les méthodes get pour effectuer un parcours de liste, l'usage d'un
 * itérateur est hautement préférable.
 * </p>
 * 
 * <p>
 * Les méthodes ne possédant pas de paramètre de type AdState ou Set<AdCategory>
 * agissent uniquement sur les annonces dont l'état et la catégorie a été
 * sélectionnée.
 * </p>
 * 
 * 
 * @invariant getName() != null && !getName().isBlank();
 * @invariant getPassword() != null && !getPassword().isBlank();
 * @invariant getRegistrationDate() != null;
 * @invariant getAvailableCash() >= 0;
 * @invariant (\forall AdState state; true; !contains(state, null));
 * @invariant (\forall int i, j; i >= 0 && i < j && j < size();
 *            get(i).isAfter(get(j)));
 * @invariant (\forall AdState state, AdCategory cat;true; <br/>
 *            (\forall int i, j; <br/>
 *            i >= 0 && i < j && j < size(state, EnumSet.of(cat)); get(state,
 *            EnumSet.of(cat), i).isAfter(get(state, EnumSet.of(cat), j))));
 * 
 * @author Marc Champesme
 * @since 27/09/2024
 * @version 26/11/2024
 * 
 */
public class User implements Iterable<ClassifiedAd> {

	/**
	 * Initialise une nouvelle instance ayant les nom et mot de passe spécifiés. La
	 * date d'inscription du nouvel utilisateur est la date au moment de l'exécution
	 * de ce constructeur. L'état sélectionné est OPEN et toutes les catégories sont
	 * sélectionnées.
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
	 * @ensures getSelectedCategories().equals(EnumSet.allOf(AdCategory.class));
	 * 
	 * @throws NullPointerException     si l'un des arguments spécifiés est null
	 * @throws IllegalArgumentException si l'un des arguments spécifiés ne contient
	 *                                  que des caractères blancs ou ne contient
	 *                                  aucun caractères
	 */
	public User(String userName, String password) {
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
		return null;
	}

	/**
	 * Sélectionne l'état spécifié.
	 * 
	 * @param state état à sélectionner pour les annonces
	 * 
	 * @requires state != null;
	 * @ensures getSelectedAdState().equals(state);
	 * @ensures getSelectedCategory().equals(\old(getSelectedCategory()));
	 * 
	 * @throws NullPointerException si l'état spécifié est null
	 */
	public void selectAdState(AdState state) {
	}

	/**
	 * Ajoute la catégorie spécifiée à l'ensemble des catégories sélectionnées.
	 * 
	 * @param cat catégorie à ajouter aux catégories sélectionnées pour les annonces
	 * 
	 * @return true si l'ensemble des catégories sélectionnées a changé; false sinon
	 * 
	 * @requires cat != null;
	 * @ensures !getSelectedCategories().isEmpty();
	 * @ensures getSelectedCategories().contains(cat);
	 * @ensures \result <==> !\old(getSelectedCategories().contains(cat));
	 * @ensures !\result ==>
	 *          getSelectedCategories().equals(\old(getSelectedCategories()));
	 * 
	 * @throws NullPointerException si la catégorie spécifiée est null
	 */
	public boolean addSelectedCategory(AdCategory cat) {
		return false;
	}

	/**
	 * Retire la catégorie spécifiée de l'ensemble des catégories sélectionnées.
	 * 
	 * @param cat catégorie à retirer des catégories sélectionnées pour les annonces
	 * 
	 * @return true si l'ensemble des catégories sélectionnées a changé; false sinon
	 * 
	 * @ensures !getSelectedCategories().contains(cat);
	 * @ensures \result <==> \old(getSelectedCategories().contains(cat));
	 * @ensures !\result ==>
	 *          getSelectedCategories().equals(\old(getSelectedCategories()));
	 */
	public boolean removeSelectedCategory(Object obj) {
		return false;
	}

	/**
	 * Renvoie une vue non modifiable de l'ensemble des catégories actuellement
	 * sélectionnées. Si aucune catégorie n'est sélectionnée, renvoie un ensemble
	 * vide.
	 * 
	 * @return un ensemble contenant les catégories actuellement sélectionnées
	 * 
	 * @ensures \result != null;
	 * 
	 * @pure
	 */
	public Set<AdCategory> getSelectedCategories() {
		return null;
	}

	/**
	 * Déselectionne toutes les catégories précédemment sélectionnées.
	 * 
	 * @return true si l'ensemble des catégories sélectionnées a changé; false sinon
	 * 
	 * @ensures getSelectedCategories().isEmpty();
	 */
	public boolean clearSelectedCategories() {
		return false;
	}

	/**
	 * Sélectionne toutes les catégories.
	 * 
	 * @return true si l'ensemble des catégories sélectionnées a changé; false sinon
	 * 
	 * @ensures getSelectedCategories().equals(EnumSet.allOf(AdCategory.class));
	 */
	public boolean selectAllCategories() {
		return false;
	}

	/**
	 * Renvoie le nom de cet utilisateur.
	 * 
	 * @return le nom de cet utilisateur
	 * 
	 * @pure
	 */
	public String getName() {
		return null;
	}

	/**
	 * Renvoie le mot de passe de cet utilisateur.
	 * 
	 * @return le mot de passe de cet utilisateur
	 * 
	 * @pure
	 */
	public String getPassword() {
		return null;
	}

	/**
	 * Renvoie l'Instant représentant la date d'inscription de cet utilisateur.
	 * 
	 * @return la date d'inscription de cet utilisateur
	 * 
	 * @pure
	 */
	public Instant getRegistrationDate() {
		return null;
	}

	/**
	 * Renvoie la somme d'argent disponible pour cet utilisateur pour acheter des
	 * objets.
	 * 
	 * @return la somme d'argent disponible pour cet utilisateur
	 * 
	 * @pure
	 */
	public int getAvailableCash() {
		return -1;
	}

	/**
	 * Achète à l'utilisateur spécifié l'objet présenté dans l'annonce spécifiée.
	 * Pour le vendeur l'annonce passe de la liste des annonces OPEN à la liste des
	 * annonces CLOSED et il reçoit le montant du prix de l'objet présenté dans
	 * l'annonce. Pour ce User, l'annonce est ajoutée à la liste des annonces
	 * PURCHASE et sa somme d'argent disponible est diminuée du prix de l'objet.
	 * 
	 * @param vendor l'utilisateur auteur de l'annonce spécifiée
	 * @param ad     l'annonce de l'objet à acheter
	 * 
	 * 
	 * @requires vendor != null;
	 * @requires this != vendor;
	 * @requires ad != null;
	 * @requires vendor.containsInState(OPEN, ad);
	 * @requires getAvailableCash() >= ad.getPrice();
	 * @ensures containsInState(PURCHASE, ad);
	 * @ensures size(PURCHASE, EnumSet.of(ad.getCategory()))<br/>
	 *          == \old(size(PURCHASE, EnumSet.of(ad.getCategory()))) + 1;
	 * @ensures !vendor.containsInState(OPEN, ad);
	 * @ensures vendor.size(OPEN, EnumSet.of(ad.getCategory())) ==
	 *          \old(vendor.size(OPEN, EnumSet.of(ad.getCategory()))) - 1;
	 * @ensures vendor.containsInState(CLOSED, ad);
	 * @ensures vendor.size(CLOSED, EnumSet.of(ad.getCategory())) ==
	 *          \old(vendor.size(CLOSED, EnumSet.of(ad.getCategory()))) + 1;
	 * @ensures getAvailableCash() == \old(getAvailableCash()) - ad.getPrice();
	 * @ensures vendor.getAvailableCash() == \old(vendor.getAvailableCash()) +
	 *          ad.getPrice();
	 * 
	 * @throws NullPointerException     si un des deux arguments spécifié est null
	 * @throws IllegalArgumentException si l'annonce spécifiée n'est pas une annonce
	 *                                  OPEN du vendeur spécifié ou si le vendeur
	 *                                  spécifié est ce User
	 * @throws IllegalStateException    si l'argent disponible de ce User est
	 *                                  inférieur au prix de l'annonce spécifiée
	 */
	public void buy(User vendor, ClassifiedAd ad) {
	}

	/**
	 * Crée et renvoie une nouvelle instance de ClassifiedAd dont les
	 * caractéristiques sont les arguments spécifiés et l'ajoute à la liste des
	 * annonces ouvertes (open ads) de cet utilisateur. La date de cette annonce est
	 * la date d'exécution de cette méthode.
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
	 * @ensures get(OPEN, EnumSet.of(cat), 0).equals(\result);
	 * @ensures \result.getCategory().equals(cat);
	 * @ensures \result.getDescription().equals(msg);
	 * @ensures \result.getPrice() == price;
	 * @ensures size(OPEN, EnumSet.of(cat)) == \old(size(OPEN, EnumSet.of(cat))) +
	 *          1;
	 * @ensures oldDate.isBefore(\result.getDate());
	 * @ensures \result.getDate().isBefore(Instant.now());
	 * 
	 * @throws NullPointerException     si la catégorie ou la description sont null
	 * @throws IllegalArgumentException si le prix spécifié est inférieur ou égal à
	 *                                  0 ou la description de l'objet ne contient
	 *                                  pas de caractères
	 * 
	 */
	public ClassifiedAd add(AdCategory cat, String msg, int price) {
		return null;
	}

	/**
	 * Renvoie le nombre d'annonces de cet utilisateur dans l'état sélectionné
	 * (open, closed ou purchase) et appartenant à une des catégories sélectionnées
	 * seules les annonces de cette catégorie sont comptées.
	 * 
	 * @return le nombre d'annonces de cet utilisateur dans l'état et la catégorie
	 *         sélectionnés.
	 * 
	 * @ensures \result == size(getSelectedAdState(), getSelectedCategories());
	 * @ensures getSelectedCategories().isEmpty() ==> \result == 0;
	 * 
	 * @pure
	 */
	public int size() {
		return -1;
	}

	/**
	 * Renvoie le nombre d'annonces de cet utilisateur dans l'état spécifié et
	 * appartenant à une des catégories appartenant à l'ensemble spécifié.
	 * 
	 * @param state  état des annonces
	 * @param catSet ensemble de catégories d'annonces
	 * 
	 * @requires state != null;
	 * @requires catSet != null;
	 * @ensures \result >= 0;
	 * @ensures getSelectedAdState().equals(state) &&
	 *          getSelectedCategories().equals(catSet) <br/>
	 *          ==> \result == size();
	 * @ensures catSet.isEmpty() ==> \result == 0;
	 * 
	 * @return le nombre d'annonces de cet utilisateur dans l'état spécifié et
	 *         appartenant à une des catégories appartenant à l'ensemble spécifié
	 * 
	 * @throws NullPointerException si l'un des paramètres est null
	 * 
	 * @pure
	 */
	public int size(AdState state, Set<AdCategory> catSet) {
		return -1;
	}

	/**
	 * Renvoie la ième plus récente annonce de ce User dans l'état sélectionné et
	 * dont la catégorie appartient à l'ensemble de catégories sélectionnées.
	 * 
	 * @param i index de l'annonce cherchée
	 * 
	 * @return la ième plus récente annonce de ce User
	 * 
	 * @requires i >= 0 && i < size();
	 * @ensures \result != null;
	 * @ensures \result.equals(get(getSelectedAdState(), getSelectedCategories(),
	 *          i);
	 * 
	 * @throws IndexOutOfBoundsException si l'index spécifié est strictement
	 *                                   inférieur à 0 ou supérieur ou égal à size()
	 * 
	 * @pure
	 */
	public ClassifiedAd get(int i) {
		return null;
	}

	/**
	 * Renvoie le ième élément de la liste des annonces étant dans l'état spécifié
	 * et dont la catégorie appartient à l'ensemble de catégories spécifié.
	 * 
	 * @param state  l'état des annonces
	 * @param catSet ensemble des catégories d'annonces concernées
	 * @param i      index de l'élément dans la liste
	 * 
	 * @return le ième élément de la liste des annonces étant dans l'état spécifié
	 *         et dont la catégorie appartient à l'ensemble de catégories spécifié
	 * 
	 * @requires state != null;
	 * @requires catSet != null;
	 * @requires i >= 0 && i < size(state, catSet);
	 * @ensures \result != null;
	 * @ensures containsInState(state, \result);
	 * @ensures catSet.contains(\result.getCategory());
	 * 
	 * @throws NullPointerException      si l'état spécifié ou l'ensemble de
	 *                                   catégories spécifié est null
	 * @throws IndexOutOfBoundsException si l'index spécifié est strictement
	 *                                   inférieur à 0 ou supérieur ou égal à
	 *                                   size(state, catSet)
	 * 
	 * @pure
	 */
	public ClassifiedAd get(AdState state, Set<AdCategory> catSet, int i) {
		return null;
	}

	/**
	 * Renvoie true si ce User possède parmi les annonces dans l'état spécifié,
	 * l'objet spécifié.
	 * 
	 * @param state état des annonces parmi lesquelles l'objet est recherché
	 * @param obj   objet cherchée
	 * @return true si ce User possède parmi les annonces dans l'état spécifié,
	 *         l'objet spécifié; false sinon
	 * 
	 * @requires state != null;
	 * @ensures !(obj instanceof ClassifiedAd) ==> !\result;
	 * @ensures \result <==> (\exists int i; <br/>
	 *          i >= 0 && i < size(state, EnumSet.allOf(AdCategory.class)); <br/>
	 *          get(state, EnumSet.allOf(AdCategory.class), i).equals(obj));
	 * @pure
	 */
	public boolean containsInState(AdState state, Object obj) {
		return false;
	}

	/**
	 * Renvoie un itérateur sur les annonces dans l'état sélectionné et appartenant
	 * à une des catégories sélectionnées.
	 * 
	 * @return un itérateur sur les annonces dans l'état sélectionné et appartenant
	 *         à une des catégories sélectionnées
	 * 
	 * @ensures \result != null;
	 * @ensures size() > 0 ==> \result.hasNext();
	 * 
	 * @pure
	 */
	public ListIterator<ClassifiedAd> iterator() {
		return null;
	}

	/**
	 * Renvoie un itérateur sur les annonces dans l'état spécifié et dont la
	 * catégories appartient à l'ensemble spécifié.
	 * 
	 * @return un itérateur sur les annonces dans l'état spécifié et dont la
	 *         catégories appartient à l'ensemble spécifié
	 * 
	 * @ensures \result != null;
	 * @ensures size(state, catSet) > 0 ==> \result.hasNext();
	 * 
	 * @throws NullPointerException si l'état spécifié ou l'ensemble de catégories
	 *                              spécifié est null
	 * 
	 * @pure
	 */
	public ListIterator<ClassifiedAd> iterator(AdState state, Set<AdCategory> catSet) {
		return null;
	}

	/**
	 * Renvoie une chaîne de caractères contenant le nom de ce User ainsi que le
	 * nombre d'annonces de cet utilisateur dans les trois états possibles (OPEN,
	 * CLOSED, PURCHASE).
	 * 
	 * @return une chaîne de caractères contenant le nom de ce User ainsi que le
	 *         nombre d'annonces de cet utilisateur
	 * 
	 * @ensures \result != null;
	 * @ensures \result.contains(getName());
	 * @ensures \result.contains("" + size(OPEN, EnumSet.allOf(AdCategory.class)));
	 * @ensures \result.contains("" + size(CLOSED, EnumSet.allOf(AdCategory.class)));
	 * @ensures \result.contains("" + size(PURCHASE, EnumSet.allOf(AdCategory.class)));
	 * 
	 * @pure
	 */
	@Override
	public String toString() {
		return null;
	}
}
