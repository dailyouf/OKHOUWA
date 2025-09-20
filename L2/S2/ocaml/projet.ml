(* type représentant une formule booléenne *) 
type eb = X of int | Vrai | Faux | Et of eb * eb | Ou of eb * eb | Not of eb ;;
  

(* concatène deux listes [l1] et [l2] *)
let rec concat l1 l2 = match l1 with
  | [] ->  l2
  | x::ll1 -> x::concat ll1 l2 ;;



(* On teste si la variable X(i) apparaît déja dans la liste [l_var] *) 
let rec si_var_exist i l_var = match l_var with
  
  | [] -> false (* la variable n'existe pas encore dans notre liste *) 
  
  | X(e)::ll_var -> 

      if e = i then true (* la variable a été trouvée ! *) 

      else si_var_exist i ll_var
          
  | _ :: rest -> si_var_exist i rest (* ce cas ne se produit jamais car la list l_var ne contient que des X(i) mais il a été ajouté pour éviter les warnings à la compilation *) ;;   


(* ajout de X(i) à la liste [l_var] seulement si elle n’y est pas déjà *)  
let ajout i l_var = 
  
  if si_var_exist i l_var then l_var (* la variable est déjà présente, on renvoie la liste inchangée *)
                                     
  else X(i)::l_var (* la variable n'est pas encore présente, on doit l'ajouter *) ;;


(* On parcourt une expression booléenne [eq] et on accumule toutes les variables dans la liste [l_var] *) 
let rec rech_var eq l_var = match eq with
  | Vrai | Faux -> l_var (* pas de variable à extraire *)
  | X(i) -> ajout i l_var (* on ajoute X(i) dans la liste l_var *)
  | Not(e) -> rech_var e l_var (* On rappel la fonction sur le sous-expression *)
  | Et(e1, e2) | Ou(e1, e2) -> rech_var e2 (rech_var e1 l_var) (* On rappel la fonction sur les deux sous-expressions (gauche puis droite) *) ;;


(* On parcourt une liste d’expressions booléennes [l_eqs] et on collecte toutes les variables dans la liste [l_var] *) 
let rec parcours_eqs l_eqs l_var = match l_eqs with
  | [] -> l_var 
  | eq::ll_eqs -> parcours_eqs ll_eqs (rech_var eq l_var) (* on collecte les variables présentes dans eq, puis continue sur la liste d’expressions booléennes restante *) ;; 


(*  On produit pour chaque environnement env de l_env deux nouveaux environnements dans lesquels la variable X(e) vaut d'abord Vrai, puis Faux.    *)
let rec ajout_var_env e l_env = match l_env with
  | [] -> []
  | env::ll_env -> 
      (* on construit deux versions de env, l’une avec X(e)=Vrai, l’autre X(e)=Faux *)
      let env_true  = (X(e), Vrai)::env in
      let env_false = (X(e), Faux)::env in
      (* on empile ces deux environnements puis on poursuit sur reste des environements *)
      concat [env_true; env_false] (ajout_var_env e ll_env) ;;



(*  On génère tous les environnements possibles à partir d’une liste de variables [l_var]  *)
let rec generate_env l_var l_env = match l_var with
  
  | [] ->
      if l_env = [] then [ [] ]
      else l_env (* plus de variables à traiter : on renvoie la liste accumulée *) 
  
  | X(e)::ll_var -> 
      
      if l_env = [] then generate_env ll_var [[(X(e), Vrai)]; [(X(e), Faux)]] (* première variable trouvée : on initialise notre variable d'environement *)
      
      else generate_env ll_var (ajout_var_env e l_env) (* on étend chaque env existant avec Vrai et Faux et on continue récursivement avec les variables restantes*) 
  
  | _ -> generate_env l_var l_env (* ce cas ne se produit jamais car la list l_var ne contient que des X(i) mais il a été ajouté pour éviter les warnings à la compilation *) ;;



(* On Cherche la valeur associée à X(i) dans l’environnement. *)
let rec find_value i env = match env with 

  | (X(e), value)::reste -> 
      
      if e = i then 
        
        if value = Vrai then true
        else false
  
      else find_value i reste 

  | _ -> true ;;


(* On évalue récursivement l’expression sous l’environnement donné. *) 
let rec evaluer env eq = match eq with 
  
  | Vrai -> true
  | Faux -> false
  | Not(e) -> not (evaluer env e)
  | Et(e1, e2) -> (evaluer env e1) && (evaluer env e2)
  | Ou(e1, e2) -> (evaluer env e1) || (evaluer env e2)
  | X(i) -> find_value i env ;;


(* On teste si un environnement satisfait toutes les équations données *) 
let rec est_solution env l_eqs = match l_eqs with
  | [] -> true
  | eq::ll_eqs -> 
      if (evaluer env eq) then est_solution env ll_eqs
      else false ;;


(* On affiche à l’écran un environnement solution de l'equation avec le format : “X1=Vrai X2=Faux …”.*)
let rec afficher env = match env with
  
  | (X(e), value)::env_restant -> 
      if (value = Vrai) then Printf.printf "x%d=Vrai " e
      else Printf.printf "x%d=Faux " e ;
      afficher env_restant

  | _ -> print_newline () ;;


(*   On parcourt tous les environnements et affiche ceux qui sont solutions.     *)
let rec solveur_aux l_env l_eqs = match l_env with 
  
  | []  -> print_newline () (* plus rien à tester *)
  
  | env::ll_env -> 
      if (est_solution env l_eqs) then afficher env ;
      solveur_aux ll_env l_eqs ;; 


(*   Fonction Main du programme : elle commence d'abord par extraire les variables, puis elle génère tous les environnements,  *)
(*   et enfin elle affiche toutes les solutions. *)
let solveur l_eqs = 
  let l_var = parcours_eqs l_eqs [] in
  let l_env = generate_env l_var [] in 
  solveur_aux l_env l_eqs ;;


