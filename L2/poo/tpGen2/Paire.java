import java.util.Collection;
import java.util.AbstractSet;

public class Paire<E> extends AbstractSet<E> {
	
	private E e, f;
	
	public Paire(E e, E f) {
		this.e = e;
		this.f = f;
	}
	
	@Override
        public Iterator<T> iterator() {
        	return Set.of(e, f).iterator();
        }
	
	
        @Override
        public int size() {
                return 2;
        }

        @Override
        public boolean contains(Object o) {
                return o.equals(premier) || o.equals(second);
        }

        @Override
        public String toString() {
                return "[" + premier + ", " + second + "]";
        }

}
