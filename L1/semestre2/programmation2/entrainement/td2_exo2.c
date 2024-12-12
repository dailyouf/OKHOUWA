#include <stdlib.h>
#include <stdio.h>

#define N 31

struct date {
	int a, m, j;
};

struct individu {
	char nom[N];
	struct date naissance;	
};

int comparer_date(struct date date1, struct date date2);

int nbre_jours_mois(int a, int m);

struct date lendemain(struct date date);

int ecart_dates(struct date date1, struct date date2);

int ecart_dates_rec(struct date date1, struct date date2);

int ecart_dates_rec_ter(struct date date1, struct date date2);
int ecart_dates_rec_ter_aux(struct date date1, struct date date2, int res, int signe);


int diff_age_max(struct individu tab[N], int n);

int diff_age_max_bis(struct individu tab[N], int n);

int diff_age_max_bis_rec(struct individu tab[N], int n)

int main(){
	
	return EXIT_SUCCESS;	
	
}

int comparer_date(struct date date1, struct date date2){
	
	if (date1.a > date2.a) return 1;
	if (date1.a < date2.a) return -1;
	if (date1.m > date2.m) return 1;
	if (date1.m < date2.m) return -1;
	if (date1.j > date2.j) return 1;
	if (date1.j < date2.j) return -1;
	
	return 0;
	
}

int nbre_jours_mois(int a, int m){
	
	if (2 == m){
		if ((a % 400 == 0) || ((a % 4 == 0) && (a % 100 != 0))) return 29;
		
		return 28;
	}	
	
	if (m==4 || m==6 || m==9 || m==11) return 30;	

	return 31;
}

struct date lendemain(struct date date){

	date.j++;

	if (date.j > nbre_jours_mois(date.a, date.m)){
		date.j = 1;
		date.m++;
		
		if (date.m > 12){
			date.m = 1;
			date.a ++;
		}
	}
	
	return date;
}

int ecart_dates(struct date date1, struct date date2){

	int res=0, signe=1;
	
	struct date tmp;
	
	if (comparer_date(date1, date2) == 1) {
		tmp = date1;
		date1 = date2;
		date2 = tmp;
		signe=-1;
	}
	
	while (comparer_date(date1, date2) != 0) {
		date1 = lendemain(date1);
		res ++;
	}
	
	return res * signe;

}

int ecart_dates_rec(struct date date1, struct date date2){

	if (comparer_date(date1, date2) == 1) {
		return -1 * ecart_dates_rec(date2, date1);
	}
	
	if (comparer_date(date1, date2) == 0) {
		return 0;
	}
	
	return ecart_dates_rec(lendemain(date1), date2) + 1;

}

int ecart_dates_rec_ter_aux(struct date date1, struct date date2, int res, int signe){

	if (comparer_date(date1, date2) == 1) {
		return ecart_dates_rec_ter_aux(date2, date1, res, -1);
	}
	
	if (comparer_date(date1, date2) == 0) {
		return res * signe;
	}
	
	
	return ecart_dates_rec_ter_aux(lendemain(date1), date2, ++res, signe);
	
}


int ecart_dates_rec_ter(struct date date1, struct date date2){

	return ecart_dates_rec_ter_aux(date1, date2, 0, 1);

}

int diff_age_max(struct individu tab[N], int n){
	
	int i, min=0, max=0;
	
	
	
	for(i=1; i < n; i++){
		if (comparer_date(tab[i].naissance, tab[min].naissance) < 0) min = i;
		if (comparer_date(tab[i].naissance, tab[max].naissance) > 0) max = i;
	}
	
	return ecart_dates_rec_ter(tab[max].naissance, tab[min].naissance);
}


int diff_age_max_bis(struct individu tab[N], int n){
	
	int i, j, dif=0;
	
	for (i=0; i < n - 1; i++){
	
		for (j=i+1; j<n; j++){
			if (ecart_dates_rec_ter(tab[j].naissance, tab[i].naissance) > dif) dif = ecart_dates_rec_ter(tab[j].naissance, tab[i].naissance; 
		}
	}
	
	return dif;

}

int diff_age_max_bis_rec(struct individu tab[N], ){
	
	int i, j, dif=0;
	
	for (i=0; i < n - 1; i++){
	
		for (j=i+1; j<n; j++){
			if (ecart_dates_rec_ter(tab[j].naissance, tab[i].naissance) > dif) dif = ecart_dates_rec_ter(tab[j].naissance, tab[i].naissance; 
		}
	}
	
	return dif;

}
