import java.util.Iterator;
import java.util.NoSuchElementException;

public class TabIterator<ObjetZork> implements Iterator<ObjetZork> {

	private ObjetZork[] tabObjs;
	private int nb, index;
	private boolean canRemove;	
	
	public TabIterator(ObjetZork[] objs, int nb) {
		
		this.nb = nb;
		tabObjs = (ObjetZork[]) new Object[10 + nb];
		for (int i=0; i<nb; i++) {
			tabObjs[i] = objs[i];
		} 
		this.index = 0;
		this.canRemove = false;
	}
	
	
	public boolean hasNext() {
		return (index < nb-1);
	}
	
	public ObjetZork next() {
		if (hasNext() == false) { 
			throw new NoSuchElementException();
		}
	
		index++;
		canRemove = true;
		return tabObjs[index];
	} 
	
	public void remove() {
		if (!canRemove) {
		    throw new IllegalStateException("remove() can only be called once per call to next()");
		}
		for (int i = index; i < nb - 1; i++) {
		    tabObjs[i] = tabObjs[i + 1];
		}
		tabObjs[nb - 1] = null;
		nb--;
		index--;
		canRemove = false;
    	}
}

