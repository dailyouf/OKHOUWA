type arbre = Vide | Noeud of int * arbre * arbre ;;

let rec appartient x h = match h with
        | Vide -> false
        | Noeud(e, h1, h2) ->
                if (x < e) then appartient x h1
                else if (x > e) then appartient x h2
                else true ;;

let rec concatenation l1 l2 = match l1 with
        | [] -> l2
        | x1::ll1 -> x1::(concatenation ll1 l2) ;;

let rec arbre_2_liste h = match h with
        | Vide -> []
        | Noeud(e, h1, h2) ->
                let l1 = (arbre_2_liste h1) in
                concatenation l1 (e::arbre_2_liste h2) ;;

let rec inserer_bas n h = match h with
        | Vide -> Noeud(n, Vide, Vide)
        | Noeud(e, h1, h2) ->
                if (n < e) then
                        Noeud(e, inserer_bas n h1, h2)
                else
                        Noeud(e, h1, inserer_bas n h2) ;;

let rec couper n h = match h with
        | Vide -> Vide, Vide
        | Noeud(e, h1, h2) ->
                if (n < e) then
                        let g, d = couper n h1 in
                        g, Noeud(e, d, h2)
                else
                        let g, d = couper n h2 in
                        Noeud(e, h1, g), d ;;

let inserer_haut n a =
        let g, d = couper n a in
        Noeud(n, g, d) ;;

let rec liste_2_arbre l = match l with
        | [] -> Vide
        | x::ll -> inserer_bas x (liste_2_arbre ll) ;;

let rec tri_liste l = match l with
        | [] -> []
        | x::ll ->
                arbre_2_liste (inserer_bas x (liste_2_arbre ll)) ;;

