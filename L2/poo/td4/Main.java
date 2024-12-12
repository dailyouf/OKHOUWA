import java.util.ArrayList;

class Main {
      
	public static void main(String[] args) {
	
		ArrayList <String> l = new ArrayList<String>();
		
		l.add("ad");
		
		l.add("ab");
		
		l.add(0, "ado");
		
		
		String s1;
        	int i;
		
		for (i=0; i<l.size(); i++) {
			
			s1 = l.get(i);
			
			if ((s1.length() % 2) == 0)
				l.set(i, "b");
			
		}


		ArrayList <String> s = new ArrayList<String>();
		
		s.add("a");
		s.add("aa");
		s.add("aaa");
			
		boolean trouve = s.contains("aa");
		int index = s.indexOf("aa");
		
		if (trouve) {
			System.out.println("Chaine aa présente à l'index: " + index);
		}
		
	}
		
        
}
