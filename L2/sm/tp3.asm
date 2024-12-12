	.ORIG x3000
   
	IN 

        LD R4 Val_0
        NOT R4 R4
        ADD R4 R4 #1

        ADD R0 R0 R4
        ADD R5 R0 #0

        ADD R1 R1 R5
        ADD R2 R1 #0
          
        AND R3 R3 #0
        AND R4 R4 #0

	ADD R3 R3 #3
        ADD R4 R4 #1
        


BOUCLE_8
	ADD R3 R3 #0
	
	BRNZ FIN_b8
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_8
	
FIN_b8
        

BOUCLE_2
	ADD R4 R4 #0
	
	BRNZ FIN_b2
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_2
	
FIN_b2
        ADD R1 R1 R2
        
        
        ADD R2 R1 #0
        
        AND R3 R3 #0
        AND R4 R4 #0
	
        ADD R3 R3 #3
        ADD R4 R4 #1
        
BOUCLE_81
	ADD R3 R3 #0
	
	BRNZ FIN_b81
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_81
	
FIN_b81


BOUCLE_21
	ADD R4 R4 #0
	
	BRNZ FIN_b21
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_21
	
FIN_b21
        ADD R1 R1 R2   
      
      
        ADD R2 R1 #0
        
        AND R3 R3 #0
        AND R4 R4 #0
	
        ADD R3 R3 #3
        ADD R4 R4 #1
        
BOUCLE_82
	ADD R3 R3 #0
	
	BRNZ FIN_b82
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_82
	
FIN_b82


BOUCLE_22
	ADD R4 R4 #0
	
	BRNZ FIN_b22
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_22
	
FIN_b22
        ADD R6 R1 R2

        
        GETC
        OUT
        
        LD R4 Val_0
        NOT R4 R4
        ADD R4 R4 #1

        ADD R0 R0 R4
        ADD R5 R0 #0

        AND R1 R1 #0
	AND R2 R2 #0

	ADD R1 R1 R5
        ADD R2 R1 #0
        
        AND R3 R3 #0
        AND R4 R4 #0
	
        ADD R3 R3 #3
        ADD R4 R4 #1


BOUCLE_8_11
	ADD R3 R3 #0
	
	BRNZ FIN_b8_11
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_8_11
	
FIN_b8_11

BOUCLE_2_11
	ADD R4 R4 #0
	
	BRNZ FIN_b2_11
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_2_11
	
FIN_b2_11
        ADD R1 R1 R2
        
       
        ADD R2 R1 #0
        
        AND R3 R3 #0
        AND R4 R4 #0
	
        ADD R3 R3 #3
        ADD R4 R4 #1


BOUCLE_8_12
	ADD R3 R3 #0
	
	BRNZ FIN_b8_12
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_8_12
	
FIN_b8_12

BOUCLE_2_12
	ADD R4 R4 #0
	
	BRNZ FIN_b2_12
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_2_12
	
FIN_b2_12
        ADD R0 R1 R2
        ADD R6 R6 R0
        
	GETC
        OUT
        
        LD R4 Val_0
        NOT R4 R4
        ADD R4 R4 #1

        ADD R0 R0 R4
        ADD R5 R0 #0
        
	AND R1 R1 #0
	AND R2 R2 #0


	ADD R1 R1 R5
        ADD R2 R1 #0
        
        AND R3 R3 #0
        AND R4 R4 #0
	
        ADD R3 R3 #3
        ADD R4 R4 #1

BOUCLE_8_2
	ADD R3 R3 #0
	
	BRNZ FIN_b8_2
	
	ADD R1 R1 R1

	ADD R3 R3 #-1
	
	BR BOUCLE_8_2
	
FIN_b8_2

BOUCLE_2_2
	ADD R4 R4 #0
	
	BRNZ FIN_b2_2
	
	ADD R2 R2 R2

	ADD R4 R4 #-1	

	BR BOUCLE_2_2
	
FIN_b2_2
        ADD R0 R1 R2
	ADD R6 R6 R0
        
        GETC
        OUT
        
        LD R4 Val_0
        NOT R4 R4
        ADD R4 R4 #1

        ADD R0 R0 R4
        ADD R6 R6 R0

	HALT


Val_0   .FILL #48

	.END
