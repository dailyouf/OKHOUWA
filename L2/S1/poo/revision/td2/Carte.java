public class Carte {
	
	private Famille f;
	private Rang r;
	
	
	/**
		Initialisation d'une carte
		
		@param	f	une instance de la classe Famille
		@param	r	une instance de la classe Rang
		
		@requires (f isistanceof Famille)
		@requires (r isistanceof Rang)
	
	*/
	public Carte(Famille f, Rang r) {
		
		this.f = f;
		this.r = r;
	
	}
	
	
	public Famille getFamille() {
		return f;
	}
	
	public Rang getRang() {
		return r;
	}
	
	/**
		Retroune la couleur de la carte
		
		@return	Couleur	la couleur de la carte
		
		@requires (f isistanceof Famille)
		@requires (r isistanceof Rang)
	
	*/
	public Couleur getCouleur() {
		
		if (f.equals(Famille.PIQUE) || f.equals(Famille.COEUR)) {
			return Couleur.ROUGE;
		}
		
		else  {
			return Couleur.NOIR;
		}
	
	}

	public String toString() {
		
		return (String) r.name() + " de " + f.name();
	
	}

}
