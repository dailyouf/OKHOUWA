import java.util.ArrayList;
import java.util.AbstractCollection;
import java.util.Collection;
import java.util.Iterator;



public class ArrayListConteneur extends AbstractCollection<ObjetZork> {
	
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
		
		// On peut s'en passer car dans objs.length il throw NullPointerException si objs est null
		if (objs == null) {
			throw new NullPointerException("l'objet fourni en arguemnt est null");
		}
		
		if (nb<0 || nb>objs.length) {
			throw new IllegalArgumentException("arugments non valides");
		}
		
		for (int i=0; i<nb; i++) {
			if (objs[i] == null) {
				throw new NullPointerException("l'objet fourni en arguemnt est null");
			}
			listObjets.add(objs[i]);
		}  
		
	}
	
	public ArrayListConteneur(Collection<ObjetZork> c) {
		this();
		listObjets.addAll(c);
	}
	
	public int size() {
		return listObjets.size();
	}
	
	public Iterator<ObjetZork> iterator() {
		return listObjets.iterator();
	}
	
	/**
	 * @trows NullPointerException si l'arguement objet est null
	 * @trows IllegalArgumentException si !ajoutEstPossible(oz)
	 */
	public boolean add(ObjetZork oz) {
		
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
	
	
	public boolean ajoutEstPossible(ObjetZork oz) {
	
		return (oz != null);
	}

}
