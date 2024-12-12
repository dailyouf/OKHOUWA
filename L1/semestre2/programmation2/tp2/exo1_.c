#include<stdlib.h>
#include<stdio.h>

struct date{

	int a;
	int m;
	int j;

};

int camparer_date(struct date date1, struct date date2);

int nbre_jours_mois(int a, int m);

struct date lendemain(struct date my_date);

int ecart_dates(struct date date1, struct date date2);

int ecart_dates_rec(struct date date1, struct date date2);

int main(){
	
	struct date date1, date2;
	
	printf("Entrez d'abord la premiere date : \n");
	printf("le jours : ");
	scanf("%d", &date1.j);
	printf("le mois : ");
	scanf("%d", &date1.m);
	printf("l'année : ");
	scanf("%d", &date1.a);
	
	printf("Entrez maintenant la deuxième date : \n");
	printf("le jour : ");
	scanf("%d", &date2.j);
	printf("le mois : ");
	scanf("%d", &date2.m);
	printf("l'année : ");
	scanf("%d", &date2.a);
	
	printf("Le nombre de jours entre ces deux dates avec recusivité est de : %d jours \n", ecart_dates_rec(date1, date2));
	printf("Le nombre de jours entre ces deux dates sans recusivité est de : %d jours \n", ecart_dates_rec(date1, date2));

	return EXIT_SUCCESS;

}

int camparer_date(struct date date1, struct date date2){

	if (date1.a > date2.a) return 1;
	if (date1.a < date2.a) return -1;
	if (date1.m > date2.m) return 1;
	if (date1.m < date2.m) return -1;
	if (date1.j > date2.j) return 1;
	if (date1.j < date2.j) return -1;
	
	return 0;

}


int nbre_jours_mois(int a, int m){
	
	if ((m == 4) | (m == 6) | (m == 9) | (m == 11)) return 30;
	
	if (m == 2){
		if (a % 400 == 0 || (a % 4 == 0 && a % 100 != 0)) return 29;
		return 28;
	}
	
	return 31;
	
}


struct date lendemain(struct date my_date){
	
	my_date.j++;
	
	if (my_date.j > nbre_jours_mois(my_date.a, my_date.m)){
		my_date.j = 1;
		my_date.m++;	
		
		if (my_date.m > 12){
			my_date.m = 1;
			my_date.a++;
		}	
	}	
	
	return my_date;	
}

int ecart_dates(struct date date1, struct date date2){

	int i = 0, signe = 1;

	if (camparer_date(date1, date2) > 0){
		struct date tmp;
		tmp = date1;
		date1 = date2;
		date2 = tmp;
		signe = -1;
	}

	
	while (camparer_date(date1, date2) < 0){
		
		date1 = lendemain(date1);
		i++;
		
	}

	return i * signe;
}


int ecart_dates_rec(struct date date1, struct date date2){
	
	if (camparer_date(date1, date2) > 0){
		return -1 * ecart_dates_rec(date2, date1);
	}
	
	if (camparer_date(date1, date2) == 0){
		return 0;
	}
	

	return ecart_dates_rec(lendemain(date1), date2) + 1;
	
}



