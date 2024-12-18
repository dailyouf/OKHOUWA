import java.util.AbstractList;

public class SubList<E> extends AbstractList<E> {

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
	
	public List<E> getSupportList() {
		return ls;
	}
	
	public int startInSupportList() {
		return start;
	}
	
	public int endInSupportList() {
		return end;
	}
	
	public boolean indexInRange(int index) {
		return ((index >= start) && (index < end));
	}
	
	public E get(int i) {		
		return ls.get(i+start);
	}
	
	public int size() {
		return end - start;
	}
	
	
	public set(int index, E elt) {
		return ls.set(index + start, elt);
	}
	
	public void add(int index, E element) {
		if ((index < 0 || (index > end))
			throw new IndexOutOfBoundsException();
			
		end++;
		ls.add(start + index, o);
	}
	
	
	public void remove(int index) {
		if ((index < 0 || (index > end))
			throw new IndexOutOfBoundsException();
			
		end--;
		ls.remove(start + index);
	}



}
