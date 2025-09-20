import java.util.ArrayList;


public class ArrayListConteneur extends AbstractConteneur {
	
	private ArrayList<ObjetZork> listObjets;
	
	public ArrayListConteneur(){
		listObjets = new ArrayList<ObjetZork>();
	}
	
	/**
	 * @throws NullPointerException si tab est null ou contient null
	 * @throws IllegalArgumentsException si nb<0 ou nb>tab.length
	 */
	public ArrayListConteneur(ObjetZork[] objs, int nb){
		
		this();
		
		// On peut s'en passer car dans objs.length il throw NullPoiterException si objs est null
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
			listObjets.add(objs[i]);
		}  
		
	}
	
	
	/**
	 * @trows NullPointerException si l'arguement objet est null
	 * @trows IllegalArgumentException si !ajoutEstPossible(oz)
	 */
	public boolean ajouter(ObjetZork oz) {
		
		if (oz == null) {
			throw new NullPointerException("l'objet fourni en arguemnt est null");
		}
		
		if (! ajoutEstPossible(oz)) {
        		throw new IllegalArgumentException("L'ajout n'est pas possible");
        	}
		
		if (listObjets.add(oz)) {
			return true;
		}
		
		return false;
	}
	
	public boolean retirer(Object oz) {
		
		 if (!(oz instanceof ObjetZork)) {
            		return false;
        	}
        	
        	return listObjets.remove(oz);
	}
	
	
	public int getNbObjets() {
		
		return listObjets.size();
	}
	
	public ObjetZork[] getTabObjets() {
		return (ObjetZork[]) listObjets.toArray();
	}
	
	/**
	 *  Renvoie le nombre d'exemplaires de l'objet spécifié en possession
	 *  de cette personne. La présence d'un objet est testé en utilisant la méthode equals de
	 *  la classe ObjetZork. Renvoie zéro si l'argument est <code>null</code>.
	 *
	 * @ensures \result >= 0;	
	 * @ensures contient(oz) <==> \result > 0;
	 * @ensures !contient(oz) <==> \result == 0;
	 *
	 * @param  oz  Objet dont on cherche a savoir en combien d'exemplaires le joeur possede l'objet.
	 * @return     le nombre d'exemplaires de l'objet spécifié en possession de ce joueur.
	 *
	 * @pure
	 */
	 public int contientCombienDe(Object oz) {
     		int res=0;
     		for (int i=0; i<listObjets.size(); i++) {
           		if (listObjets.get(i).equals(oz)) res++;
      		}
		return res;
	}
	
	/**
	 *  Renvoie true si la personne possede au moins un exemplaire de l'objet
	 *  spécifié. La présence d'un objet est testé en utilisant la méthode equals
	 *  de la classe ObjetZork. L'argument doit etre non <code>null</code>.
	 *
	 * @ensures \result <==> (contientCombienDe(oz) > 0);
	 *
	 * @param  oz  Objet dont on cherche a savoir s'il est présent dans cette piece
	 * @return     true si ce joueur possede au moins un exemplaire de l'objet
	 *      spécifié ; false sinon.
	 * @pure
	 */     
	public boolean contient(Object oz) {
		return listObjets.contains(oz);
	}


}
