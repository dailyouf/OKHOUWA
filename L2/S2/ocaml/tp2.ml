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
