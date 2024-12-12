public abstract class AbstractConteneur implements Conteneur {
	
	
	public int getNbObjets() {
		return getTabObjets().length;
	}
	
	
	public boolean contient(ObjetZork oz) {
		
		ObjetZork[] tab = getTabObjets();
		
		for (int i=0; i<tab.length; i++) {
			if (tab[i].equals(oz))
				return true;
		}
	
		return false;
	
	}
	
	
	public int contientCombientde(ObjetZork oz) {
		
		ObjetZork[] tab = getTabObjets();
		
		int res=0;
		
		for (int i=0; i<tab.length; i++) {
			if (tab[i].equals(oz))
				res++;
		}	
			
		return res;
		
	}
	
	
	public boolean ajoutEstPossible(ObjetZork oz) {
	
		return (oz != null);
	}

}
