import java.util.ListIterator;

public class SeqListIterator<E> implements ListIterator<E> {
	
	int start, end, index;
	ListIterator<E> iter;
		
	public SeqListIterator(ListIterator<E> it, int start, int end) {
		iter = it;
		this.start = start;
		this.end  = end;	
		index = start;
	}
	
	
	
	public int index() {
		return index;
	}
	
	public boolean hasNext() {
		return index < end;
	}
	
	public boolean hasPrevious() {
		return index > start;
	}
	
	public E next() {
		index++;
		return iter.next();
	}
	
	public E previous() {
		index--;
		return iter.previous();
	}
	
	

}

