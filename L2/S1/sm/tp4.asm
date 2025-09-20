.ORIG x3000
	

main 

; Remplir le tableau

   	LEA R1 tab
    	LD R3 taille

	LD R4 Val_0

	NOT R4 R4
	ADD R4 R4 #1


b_i
	ADD R3 R3 #0

	BRZ n_i

	GETC 
	OUT 

	ADD R0 R0 R4

	STR R0 R1 #0

	ADD R1 R1 #1
	ADD R3 R3 #-1

	BR b_i

n_i

	AND R0 R0 #0
	
	LEA R1 tab	
	LD R2 taille

	JSR somme
	
	LD R4 Val_0
	
	ADD R1 R0 #0
	
	ADD R0 R0 R4
	
	OUT
	
	HALT
	
	
	
tab	.BLKW #3	

taille	.FILL #3

Val_3	.FILL #3

Val_0	.FILL #48



; Routine qui fait la somme d'elemnts d'un tableau
; @param R1 l'adresse du tableau
; @param R2 la taille du tableau
; @return R0 le resultat de la somme
somme 
	AND R0, R0, #0
	ADD R2 R2 #0	
boucle	
	BRZ next
	
	LDR R3 R1 #0  	
	ADD R0 R0 R3
	
	ADD R1 R1 #1
	ADD R2 R2 #-1
	 
	BR boucle	
	
next	
	RET	
	
	.END
