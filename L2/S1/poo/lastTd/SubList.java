import java.lang.reflect.Array;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * <p>Une vue d'une portion d'une liste entre les index <code>startInSupportList()</code> (inclu)
 * et <code>endInSupportList()</code> (exclu). Si ces deux index sont égaux cette sous-liste est vide.
 * Une telle sous-liste satisfait complètement le contrat devant satisfaire une liste retournée par la
 * méthode <code>List&lt;E&gt; subList(int fromIndex, int toIndex)</code> définie dans l'interface
 * <code>List&lt;E&gt;</code>.</p>
 *
 * <p>La structure de données servant à mémoriser les éléments d'une sous-liste telle que définie dans
 * cette classe est la structure de données de la liste dont elle représente une vue. Dans cette documentation
 * cette liste est appelée "liste support" (ou "support List"). La structure de données des deux listes
 * étant la même, toute modification opérée sur une sous-liste est une modification de sa liste support. De la
 * même manière, toute modification non structurelle de la liste support concernant les éléments d'une de
 * ses sous-listes est une modification de cette sous-liste.</p>
 *
 *  <p>Une sous-liste supporte exactement les mêmes opérations optionnelles que sa liste support,
 *  de la même manière le comportement d'une sous-liste par rapport aux caractéristiques des éléments
 *  qu'elle peut contenir (par exemple, si elle admet ou non des éléments <code>null</code>) est le
 *  même que celui de sa liste support.</p>
 *
 *  <p>La maintien du contrat d'une sous-liste n'est pas garantie si sa liste support est modifiée
 *  struturellement sans utiliser les operations de cette sous-liste. On appelle modifications structurelles
 *  celles qui changent la taille de la liste (i.e. suppriment ou ajoutent des éléments à la liste).</p>
 *
 * @see java.util.List
 * @see java.util.List#subList(int, int)
 *
 * @invariant this.equals(getSupportList().subList(startInSupportList(), endInSupportList()));
 * @invariant size() <= getSupportList().size();
 * @invariant startInSupportList() <= endInSupportList();
 * @invariant size() == (endInSupportList() - startInSupportList());
 *
 * @author Marc Champesme
 * @since 19 janvier 2008
 * @version 20 janvier 2008
 *
 */
public class SubList<E> implements List<E> {

	private int start, end;
	private List<E> ls;

