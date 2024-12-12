import java.util.Collection;
import java.util.HashSet;

class Relation<E,F> implements Cloneable {
	
	private HashSet<Couple<E, F>> contenu;
	
	public Relation() {		
		contenu = new HashSet<Couple<E, F>>();
	}
	
	public Relation(Collection<? extends Couple<E, F>> c) {		
		contenu = new HashSet<Couple<E, F>>(c);
	}
	
	public boolean add(E e, F f) {
		return contenu.add(new Couple<E, F>(e, f));
	} 
	
	public boolean contains(Object e, Object f) {
		return contenu.contains(new Couple<>(e, f));
	} 
	
	public boolean equals(Object obj) {
		if (!(obj instanceof Relation<?, ?>)) {
			return false;
		}
		
		Relation<E,F> cpy = (Relation<E,F>) obj;
		
		return contenu.equals(cpy.contenu);
		
	} 
	
	public int hashCode() {
		return contenu.hashCode();
	}
	
	public String toString() {
		return contenu.toString();
	}
	
	public Relation<E,F> clone() {
		Relation<E,F> cln = new Relation<E, F>();
		cln.contenu = (HashSet<Couple<E, F>>) this.contenu.clone();
		return cln;
	}
}
