let rec inserer a l = match l with
  | [] -> [a]
  | x::ll -> 
      if x > a then a::ll
      else x::(inserer a ll) ;;


let rec tri_insertion_acc l1 l2 = match l1 with
  | [] -> l2
  | x1::ll1 -> tri_insertion_acc ll1 (inserer x1 l2) ;;


let rec tri_insertion l1 = match l1 with
  | [] -> []
  | x1::ll1 -> inserer x1 (tri_insertion ll1) ;;


let rec decouper e l = match l with
  | [] -> [], []
  | x::ll -> 
      let (a, b) = (decouper e ll) in
      if (x < e) then (x::a, b)
      else (a, x::b) ;; 


let rec concatenation l1 l2 = match l1 with 
  | [] -> l2
  | x1::ll1 -> x1::(concatenation ll1 l2) ;;


let rec tri_rapide l = match l with
  | [] -> []
  | x::ll -> 
      let (a, b) = (decouper x ll) in
      concatenation (tri_rapide a) (x::tri_rapide b) ;;


let rec decouper_bis l = match l with
  | [] -> [], []
  | [x] -> [x], []
  | x1::x2::ll -> 
      let (a, b) = decouper_bis ll in
      (x1::a, x2::b) ;;
  

let rec fusion l1 l2 = match l1, l2 with
  | [], l2 -> l2
  | l1, [] -> l1
  | x1::ll1, x2::ll2 -> 
      if (x1 < x2) then x1::(fusion ll1 l2) 
      else if (x1 > x2) then x2::(fusion l1 ll2)
      else x1::x2::(fusion ll1 ll2) ;;


let rec tri_fusion l = match l with
  | [] -> []
  | x::[] -> [x]
  | x::ll -> 
      let (a, b) = decouper_bis ll in
      fusion (tri_fusion a) (tri_fusion b) ;;


let rec append l1 l2 = match l1 with
  | [] -> l2
  | x1::ll1 -> x1::(append ll1 l2) ;;


let rec prefixe u a = match u, a with
  | [], _ -> true
  | x1::uu, [] -> false
  | x1::uu, x2::aa -> 
      if x1=x2 then prefixe uu aa
      else false ;;

let rec rev l = match l with
  | [] -> []
  | x::ll -> append (rev ll) [x] ;;

let suffixe u a = prefixe (rev u) (rev a) ;;

let rec facteur u a = match u, a with
  | [], _ -> true
  | x1::uu, [] -> false
  | x1::uu, x2::aa -> 
      if (x1 != x2) then facteur u aa
      else if (prefixe uu aa) then true
      else facteur u aa ;;


let rec aux prefix suffix = match suffix with
  | [] -> [[prefix; []]]
  | x::xs ->
        (* on construit d’abord le nouveau préfixe *)
      let nouveau_prefix = concatenation prefix [x] in
        (* puis on appelle récursivement aux bonnes arguments *)
      let reste = aux nouveau_prefix xs in
        (* et enfin on concatène la décomposition courante avec le reste *)
      concatenation [[prefix; suffix]] reste ;;


let liste_des_decompositions l = aux [] l ;;