	/**
	 * Initialise une sous-liste de la liste support spécifiée. Cette sous-liste est constituée des
	 * éléments de la liste support dont les index sont compris entre les deux index spécifiés (i.e.
	 * fromIndex et toIndex).
	 *
	 * @requires support != null;
	 * @requires fromIndex >= 0 && toIndex <= support.size() && fromIndex <= toIndex;
	 * @ensures getSupportList() == support;
	 * @ensures startInSupportList() == fromIndex;
	 * @ensures endInSupportList() == toIndex;
	 * @ensures (fromIndex == toIndex) ==> isEmpty();
	 *
	 * @param support la liste "support" dont on veut une sous-liste
	 * @param fromIndex index du premier élément de la liste support appartenant à cette sous-liste
	 * @param toIndex index du premier élément de la liste support (après le premier élément) n'appartenant
	 * pas à cette sous-liste.
	 * @throws IndexOutOfBoundsException si un des deux index fournis n'est pas valide
	 *  (fromIndex < 0 || toIndex > support.size() || fromIndex > toIndex).
	 * @throws NullPointerException si la liste support spécifiée est <code>null</code>.
	 */
	public SubList(List<E> l, int start, int end) {
		
		if (l == null)
			throw new NullPointerException();
		
		if ((start < 0 || (end >= l.size()) || (start > end))
			throw new IndexOutOfBoundsException();
			

		ls = List<E> l;
		this.start = start;
		this.end = end;
	
	}

	/**
	 * Renvoie la liste support de cette sous-liste.
	 *
	 * @ensures \result != null;
	 *
	 * @return la liste support de cette sous-liste
	 */
	public List<E> getSupportList() {
		return ls;
	}

	/**
	 * Renvoie l'index du premier élément de cette liste dans la liste support.
	 *
	 * @ensures \result <= endInSupportList();
	 * @ensures \result >= 0;
	 *
	 * @return l'index du premier élément de cette liste dans la liste support.
	 */
	public int startInSupportList() {
		return start;
	}

	/**
	 * L'index du premier élément de la liste support (après le premier élément) n'appartenant
	 * pas à cette sous-liste ou getSupportList().size() si cette sous-liste et sa liste support
	 * ont le même dernier élément.
	 *
	 * @ensures \result >= startInSupportList();
	 * @ensures \result <= getSupportList().size();
	 *
	 * @return L'index du premier élément de la liste support (après le premier élément) n'appartenant
	 * pas à cette sous-liste ou getSupportList().size() si
	 */
	public int endInSupportList() {
		return end;
	}

	public boolean indexInRange(int index) {
		return ((index >= start) && (index < end));
	}

	/* (non-Javadoc)
	 * @see java.util.List#add(java.lang.Object)
	 */
	 @Override
	public boolean add(E o) {
		end++;
		return ls.add(start, o);
	}

	/* (non-Javadoc)
	 * @see java.util.List#add(int, java.lang.Object)
	 */
	 @Override
	public void add(int index, E element) {
		if ((index < 0 || (index > end))
			throw new IndexOutOfBoundsException();
			
		end++;
		ls.add(start + index, o);
	}

	/* (non-Javadoc)
	 * @see java.util.List#addAll(java.util.Collection)
	 */
	 @Override
	public boolean addAll(Collection<? extends E> c) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#addAll(int, java.util.Collection)
	 */
	 @Override
	public boolean addAll(int index, Collection<? extends E> c) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#clear()
	 */
	 @Override
	public void clear() {
		
	}

	/* (non-Javadoc) 
	 * @see java.util.List#contains(java.lang.Object)
	 */
	 @Override
	public boolean contains(Object o) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#containsAll(java.util.Collection)
	 */
	 @Override
	public boolean containsAll(Collection<?> c) {
		return true;
	}

	/* (non-Javadoc)
	 * @see java.util.List#get(int)
	 */
	 @Override
	public E get(int index) {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#indexOf(java.lang.Object)
	 */
	 @Override
	public int indexOf(Object o) {
		return -1;
	}

	/* (non-Javadoc)
	 * @see java.util.List#isEmpty()
	 */
  @Override
	public boolean isEmpty() {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#iterator()
	 */
	 @Override
	public Iterator<E> iterator() {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#lastIndexOf(java.lang.Object)
	 */
	 @Override
	public int lastIndexOf(Object o) {
		return -1;
	}

	/* (non-Javadoc)
	 * @see java.util.List#listIterator()
	 */
	 @Override
	public ListIterator<E> listIterator() {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#listIterator(int)
	 */
	 @Override
	public ListIterator<E> listIterator(int index) {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#remove(java.lang.Object)
	 */
	 @Override
	public boolean remove(Object o) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#remove(int)
	 */
	 @Override
	public E remove(int index) {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#removeAll(java.util.Collection)
	 */
	 @Override
	public boolean removeAll(Collection<?> c) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#retainAll(java.util.Collection)
	 */
	 @Override
	public boolean retainAll(Collection<?> c) {
		return false;
	}

	/* (non-Javadoc)
	 * @see java.util.List#set(int, java.lang.Object)
	 */
	 @Override
	public E set(int index, E element) {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#size()
	 */
	 @Override
	public int size() {
		return -1;
	}

	/* (non-Javadoc)
	 * @see java.util.List#subList(int, int)
	 */
	 @Override
	public List<E> subList(int fromIndex, int toIndex) {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#toArray()
	 */
	 @Override
	public Object[] toArray() {
		return null;
	}

	/* (non-Javadoc)
	 * @see java.util.List#toArray(T[])
	 */
	@SuppressWarnings("unchecked")
	@Override
	public <T> T[] toArray(T[] a) {
		T[] anArray = null;
		if (a.length >= size()) {
			anArray = a;
		} else {
			anArray = (T[]) Array.newInstance(a.getClass(), size());
		}
		int index = 0;
		for (E elt : this) {
			anArray[index] = (T) elt;
			index++;
		}
		return anArray;
	}

	@Override
	public boolean equals(Object o) {
		return true;
	}

	@Override
	public int hashCode() {
		return -1;
	}

	@Override
	public String toString() {
		return null;
	}
}
