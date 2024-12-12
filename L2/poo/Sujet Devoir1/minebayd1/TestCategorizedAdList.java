package minebayd1;

import java.util.ArrayList;
import java.util.Optional;
import static minebayd1.Category.*;

public class TestCategorizedAdList {
    public static void main(String[] args) {
        // Créer une nouvelle liste d'annonces catégorisées
        CategorizedAdList adList = new CategorizedAdList();
        
        		if (!(adList.lastIndex() == adList.nextIndex() || adList.lastIndex() == adList.previousIndex())) System.out.println("noooooooooo");

        // Ajouter des annonces pour chaque catégorie
        ClassifiedAd ad1 = new ClassifiedAd(CLOTHES, "Ad for clothes 1", 14);
        adList.add(ad1);
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 1", 23));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 1", 31));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 1", 10));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 1", 94));
        adList.add(new ClassifiedAd(CLOTHES, "Ad for clothes 2", 17));
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 2", 25));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 2", 36));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 2", 8));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 2", 100));
        adList.add(new ClassifiedAd(CLOTHES, "Ad for clothes 3", 12));
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 3", 29));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 3", 45));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 3", 9));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 3", 70));
        adList.add(new ClassifiedAd(CLOTHES, "Ad for clothes 4", 15));
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 4", 19));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 4", 33));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 4", 22));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 4", 85));
        adList.add(new ClassifiedAd(CLOTHES, "Ad for clothes 5", 11));
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 5", 28));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 5", 39));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 5", 14));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 5", 60));
        adList.add(new ClassifiedAd(CLOTHES, "Ad for clothes 6", 18));
        adList.add(new ClassifiedAd(SHOES, "Ad for shoes 6", 21));
        adList.add(new ClassifiedAd(BOOKS, "Ad for books 6", 44));
        adList.add(new ClassifiedAd(GAMES, "Ad for games 6", 13));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 6", 95));
        adList.add(new ClassifiedAd(COMPUTERS, "Ad for computers 7", 77));

        // Afficher la taille totale de la liste
        System.out.println("Nombre total d'annonces : " + adList.size());
        
	System.out.println("Affichage de la première annonce : " + adList.get(adList.size() - 1));
	
	
	while (adList.hasNext()) {
		System.out.println(adList.nextIndex());
		System.out.println(adList.next());
		
				
		if (!(adList.lastIndex() == adList.nextIndex() || adList.lastIndex() == adList.previousIndex())) System.out.println("noooooooooo");
	}

	while (adList.hasPrevious()) {
		System.out.println(adList.previousIndex());
		System.out.println(adList.previous());
	}
	
	System.out.println("Affichage de la dernière annonce : " + adList.index);
	
        // Tester la sélection de catégorie
        adList.selectCategory(CLOTHES);
        System.out.println("Catégorie sélectionnée : " + adList.getSelectedCategory());

        // Tester le parcours avec next() dans une catégorie spécifique
        adList.startIteration();
        System.out.println("\nParcours avec next() pour la catégorie " + CLOTHES + " :");
        while (adList.hasNext()) {
            System.out.println(adList.next());
        }
        

        // Tester le parcours avec previous()
        System.out.println("\nParcours avec previous() pour la catégorie " + CLOTHES + " :");
        while (adList.hasPrevious()) {
            System.out.println(adList.previous());
        }

        // Changer de catégorie et tester de nouveau le parcours
        adList.selectCategory(SHOES);
        System.out.println("\nCatégorie sélectionnée : " + adList.getSelectedCategory());
        adList.startIteration();
        System.out.println("Parcours avec next() pour la catégorie " + SHOES + " :");
        while (adList.hasNext()) {
            System.out.println(adList.next());
        }

        // Tester la suppression d'une annonce
        System.out.println("\nSuppression d'une annonce : " + ad1);
	System.out.println("Contient adToRemove avant suppression : " + adList.contains(ad1));
        boolean removed = adList.remove(ad1);
        System.out.println("Annonce supprimée : " + removed);

        // Vérifier si l'annonce supprimée est encore présente
        System.out.println("Contient adToRemove après suppression : " + adList.contains(ad1));

        // Imprimer la liste complète des annonces restantes
        adList.selectCategory(CLOTHES);
        adList.startIteration();
        System.out.println("\nParcours avec next() pour la catégorie " + CLOTHES + " :");
        while (adList.hasNext()) {
            System.out.println(adList.next());
        }

        // Vérifier la méthode equals en comparant deux listes identiques
        CategorizedAdList adListCopy = new CategorizedAdList();
        adListCopy.add(new ClassifiedAd(CLOTHES, "Ad for clothes 1", 14));
        adListCopy.add(new ClassifiedAd(SHOES, "Ad for shoes 1", 23));
        adListCopy.add(new ClassifiedAd(BOOKS, "Ad for books 2", 36));  // Différent pour tester equals

        System.out.println("\nLes deux listes sont-elles égales ? " + adList.equals(adListCopy));
        
        // Test de l'accès à la i eme positiond de la liste 
	System.out.println("\n"  + adList.get(20));
        
        
        System.out.println("\nLes deux listes égales sont-elles vraiment égales ? " + adList.equals(adList.clone()));
	
        // Test de réinitialisation de l’itération
        adList.selectCategory(COMPUTERS);
        adList.startIteration();
        System.out.println("\nParcours pour la catégorie " + COMPUTERS + " après réinitialisation de l’itération :");
        while (adList.hasNext()) {
            System.out.println(adList.next());
        }

        // Test du passage entre catégories et vérification des annonces par catégorie
        System.out.println("\nAnnonces par catégorie après itérations multiples :");
        for (Category category : Category.values()) {
            adList.selectCategory(category);
            adList.startIteration();
            System.out.println("Catégorie " + category + " : ");
            while (adList.hasNext()) {
                System.out.println("  - " + adList.next());
            }
        }
        
        
	System.out.println("\n\n\nAnnonces par catégorie avec toString :" + adList.toString());
	
	
	// Test de la methode clone
	System.out.println("\n\n\n Annonces par catégorie avec clone :" + adList.clone().toString());
	System.out.println("\n Test de la methode clone  :" + (adList == adList.clone()));
    	
    }
    
}




