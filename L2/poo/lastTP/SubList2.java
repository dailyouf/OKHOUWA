import java.util.AbstractSequentialList;

public class SubList2<E> extends AbstractSequentialList<E> {

	private int start, end;
	private List<E> ls;

	public SubList(List<E> l, int start, int end) {
		
		if (l == null)
			throw new NullPointerException();
		
		if ((start < 0 || (end >= l.size()) || (start > end))
			throw new IndexOutOfBoundsException();
			

		ls = List<E> l;
		this.start = start;
		this.end = end;
	
	}
	
	public ListIterator<E> listIterator(int index) {
		return new SeqListIterator(ls.ListIterator(start), start, end);
	}
	
	public int size() {
		return end - start;
	}
	
	public void add(int index, E elt) {
		if ((index < 0 || (index > end))
			throw new IndexOutOfBoundsException();
			
		end++;
		ls.add(start + index, o);
	}
	
	
	public void remove(int index) {
		if ((index < 0 || (index >= end))
			throw new IndexOutOfBoundsException();
			
		end--;
		ls.remove(start + index);
	}
	

}
