class ObjetEcoZork {

	private final String nom;
	private final int poids;
	private final boolean compostable;
	private ArrayList<> = new ArrayList<>();

	/**
	 * Initialise une 
	
	*/
	public ObjetEcoZork() {
	}


	public boolean equals(Object obj) {
		
		if (! (obj instanceof ObjetEcoZork)) {
			return false;
		}
		
		ObjetEcoZork copie = (ObjetEcoZork) obj;
		
		return (nom==copie.nom && poids==copie.poids && compostable==copie.compostable)
	}
	
	public Object clone() {
		
		ObjetEcoZork clone=null;
		
		try {
			clone = (ObjetEcoZork) super.clone();
		} 
		catch (CloneNotSupportedException e){
			throw new InternalError();
		}
		
		return (Object) clone;
	}
}
