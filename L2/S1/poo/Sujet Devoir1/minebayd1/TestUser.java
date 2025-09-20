package minebayd1;

import java.time.Instant;
import java.util.Optional;

import static minebayd1.AdState.*;
import static minebayd1.Category.*;

public class TestUser {

    public static void main(String[] args) {

        // Test du constructeur
        User user = new User("testUser", "password123");
        System.out.println("Nom de l'utilisateur : " + user.getName());
        System.out.println("Mot de passe de l'utilisateur : " + user.getPassword());
        System.out.println("Solde initial : " + user.getAvailableCash());
        System.out.println("Date d'enregistrement : " + user.getRegistrationDate());

        // Vérifier l'état d'annonce sélectionné par défaut
        System.out.println("État d'annonce par défaut : " + user.getSelectedAdState());

        // Ajouter et vérifier les annonces
	ClassifiedAd ad1 = user.add(CLOTHES, "Vends un T-shirt", 10);
	ClassifiedAd ad2 = user.add(BOOKS, "Vends un livre de programmation", 20);
	ClassifiedAd ad3 = user.add(GAMES, "Jeu vidéo d'occasion", 15);
	
	ClassifiedAd ad6 = user.add(CLOTHES, "Veste en cuir", 50);
	ClassifiedAd ad7 = user.add(BOOKS, "Roman de science-fiction", 12);
	ClassifiedAd ad8 = user.add(GAMES, "Console de jeu ancienne", 75);
	ClassifiedAd ad9 = user.add(COMPUTERS, "Clavier mécanique", 40);
	ClassifiedAd ad10 = user.add(SHOES, "Sandales d'été", 15);
	ClassifiedAd ad11 = user.add(CLOTHES, "Casquette de baseball", 8);
	ClassifiedAd ad12 = user.add(BOOKS, "Guide de voyage", 10);
	ClassifiedAd ad13 = user.add(GAMES, "Puzzle de 1000 pièces", 20);
	ClassifiedAd ad14 = user.add(COMPUTERS, "Écran 24 pouces", 100);
	ClassifiedAd ad15 = user.add(SHOES, "Bottes d'hiver", 45);
	ClassifiedAd ad16 = user.add(CLOTHES, "Pantalon en jean", 30);
	ClassifiedAd ad17 = user.add(BOOKS, "Dictionnaire", 18);
	ClassifiedAd ad18 = user.add(GAMES, "Cartes à collectionner", 5);
	ClassifiedAd ad19 = user.add(COMPUTERS, "Souris sans fil", 25);
	ClassifiedAd ad20 = user.add(SHOES, "Mocassins en cuir", 60);

	

        System.out.println("Nombre d'annonces ouvertes : " + user.size(OPEN, Optional.empty()));

        // Tester la sélection de catégorie et d'état
        user.selectCategory(CLOTHES);
        System.out.println("Catégorie sélectionnée : " + user.getSelectedCategory().get());
        user.selectAdState(CLOSED);
        System.out.println("État d'annonce sélectionné après modification : " + user.getSelectedAdState());

        // Ajouter une annonce fermée pour tester la transition d'état
        ClassifiedAd ad4 = new ClassifiedAd(CLOTHES, "Pull d'hiver", 25);
        // user.closedAds.add(ad4);
        System.out.println("Nombre d'annonces fermées : " + user.size(CLOSED, Optional.empty()));

        // Tester l'achat
        User vendor = new User("vendorUser", "vendorPass");
        ClassifiedAd ad5 = vendor.add(COMPUTERS, "Ordinateur d'occasion", 13);
        System.out.println("Solde du vendeur avant vente : " + vendor.getAvailableCash());
        System.out.println("Solde de l'utilisateur avant achat : " + user.getAvailableCash());
        user.buy(vendor, ad5);
        System.out.println("Solde du vendeur après vente : " + vendor.getAvailableCash());
        System.out.println("Solde de l'utilisateur après achat : " + user.getAvailableCash());

        // Vérifier les annonces après l'achat
        System.out.println("Nombre d'achats de l'utilisateur : " + user.size(PURCHASE, Optional.empty()));

        // Tester le parcours des annonces ouvertes avec next()
        user.selectAdState(OPEN);
        user.startIteration();
        System.out.println("Parcours des annonces ouvertes avec next() :");
        while (user.hasNext()) {
            System.out.println(user.next());
        }

        // Tester le parcours avec previous()
        System.out.println("Parcours avec previous() :");
        while (user.hasPrevious()) {
            System.out.println(user.previous());
        }

        // Test de la méthode get() avec l'index
        System.out.println("Obtention de la dernière annonce ouverte : " + user.get(0));

        // Vérifier containsInState
        System.out.println("L'utilisateur contient-il ad1 dans OPEN ? " + user.containsInState(OPEN, ad1));
        System.out.println("L'utilisateur contient-il ad5 dans CLOSED ? " + user.containsInState(CLOSED, ad5));
        System.out.println("L'utilisateur contient-il ad5 dans PURCHASE? " + user.containsInState(PURCHASE, ad5));

        // Vérifier la méthode toString
        System.out.println("Résumé des annonces de l'utilisateur :");
        System.out.println(user.toString());
        
        // user.purchases.remove(ad5);
        System.out.println(user.size(PURCHASE, Optional.empty()));
        
        AdState[] tabState = AdState.values();
	Category[] tabCat = Category.values();
        
        for (AdState state : tabState) {
			for (Category cat : tabCat) {
				for (int i = 1; i < vendor.size(state, Optional.of(cat)); i++) {
					System.out.println(vendor.get(state, Optional.of(cat), i - 1).isAfter(vendor.get(state, Optional.of(cat), i)));
				}
			}
		}
	
    }
}

