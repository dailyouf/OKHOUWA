import java.util.ArrayList;
import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Iterator;


public class ArrayConteneur extends AbstractCollection<ObjetZork> {

	private ObjetZork[] tabObjets;
	int nb;

	public ArrayConteneur(){
		tabObjets = new ObjetZork[10];
	}
	
	/**
	 * @throws NullPointerException si tab est null ou contient null
	 * @throws IllegalArgumentsException si nb<0 ou nb>tab.length
	 */
	public ArrayConteneur(ObjetZork[] objs, int nb){
		
		tabObjets = new ObjetZork[nb];
		
		if (objs == null) {
			throw new NullPointerException("l'objet fourni en arguemnt est null");
		}
		
		if (nb<0 || nb>objs.length) {
			throw new IllegalArgumentException("arugments non valides");
		}
		
		this.nb = nb;
		
		for (int i=0; i<nb; i++) {
			if (objs[i] == null) {
				throw new NullPointerException("l'objet fourni en arguemnt est null");
			}
			
			tabObjets[i] = objs[i];
		}  
		
		
	}
	
	public ArrayConteneur(Collection<ObjetZork> c) {
		this((ObjetZork[]) c.toArray(), c.size());
	}
	
	public int size() {
		return nb;
	}
	
	public Iterator<ObjetZork> iterator() {
		return new TabIterator<ObjetZork>(tabObjets, nb);
	}
	
	/**
	 * @trows NullPointerException si l'arguement objet est null
	 * @trows IllegalStateException si !ajoutEstPossible(oz)
	 */
	public boolean add(ObjetZork oz) {
		
		if (oz == null) {
			throw new NullPointerException("l'objet fourni en arguemnt est null");
		}
		
		if (! ajoutEstPossible(oz)) {
        		throw new IllegalStateException("L'ajout n'est pas possible");
        	}
		
		if (size() == tabObjets.length)  {
            		ObjetZork[] temp = new ObjetZork[size() + 5];
            		for (int i = 0; i < size(); i++) {
                		temp[i] = tabObjets[i];
            		}
            		tabObjets = temp;
        	}
        	
        	tabObjets[size()] = oz;
        	
        	nb++;
        	
        	return true;
		
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
	public int contientCombientde(ObjetZork oz) {
		
		ObjetZork[] tab = tabObjets;
		
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
