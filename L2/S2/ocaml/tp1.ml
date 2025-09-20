let rec fact i = 
        if i = 0
        then 1
        else i * fact (i-1) ;;

let rec fact_acc i a = 
        if i = 0
        then a
        else fact_acc (i-1) (a*i) ;;


let rec append l1 l2 = match l1 with
        | [] -> l2
        | x1::ll1 -> x1::(append ll1 l2) ;;


let rec rev l = match l with
        | [] -> []
        | x::ll -> append (rev ll) [x] ;;

let rec rev l = match l with
        | [] -> []
        | x::ll -> append (rev ll) [x] ;;
                             

let rec rev_acc l a = match l with
        | [] -> a
        | x::ll -> rev_acc ll (append [x] a) ;;


let rec inter l1 l2 = match l1, l2 with
        | [], _ -> []
        | _, [] -> []
        | x1::ll1, x2::ll2 -> 
                if x1 < x2 then inter ll1 l2
                else if x1 > x2 then inter l1 ll2 
                else append [x1] (inter ll1 ll2) ;;

let rec union l1 l2 = match l1, l2 with
        | [], l2 -> l2
        | l1, [] -> l1
        | x1::ll1, x2::ll2 -> 
                if x1 < x2 then append [x1] (union ll1 l2)
                else if x1 > x2 then append [x2] (union l1 ll2)
                else append [x1] (union ll1 ll2) ;;


let rec appartient a l = match l with
        | [] -> false 
        | x::ll -> 
                if x = a then true
                else appartient a ll ;;

let rec inter_2 l1 l2 = match l1 with
        | [] -> []
        | x1::ll1 -> 
                if (appartient x1 l2) then append [x1] (inter_2 ll1 l2)
                else inter_2 ll1 l2 ;; 


let rec union_2 l1 l2 = match l1 with
        | [] -> l2
        | x1::ll1 -> 
                if (appartient x1 l2) then union_2 ll1 l2
                else append [x1] (union_2 ll1 l2) ;;
