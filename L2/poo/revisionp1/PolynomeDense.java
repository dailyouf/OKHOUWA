import java.lang.Math;

public class PolynomeDense {
	
	private int[] tab;
	
	public	PolynomeDense() {
	
		tab = new int[1];
		
	}
		
	public	PolynomeDense(int coeff, int exp) {
	
		tab = new int[exp + 1];
		tab[exp] = coeff;
		
	}	
	
	public PolynomeDense additionner(PolynomeDense p) {
		
		int degre = (getDegre() < p.getDegre()) ? getDegre() : p.getDegre();
		
		if (getDegre() == p.getDegre()) {
			while ((getCoefficient(degre) - p.getCoefficient(degre) == 0) && (degre > 0)) {
				degre--;	
			}
		}
		
		PolynomeDense res = new PolynomeDense(getCoefficient(degre), degre);
		
		int i;
		for (i=0; i<degre; i++){
			res.tab[i] = getCoefficient(i) + p.getCoefficient(i);
		}
		 
		 return res;
		
		
	}
	
	public boolean equals(Object obj) {
		
		int i;
		
		if (! (obj instanceof PolynomeDense)) {
			return false;
		}
		
		PolynomeDense tmp = (PolynomeDense) obj;
		
		if (tmp.getDegre() != getDegre()) {
			return false;
		}
			
		for (i=0; i<tab.length; i++) {		
			if (tmp.getCoefficient(i) != getCoefficient(i)) {
				return false;
			}  
		}
		
		return true;
	}
	
	
	public boolean estZero() {
		
		int i;
		
		for (i=0; i<tab.length; i++) {		
			if (this.getCoefficient(i) != 0) {
				return false;
			}  
		}
		
		return true;
	
	}
	
	public double evaluer(double x) {
	
		int i;
		double res;
		
		for (i=0; i<tab.length; i++) {
			res += Math.pow(x, i) * tab[i];	
		}
		
		return res;
		
		
		// ne pas prendre en compte l'odre lorsqu'il on a pas une liste ordonné: exxemple: on renvoi pas
	}
	
	
	public int getCoefficient(int i) {
	
		if (i <= tab.length) {
			return 0;
		}	
		
		return tab[i];
		
	} 
	
	public int getDegre() {
		return tab.length - 1;
	}
	
	
	public int hashCode() {
		return 22;
	}
	
	public String toString() {
		
		String s = "Poly: ";
		
		int i;
		
		for(i=0; i<tab.length; i++) {
			if (tab[i] != 0) {
				s += Integer.toString(tab[i]) + ".X^" + Integer.toString(i);
				break;	
			}
		}
		
		for(; i<tab.length; i++) {
			if (tab[i] != 0) {
				s += " + " + Integer.toString(tab[i]) + ".X^" + Integer.toString(i);	
			}
		}
		
		return s;
	}	
	
	

}
