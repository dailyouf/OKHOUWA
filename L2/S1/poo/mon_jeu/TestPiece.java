/**
* ...
* @invariant descriptionCourte() != null;
* @invariant getNbObjets() >= 0;
*/


public class TestPiece {
	
	public static void main(String[] argv) {
		
		
		
	}
	
	/**
	* Retire un exemplaire de l’objet sp´ecifi´e de cette piece si cet objet y est
	* présent. Renvoie true si cet objet ´etait effectivement pr´esent dans la
	* pièce et que l’objet a pu etre effectivement retir´e ; renvoie false sinon.
	* La préesence d’un objet est test´e en utilisant la m´ethode equals de la
	* classe ObjetZork. L’argument doit etre non <code>null</code>.
	*
	* @param	oz	Objet dont un exemplaire doit etre retirer de cette piece
	* @return	<code>true<\code>si cet objet ´etait effectivement préesent ; 
			<code>false<\code> sinon.
	*
	* @requires oz != null;
	* @ensures \result <==> (getNbObjets() == \old(getNbObjets()) - 1);
	* @ensures !\result <==> (getNbObjets() == \old(getNbObjets()));
	* @ensures \old(contient(oz)) <==> \result;
	* @ensures \old(contient(oz)) <==> (contientCombienDe(oz)
	* == \old(contientCombienDe(oz)) - 1);
	* @ensures !\old(contient(oz)) <==> (contientCombienDe(oz)
	* == \old(contientCombienDe(oz)));
	* @ensures \old(contientCombienDe(oz) == 1) ==> !contient(oz);
	* @ensures \old(contientCombienDe(oz) > 1) <==> contient(oz);
	*/
	
	public boolean retirer(ObjetZork oz) {
		
		
	
	}

}	
