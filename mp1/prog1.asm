; partners : jgruber5, av28
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string, then print the HIST.

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha(betic) count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST



;To print the Histogram, we first need to load the data of the histogram into a register (R3). With the Hex Data in r3, I then decoded R3 into 		
;bits to evaluate each HEX digit individually in terms of bits. I looped through the first 4 bits of the Histogram data to print the first HEX digit. 
;Then repeated this process 4 times to get a total of 4 HEX digits which is equivalent to the HEX stored in the first address of the histogram.
;I created a loop to go all the way back to the beginning of the decode of R3 but I also incremented the address of R3 to get the next HEX data, 
;decrement the letter counter, and incremented ASCII character (@-Z). When the letter counter reaches 0, we have gone through all of the data in all of 
;the addresses of the histogram. Current ASCII character is printed, space is printed, HEX data printed, then NEWLINE printed.

;INITIALIZING ALL REGISTERS.
AND R0, R0, #0; r0= used register that prints ASCII characters
AND R1, R1, #0; r1 = digit(the hex value to print) AND counter for how many letters have been printed(set to #27) 
AND R2, R2, #0; r2 = bit counter
AND R3, R3, #0; r3 = holds the histogram data 
AND R4, R4, #0; r4 = digit counter
AND R5, R5, #0; R5 = holds value #64 or @ which is the first character of the histogram.
	      ;      Will be incremented 27 times to print the entire alphabet
AND R6, R6, #0; R6 = holds the adress of where the histogram data is stored
		
		LD R6, HIST_ADDR ; starting address of histogram data is loaded into r6
		LDR R3, R6, #0	; the actual data of the histogram is loaded into r3

		ADD R1, R1, #14
		ADD R1, R1, #13	 ; R1 = #27 @ + 26 letters in alphabet
		ST R1, SAVE_R1	; store in R1 right now since r1 will be used in inner loop to hold digit 

		ADD R5, R5, #15
		ADD R5, R5, #15
		ADD R5, R5, #15
		ADD R5, R5, #15
		ADD R5, R5, #4	; R5 = #64 or @ in ASCII, increment 27 times to print out @ + 26 letters 
		

START		
		ST R1, SAVE_R1	; save new value of bin counter after loop
		AND R0, R0, #0	; clear r0 
		ADD R0, R0, R5 	; loading decimal value of first character to R0 to be printed in 	
		
		OUT 		; ASCII printed to monitor
		AND R0, R0, #0 ; clears out R0 so that space can be printed next 
		LD R0, SPACE	; hexadecimal value of space is loaded into R0 and printed in ASCII
				; to monitor
		OUT
		AND R0, R0, #0  ; clears the space value 
		
		
		AND R4, R4, #0 ;digit counter
		ADD R4, R4, #4	; 4 digits in hex

FOUR_LOOP	AND R1, R1, #0
		ADD R2, R2, #4 ; R2 is the bit counter, 4 bits per digit

CHECK_BITS	BRnz NINE_LOOP	; if all 4 bits are checked, loop to see if it is a char or num 
		ADD R1,R1, R1	; leftshift digit
		ADD R3, R3, #0 	; check if r3 is less 0 
		BRn TRUE_S
		BRzp FALSE_S

FALSE_S		ADD R1, R1, #0 ; add 0 to digit 
		ADD R3, R3, R3	; left shift R3
		ADD R2, R2, #-1 ; decrement bit counter 
		BR CHECK_BITS 	; loop back to bits to see how many bits we have checked

TRUE_S		ADD R1, R1, #1 ; add 1 to digit 
		ADD R3, R3, R3 ; left shift 
		ADD R2, R2, #-1	; decrement bit counter 
		BR CHECK_BITS	; loop back 

; loop to check whether the 4 bits we just checked are a number(0-9) or char(A-F)

NINE_LOOP	AND R0, R0, #0	; clear r0 so we can use it to print char or num
		ADD R0, R0, R1	; add current digit to R0 to get ready to print 
		ADD R1, R1, #-9 ; condition to see if digit is a char(greater than 9) or num(lessthan or equal to 9)
		BRp FALSE_N	; DIGIT is a character
		BRnz TRUE_N 	; DIGIT is a number 

TRUE_N 		ADD R0, R0, #12	; ADD '0' in decimal to print out an ascii number of current digit
		ADD R0, R0, #12	
		ADD R0, R0, #12
		ADD R0, R0, #12
		OUT 		; print
		ADD R4, R4, #-1 ; decrement digit counter 
		BRp FOUR_LOOP	; positive = loop again to print next digit 
		BRnz NEWLINE	; negative = first line of histogram is printed, 
				; now go to newline loop for next line of hist. 

FALSE_N 	ADD R0, R0, #12; ; ADD 'A' - 10  in decimal to get offset starting at ASCII 'A'
		ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #12
		ADD R0, R0, #7
		OUT 		; prints out char digit 
		ADD R4, R4, #-1 ; decrement digit counter 
		BRp FOUR_LOOP 	; positive = loop again to print next digit
		BRnz NEWLINE 	; negative = go to newline code

NEWLINE		AND R1, R1, #0	; clear current value of R1 
		LD R1, SAVE_R1	; restore previous value of R1 (#27 for the letter counter)
		ADD R1, R1, #-1   ; current letter -1
		ADD R5, R5, #1	; increment letter printer 
		AND R0, R0, #0 ; clear r0 so it is ready to print a new ASCII
		LD R0, NEW_LINE	
		OUT	; prints new line
		ADD R6, R6, #1 ; increment address of histogram so the next data can be stored in R3
		LDR R3, R6, #0	; next data stored in R3
		ADD R1, R1, #0 ; check to see if we have printed all of the Characters (@-Z)
		BRnz DONE	; All Char is printed
		BRp START	; next Char needs to be printed
		






DONE	HALT			; done


; the data needed by the program


SAVE_R1		.BLKW		#1
NEW_LINE 	.FILL x0A  	; the hex equivalent to a newline in ASCII
SPACE 		.FILL x20 	; hex value of space in ASCII
NUM_LETTERS	.FILL #64	; decimal value of @ which is the starting character of the histogram
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
