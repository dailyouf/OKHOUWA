package minebayd1;

import java.time.Instant;

public class ClassifiedAdTest {
    public static void main(String[] args) {
        // Création de deux annonces dans différentes catégories
        ClassifiedAd ad1 = new ClassifiedAd(Category.GAMES, "Smartphone", 250);
        ClassifiedAd ad2 = new ClassifiedAd(Category.BOOKS, "Roman", 15);

        // Affichage des annonces
        System.out.println(ad1);
        System.out.println(ad2);

        // Comparaison des dates
        System.out.println("L'annonce ad1 a été publiée avant ad2 : " + ad1.isBefore(ad2));
        System.out.println("L'annonce ad1 a été publiée après ad2 : " + ad1.isAfter(ad2));

        // Comparaison d'égalité
        ClassifiedAd ad3 = new ClassifiedAd(Category.GAMES, "Smartphone", 250);
        System.out.println("L'annonce ad1 est-elle égale à ad3 ? " + ad1.equals(ad3));

        // Vérification de hashCode
        System.out.println("HashCode ad1 : " + ad1.hashCode());
        System.out.println("HashCode ad3 : " + ad3.hashCode());
    }
}

