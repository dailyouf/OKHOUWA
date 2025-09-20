type f =
  | X of int
  | Vrai
  | Faux
  | Et of f * f
  | Ou of f * f
  | Imp of f * f
  | Equiv of f * f
  | Not of f ;;

let rec elim_equiv f = 
  match f with
  | X _ -> f 
  | Vrai -> f
  | Faux -> f
  | Not a -> Not (elim_equiv a)
  | Et (a, b) -> Et (elim_equiv a, elim_equiv b)
  | Ou (a, b) -> Ou (elim_equiv a, elim_equiv b)
  | Imp (a, b) -> Imp (elim_equiv a, elim_equiv b)
  | Equiv (a, b) -> Ou ( Et (elim_equiv a, elim_equiv b), Et (Not (elim_equiv a), Not (elim_equiv b)) ) ;;

let rec elim_imp f = 
  match f with
  | X _ -> f 
  | Vrai -> f
  | Faux -> f
  | Not a -> Not (elim_imp a)
  | Et (a, b) -> Et (elim_imp a, elim_imp b)
  | Ou (a, b) -> Ou (elim_imp a, elim_imp b)
  | Imp (a, b) -> Ou (Not (elim_imp a), elim_imp b) ;;

let rec repousse_neg f = 
  match f with
  | X _ -> f 
  | Vrai -> f
  | Faux -> f
  | Et (a, b) -> f
  | Ou (a, b) -> f
  | Not (X _) -> f
  | Not Vrai -> f
  | Not Faux -> f
  | Not (Not a) -> a
  | Not (Et (a, b)) -> Ou (repousse_neg (Not a), repousse_neg (Not b))
  | Not (Ou (a, b)) -> Et (repousse_neg (Not a), repousse_neg (Not b)) ;;

let rec inverse_ou_et f = 
  match f with
  | X _ -> f 
  | Vrai -> f
  | Faux -> f
  | Not a -> f
  | Et (a, Ou (b, c)) -> Ou (Et (a, b), Et (a, c))
  | Et (Ou (b, c), a) -> Ou (Et (a, b), Et (a, c))
  | Ou (a, Et (b, c)) -> Et (Ou (a, b), Ou (a, c))
  | Ou (Et (b, c), a) -> Et (Ou (a, b), Ou (a, c)) ;;

