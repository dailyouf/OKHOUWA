public interface Conteneur {
	
	public boolean ajouter(ObjetZork oz);
	
	public boolean retirer(Object oz);
	
	public int getNbObjets();
	
	public boolean contient(ObjetZork oz);
	
	public int contientCombientde(ObjetZork oz);	
	
	public ObjetZork[] getTabObjets();

	public boolean ajoutEstPossible(ObjetZork oz);
	
}
