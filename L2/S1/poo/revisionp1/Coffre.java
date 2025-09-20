
import java.util.ArrayList;

class Coffre {
	
	private String desc;
	private int poids;
	private boolean ouvert;
	
	private ArrayList<ObjetZork> objets;
	
	private Cle c;
	
	public Coffre((String desc, int poids) {
			
		this.desc = desc;
		this.poids = poids;
		
		c = new Cle(desc, poids, this);
		
		objets = new ArrayList<ObjetZork>();
		
		ouvert = false;
	
	}
	
	
	public Coffre((String desc, int poids, ObjetZork[] desObjets, int nbObjets) {
			
		this.desc = desc;
		this.poids = poids;
		
		c = new Cle(desc, poids, this);
		
		objets = new ArrayList<ObjetZork>(nbObjets);
		
		for (int i=0; i<nbObjet) {
			objets.add(desObjets[i]);
		}
		
		ouvert = false;
	 
	}
	
	public boolean ajouter(ObjetZork oz) {
	
		if (ouvert) return objets.add(oz);
		
		return false;
	}
	
	public boolean contient(ObjetZork oz) {
		
		if (ouvert) return objets.contains(oz);
		
		return false;
	}
	
	public boolean equals(Object o) {
		
		if (! (o instanceof Coffre)) {
			return false;
		}
		
		Coffre test = (Coffre) o;
		
		return (desc==test.desc && poids==test.poids && c.equals(test.c) && objets.equals(objets) && ouvert==test.ouvert); 
	}
	
	public boolean estOuvert() {
		return ouvert;
	}

	public boolean fermerAvec(Cle uneCle) {
		if (c.equals(uneCle)) {
			ouvert=false;
		}
	}


	public String getDescription() {
		return desc;
	}
	
	public int getNbObjets() {
		return objets.size();
	}
	
	public int getPoids() {
		
		int res = poids;
	
		for (int i=0; i<objets.size(); i++) {
			res += objets.get(i).getPoids();
		}
		
		return res;
	}


	public int getPoidsAVide() {
		return poids;
	}
	
	public ObjetZork[] getTabObjets() {
		return objets.toArray();
	}
	
	public int hashCode() {
		
		int i=0;
		
		if (ouvert) i++;
	
		return getPoids() + desc.hashCode() + c.hashCode() + i;
	}

	public boolean ouvrirAvec(Cle uneCle) {
		if (c.equals(uneCle)) {
			ouvert=true;
		}
	}
	
	public boolean retirer(ObjetZork oz) {
		if (ouvert) {
			return objets.retirer(oz);
		}
		
		return false;
	}
	
	public String toString() {
		
		String s = "Coffre: " + desc + " \n";
		
		s +=  " il pèse " + Integer.toString(poids) + "kg. \n"
		
		s += "il contient les elements suivants: "
		for (int i=0; i<objets.size(); i++) {
			s += objets.get(i) + "  ";
		}
		
		s += "il doit être ouvert avec " + c.toString();
		
		return s;
		
	}
	
}
