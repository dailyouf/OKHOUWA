class Monome {

	int coef, exp;
	
	public Monome() {
		coef = 0;
		exp = 0;
	}

	public Monome(int coef, int exp) {
		
		this.coef = coef;
		this.exp = exp;
	
	}
	
	PolynomeDense additionner(Monome m) {
		PolynomeDense p1 = PolynomeDense(coef, exp);
		return p1.additionner(PolynomeDense(m.coef, m.exp));
	}
	
	
	public boolean equals(Object obj) {
		
		int i;
		
		if (! (obj instanceof Monome)) {
			return false;
		}
		
		Monome tmp = (Monome) obj;
		
		return (tmp.coef == this.coef && tmp.exp == this.exp);
		
	}
	
	
	public boolean estZero() {
		
		if (exp==0 && coef==0) return true;
		
		return false;
	}
	
	public double evaluer(double x) {
		
		double res = 1;
		
		for (int i=0; i<exp; i++) {
			res *= x;
		}	
		
		return res * coef;
	}
	
	
	public int getCoefficient(int i) {
	
		return this.coef;
		
	} 
	
	public int getDegre() {
		return exp;
	}
	
	
	public int hashCode() {
		return coef * exp;
	}
	
	public String toString() {
		
		String s = "Monome: ";
		
		return s + Integer.toString(coef) + ".X^" + Integer.toString(exp);
	}	
	
	
}
