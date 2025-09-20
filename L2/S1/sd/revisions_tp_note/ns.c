**********************ARBRES ROUGES ET NOIRS******************************/
/* ICI la fonction verifie SI l arbre EST bien un ARBRE ROUGE NOIR*/
int LLRBT(struct binary_tree *l){
    if(l == NULL) return 1;
    /* verification de deux rouges consecutifs*/ 
    /* le 1 represente le rouge et le 0 represente le noir*/
    if(l->couleur == 1){
        if(l->droite && l->droite->couleur == 1) return 0;
        if(l->gauche && l->gauche->couleur == 1) return 0;
    }
    
    int left_black_height = hauteur_noirs(l->gauche);
    int right_black_height = hauteur_noirs(l->droite);
    if (left_black_height != right_black_height) return 0;


    return LLRBT(l->gauche ) && LLRBT(l->droite);


}

/* on compte le nombre de noeuds noirs dans l arbre */
int hauteur_noir(struct binary_tree *l){
    if(!l) return 0;
    int gauche = hauteur_noir(l->gauche);
    int droite = hauteur_noir(l->droite);
    if(gauche != droite) return 0;
    return gauche  + (l->couleur == 0? 1 : 0);
}

/** Insere iterativement un noeud avec une etiquette donnée a la racine sans pile(c est pas un arbre RB)*/
link insert_BST_root_it(link h, int v) {
  if(h==NULL) {
    return cons_binary_tree(v,NULL,NULL) ;
    }
    
    link parent ;
    link current=h ;
    
   while (current != NULL) { 
        parent = current; 
        current = less(v, get_binary_tree_root(current)) ? left(current) : right(current);
    }
    current = cons_binary_tree(v, NULL, NULL); 
    if (less(v, get_binary_tree_root(parent))) { 
        parent->left = current ;
        parent=rotate_right(parent) ; /* je fais une rotation pour que mon element ne soit plus une feuille et que je puisse faire apres des rotations simples et le faire ramener a la racine */ 
    } else { 
        parent->right = current ; 
        parent=rotate_left(parent) ;
    }
   
}
 while(h->label != v) {
   if(less(v, get_binary_tree_root(h))) {
     h=rotate_right(h) ;
     }
    else {
     h=rotate_left(h) ;
     }
   return h;
}
/* insertion a la racine iterativement en utilisant une pile C EST PAS UN ARBRE ROUGE NOIR */
link insert_root_BST_it(link h , int v) {
   struct stack *s=init_stack(height_binary_tree(h)+1) ;
   link k ;
   while (h!=NULL) {
    k= less(v, get_binary_tree_root(h))? h->left :h->right ;
    push_stack(s,h) ;
    h=k ;
    }
    
    h= cons_binary_tree(v,NULL,NULL) ;
    
    while(!is_empty_stack(s)) {
     k=pop_stack(s) ;
     if(v<k->value) {
       k->left =h ;
       k=rotate_right(k) ;
       }
       else{
         k->right=h ;
         k=rotate_left(h) ;
         }
         
       delete_stack(*s) ;
       return h ; 
       
 }
