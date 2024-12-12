public class ArrayConteneur extends AbstractConteneur {

	private ObjetZork[] tabObjets;


	public ArrayConteneur(){
		tabObjets = new ObjetZork[10];
	}
	
	/**
	 * @throws NullPointerException si tab est null ou contient null
	 * @throws IllegalArgumentsException si nb<0 ou nb>tab.length
	 */
	public ArrayListConteneur(ObjetZork[] objs, int nb){
		
		tabObjets = new ObjetZork[nb];
		
		if (objs == null) {
			throw new NullPoiterException("l'objet fourni en arguemnt est null");
		}
		
		if (nb<0 || nb>objs.length) {
			throw new IllegalArgumentException("arugments non valides");
		}
		
		for (int i=0; i<nb; i++) {
			if (objs[i] == null) {
				throw new NullPoiterException("l'objet fourni en arguemnt est null");
			}
			
			tabObjets[i] = objs[i];
		}  
		
	}
	
	
	
	/**
	 * @trows NullPointerException si l'arguement objet est null
	 * @trows IllegalStateException si !ajoutEstPossible(oz)
	 */
	public boolean ajouter(ObjetZork oz) {
		
		if (oz == null) {
			throw new NullPointerException("l'objet fourni en arguemnt est null");
		}
		
		if (! ajoutEstPossible(oz)) {
        		throw new IllegalStateException("L'ajout n'est pas possible");
        	}
		
		if (getNbObjets() == tabObjets.length)  {
            		ObjetZork[] temp = new ObjetZork[getNbObjets() + 5];
            		for (int i = 0; i < getNbObjets(); i++) {
                		temp[i] = tabObjets[i];
            		}
            		tabObjets = temp;
        	}
        	
        	tabObjets[getNbObjets()] = oz;
        	
        	return true;
		
	}
	
	public boolean retirer(Object o) {
		
		 if (!(o instanceof ObjetZork)) {
            		return false;
        	}
        	
        	ObjetZork oz = (ObjetZork) o;
        	
        	for(int i = 0; i<getNbObjets(); i++) {
            		if(tabObjets[i].equals(oz)) {
                		tabObjets[i] = tabObjets[getNbObjets() - 1];
            		}
			return true;
        	}
        
        	return false;		
	}
	
	
	public int getNbObjets() {
		
		return tabObjets.length;
	}
	
	public ObjetZork[] getTabObjets() {
		return tabObjets;
	}
	
}
