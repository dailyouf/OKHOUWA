void tri_selection(int taille, float * tab) {
	
	int i, j, min, tmp;

	for (i=0; i<taille-1; i++) {

		min = i;

		for (j=i+1; j<taille; j++) {
			if (tab[j] < tab[min]) 
				min = j;
		}
		
		tmp = tab[min];
		tab[min] = tab[i];
		tab[i] = tmp; 
	
	}
	

}


void tri_insertion(int taille, float * tab) {
	
	int i, j, tmp, min=0;
	
	
	for (i=1; i<taille; i++) {
		
		if (tab[i] < tab[min]) {
			min = i;
		}
	} 
	
	tmp = tab[i];
	tab[i] = tab[min];
	tab[min] = tmp;	
	
	for (i=2; i<taille; i++) {
	
		j=i;
		tmp = tab[j];
		
		while (tab[j] < tab[j-1]) {			
			tab[j] = tab[j-1];
			j--;
		}
		
		tab[j] = tmp;
	
	}
	
}


void tri_bulles(int taille, float * tab) {
	
	int i, j, tmp;
	
	int stop=0;	
	
	for (i=0; i<taille-1; i++) {
		
		stop = 1;
		
		for (j=1; j<taille-i; j++) {
			
			if (tab[j] < tab[j-1]) {
				tmp = tab[j];
				tab[j] = tab[j-1];
				tab[j-1] = tmp;
				
				stop = 0;
			}	
			
		}
	
		if (stop == 1)
			break;
	
	
	}

}



void fusionner(int * tab, int g, int d, int m) {

	
	int i, j, k;
	
	int * aux = malloc(sizeof(int) * (d - g + 1));	
	
	
	for (i=0; i<=m-g; i++) {
		
		aux[i] = tab[g + i];
	
	}	
	
	for (j=m+1; j<=d; j++) {
		
		aux[d + m - j - g + 1] = tab[j];
	
	}
	
	i=0;
	j=d-g;
	
	
	for (k=g; k<=d; k++) {
	
		if (aux[i] < aux[j]) {
			
			tab[k] = aux[i];
			i++;	
		}
		
		else {
			tab[k] = aux[j];
			j--;
		}
	
	}

}


void tri_fusion(int * tab, int g, int d) {
	
	
	int m = g + ((d - g) / 2);
	
	if (d <= g) {
		return ;
	}	
	
	
	tri_fusion(tab, g, m);
	tri_fusion(tab, m+1, d);
	
	fusioner(tab, g, d, m);
	

}


int partitionner(int * tab, int g, int d) {
	

	int pivot = d;
	int i=g, j=d-1, tmp;
	
	
	
	while (1+1==2) {
	
		
		while (tab[i] < tab[pivot]) 
			i++;
			
		while (tab[j] > tab[pivot])
			j--;
			
		if (i>=j)
			break;
			
		
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	
	}
	
	tmp = tab[i];
	tab[i] = tab[pivot];
	tab[pivot] = tmp;
	
	return i; 

}




void tri_rapide(int * tab, int g, int d) {
	
	int i;
	
	if (d <= g) 
		return;
	
	i = partitionner(tab, g, d);
	
	
	tri_rapide(tab, g, i-1);
	tri_rapide(tab, i+1, d);
} 



void tri_shell(int * tab, int g, int d) {

		
	int h, tmp;
	
	for (h=g; (3*h+1) < d; h=3*h+1);
		

	for (;h>0;h/=3) {
	
		for (i=g+h; i<d-1; i++) {
			
			for (j=i; j>=(g+h) && tab[j]<tab[j-h]; j-=h) {
				
				tmp = tab[j];
				tab[j] = tab[j-h];
				tab[j-h] = tmp;
			
			}	
				
		}
		
	}

}


struct compteur * tri_selection(list * l) {

	node *f, *q, *min;
	
	int tmp;
	
	for (f=l->first; f->next!=NULL; f=f->next) {
		
		min = f;
		
		for (q=f->next; q!=NULL; q->next) {
			
			if (q->value < min->value) 
				min = q;
		
		}
		
		
		tmp = f->value;
		f->value = min->value;
		min->value = tmp; 
	
	}
	
}


struct compteur * tri_bulles(list * l) {
	
	int stop=0, i, tmp;
	
	node * f;
	
	for (i=0; i<l->length; i++) {
	
		stop = 1;
		
		for (f=l->next; f->next!=NULL; f->next) {
			
			if (f->next->value < f->value) {
				
				tmp = f->next->value;
				f->next->value = f->value;
				f->value = tmp;
				
				stop=0;
			}			
		}	
			
			
		if (stop == 1) 
			break;
	
	}


}
