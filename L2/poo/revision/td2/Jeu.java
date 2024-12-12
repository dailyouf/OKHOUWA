public class Jeu {
	
	public static void main(String[] argv) {
		
		Famille f = Famille.TREFLE;
		Rang r = Rang.ROI;
		
		Carte my_card = new Carte(f, r);
		
		System.out.println(my_card);
		
	}

}
