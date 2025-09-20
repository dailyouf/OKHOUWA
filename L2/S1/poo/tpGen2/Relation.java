import java.util.Collection;
import java.util.HashSet;

public class Relation<E> extends HashSet<Paire<E>> {
	
	public Relation() {
		super();
	}
	
	public Relation(Collection<? extends Paire<E>> c) {
		super(c);
	}
		
		
	public boolean add(E e, E f) {
		return add(new Paire<E>(e, f));
	} 
	
	public boolean contains(Object e, Object f) {
		return contains(new Paire<?>(e, f));
	} 
}

