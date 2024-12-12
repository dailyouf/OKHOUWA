import java.awt.geom.Point2D;
import java.awt.Point;

public class Polynome {
	
	private Point2D sommets[];
	
	public Polynome(Point2D[] points, int nb) {
		sommets = new Point[nb];
		for (int i=0; i<nb; i++) {
			sommets[i] = (Point2D) points[i].clone();
		}
	}
	
	public int nbSommets() {	
		return sommets.length;	
	}
	
	public Point2D getSommet(int i) {
		return sommets[i];
	}
	
	public double getLgCote(int i) {
		return sommets[i].distance(sommets[i+1]);
	}
	
	public double getPerimetre() {
		
		double res=0;
			
		for (int i=0; i<nbSommets()-1; i++) {
			res += getLgCote(i);
		}
		
		return res;
	
	}
	
	@Override
	public boolean equals(Object obj) {
		
		if (! (obj instanceof Polynome)) {
			return false;
		}
		
		Polynome tmp = (Polynome) obj;
		
		if (nbSommets() != tmp.nbSommets()) return false;
		
		for (int i=0; i<nbSommets(); i++) {
			/* A utiliser au dépend de l'implémentation
			if ((! getSommet(i).equals(tmp.getSommet(i)) || (getLgCote(i) != tmp.getLgCote(i)))) return false;
			*/
			if (getLgCote(i) != tmp.getLgCote(i)) return false;
		}
		
		return true;
		
	}
	
	@Override
	public int hashCode() {
		// Flemme de réflichir (je suis fatigué)
		
		return (int) getPerimetre();
	}
	
	@Override
	public String toString() {
		String res = "";
		
		res += "Le polynome est composé des " + Integer.toString(nbSommets()) + " sommets: \n";
		
		for (int i=0; i<nbSommets(); i++) {
			res += getSommet(i).toString() + '\n';
		}
		
		return res;
		
		
	}
	
	@Override
	public Polynome clone() {
	
		Polynome p;
		
		try {
			p = (Polynome) super.clone();
		}
		catch (CloneNotSupportedException e) {
			throw new InternalError();
		}
		
		return p;
		
	}	 

}
