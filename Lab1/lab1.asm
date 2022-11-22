.ORIG x3000
; write your code here

AND R0, R0, #0; r0= digit counter
AND R1, R1, #0; r1 = digit(the hex value to print)
AND R2, R2, #0; r2 = bit counter
AND R3, R3, #0; r3 = given intital value that needs to be printed
AND R4, R4, #0; r4 = the equivalent ascii vlaue of r3


		
		LD R3, VALUE
		AND R4, R4, #0 ;digit counter
		ADD R4, R4, #4
FOUR_LOOP	BRnz DONE
		
		AND R1, R1, #0
		ADD R2, R2, #4 ; R2 is the bit counter

CHECK_BITS	BRnz NINE_LOOP
		ADD R1,R1, R1
		ADD R3, R3, #0 
		BRn TRUE_S
		BRzp FALSE_S

FALSE_S		ADD R1, R1, #0 
		ADD R3, R3, R3
		ADD R2, R2, #-1 
		BR CHECK_BITS 

TRUE_S		ADD R1, R1, #1 
		ADD R3, R3, R3
		ADD R2, R2, #-1
		BR CHECK_BITS

NINE_LOOP	AND R0, R0, #0
		ADD R0, R0, R1
		ADD R1, R1, #-9 
		BRp FALSE_N
		BRnz TRUE_N 

TRUE_N 		ADD R0, R0, #12	
		ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #12
		OUT 
		ADD R4, R4, #-1 
		BRp FOUR_LOOP
		BRnz DONE

FALSE_N 	ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #7
		OUT 
		ADD R4, R4, #-1 
		BRp FOUR_LOOP 
		BRnz DONE 

DONE 		HALT



VALUE 		.FILL x00e0

		.END
