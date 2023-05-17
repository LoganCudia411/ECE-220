;
;
;
.ORIG x3000
	;In this program, we followed a 3 step algorithim to simulate a calulator whose inputs are "reverse polish notation". 
        ; To begin, we evaluate whether the inputted character is a number or operator. If it is a number we push then lop back 
        ; and get the next input. If it is an operator, we move to the 2nd step, check the stack. We check the stack to see if we 
        ; are able to pop 2 values from the stack and perform the operation through subroutines. After, we lastly print the value stored in 
        ; in R0. However, we check first for overflow/underflow through the value of R5. If R5 indicates an under/overflow, we print 
        ; "Invalid Expression". If it passes, we print the result of the inputted expression in hex, then store the result in R5 as well. 
        ; partners : cudia2





;your code goes here
	
EVALUATE
	GETC            ; echo input 
	OUT
	LD R1, SPACE_ASCII      ; check if input is space 
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz EVALUATE            ; ignore if space and get next char

        LD R1, EQUAL_ASCII      ; check if equal 
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz EQUAL               ; branch to equal and proceed next steps 

	LD R1, OPERATOR_ADD     ; check if "+"
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz ADD_NUM             ; next step if "+"

        LD R1, OPERATOR_SUB     ; check if "-" 
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz SUB_NUM             ; next step if "-"

        LD R1, OPERATOR_MULT ; check if "*"
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz MULT_NUM            ; next step if "*" 

        LD R1, OPERATOR_DIVI ; check if "/"
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz DIVI_NUM            ; next step if "/" 

        LD R1, OPERATOR_EXP ; check if "^" 
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        BRz EXP_NUM         ; next step if "^"
        
        LD R1, ZERO_ASCII ; subtract hex equivalent of "0" (ascii)
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R0
        ADD R1, R1, #-9 ; then check if it is less than or equal to "9" (ascii)
        BRnz NUMBER

ERROR
        LEA R0, ERROR_MESSAGE ; error branch if we detect underflow/overflow signaled by the value of R5
        PUTS            ; print error string
        HALT            ; end program 

NUMBER
        ADD R0, R0, #-15 ; subtract to get original input 
        ADD R0, R0, #-15
        ADD R0, R0, #-15
        ADD R0, R0, #-3
        ADD R5, R5, #0 
        BRp EVALUATE
        JSR PUSH        ; JSR to push subroutine to add the inputted number to stack 
        BR EVALUATE     ; branch back to evaluate for next input 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; For each of these operation branches, we first CHECK_STACK to see if 2 items are able to be popped. If we are not able
; to pop 2, R5 will signal underflow. If there are at least 2 items in the stack, we pop them, perform operation, then push back the 
; result into the stack. Lastly, we branch back to EVALUATE to get our next input. 

ADD_NUM    
        
        JSR PLUS        
        BR EVALUATE    
MULT_NUM
        
        JSR MUL
        BR EVALUATE

SUB_NUM
        
        JSR MIN
        BR EVALUATE
DIVI_NUM
        
        JSR DIV
        BR EVALUATE
EXP_NUM
        
        JSR EXP
        BR EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PRINT_HEX
			ST R1, SAVE_R1_PRINT ;hex counter
			ST R2, SAVE_R2_PRINT ;decimal counter
			ST R3, SAVE_R3_PRINT ; value to print
                        ST R6, SAVE_R6_PRINT 
                        LD R6, ZERO_ASCII    ; holds ascii '0' as hex equivalent
			AND R1, R1, #0
			AND R2, R2, #0
			AND R3, R3, #0
			ADD R3, R0, #0 ; put value into R3
			AND R0, R0, #0 ; clear R0 and use R0 to print 
			ADD R1, R1, #4
OUTER		
			AND R0, R0, #0 ; clear last printed character
			ADD R2, R2, #4 ; loop 4 times for each bit in one hex digit

INNER		BRnz CONVERT           
			ADD R0, R0, R0
			ADD R3, R3, #0 ; Check if r3 is less than 0 
			BRn MSB_1
			ADD R0, R0, #0 ; add 0 to digit 
			ADD R3, R3, R3 ; left shift R3 to evaluate next bit 
			ADD R2, R2, #-1 ; decrement bit counter 
			BR INNER        ; loop back to check next bit 
MSB_1	
			ADD R0, R0, #1 ; add 1 to R0 
			ADD R3, R3, R3  ; left shift R3 
			ADD R2, R2, #-1 ; decrement bit counter 
			BR INNER        ; loop to check next bit 

CONVERT       ; check to see if digit is (0-9) or (A-F)
			ADD R0, R0, #-9
			BRnz IS_NUMBER
			ADD R0, R0, R6 ; offset input with '0', will print (0-9) in ascii
			ADD R0, R0, #7 
			ADD R0, R0, #9 ; ADD 'A' - 10 to print within ascii range of (A-F)
			OUT
			ADD R1, R1, #-1 ; decrement hex digit counter
			BRp OUTER       ; loop to check next digit 
			BRnz DONE       ; done once weve checked 4 digits 
IS_NUMBER
			ADD R0, R0, R6 ; The hex digit is a number, add back 9 to get within range (0-9) in ascii
			ADD R0, R0, #9
			OUT
		        ADD R1, R1, #-1 ; decrement hex counter 
			BRp OUTER ; loop back to check next digit 
			BRnz DONE ; done once weve checked 4 digits 
DONE	
			LD R1, SAVE_R1_PRINT
			LD R2, SAVE_R2_PRINT
			LD R3, SAVE_R3_PRINT
			HALT
EQUAL

        ; check if there is only 1 item on stack before performing '=' operation 
        ST R1, SAVE_R1_EQ 
        ST R2, SAVE_R2_EQ
        LD R1, STACK_START
        LD R2, STACK_TOP
        ADD R1, R1, #-1 ; increment stack start to point to one entry below
        NOT R1, R1
        ADD R1, R1, #1
        ADD R1, R1, R2
        BRnp ERROR      ; top of the stack should be 1 address above or -1 from x4000 or the starting address of the stack
        JSR POP         ; condition doesnt apply so we pop out the 1 item in stack 
        AND R5, R5, #0  ; clear R5 which signals overflow/underflow 
        ADD R5, R0, #0 ; add the result of operations to R5 
        BR PRINT_HEX    ; print the result 
        BR END          ; end the program 

SAVE_R1_PRINT			.BLKW #1
SAVE_R2_PRINT			.BLKW #1
SAVE_R3_PRINT			.BLKW #1
SAVE_R1_EQ                      .BLKW #1
SAVE_R2_EQ                      .BLKW #1
SAVE_R6_PRINT                   .BLKW #1
ERROR_MESSAGE                   .STRINGZ "Invalid Expression" 
OPERATOR_ADD                    .FILL x002B
OPERATOR_DIVI                   .FILL x002F
OPERATOR_MULT                   .FILL x002A
OPERATOR_SUB                    .FILL x002D
OPERATOR_EXP                    .FILL x005E
SPACE_ASCII                     .FILL x0020
EQUAL_ASCII                     .FILL x003D
ZERO_ASCII                      .FILL x0030
NEG_ZERO                        .FILL xFFD0
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET
END	         HALT
POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


;R3- value to print in hexadecimal, INPUT R0


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
            ST R3, SAVE_R3_ADD
            ST R4, SAVE_R4_ADD
            ST R7, SAVE_R7_ADD
            AND R3, R3, #0 ; initialize input registers 
            AND R4, R4, #0
            AND R5, R5, #0
            JSR POP ; pop #1 ; pop first item 
            ADD R3, R3, R0   ; store value in R3 
            ADD R5, R5, #0     ; check if underflow occured 
            BRp EXIT_ADD ; pop did not work

            JSR POP ; pop #2 
            ADD R4, R4, R0      ; R4 holds second value 
            ADD R5, R5, #0
            BRp EXIT_ADD ; 
            ADD R0, R3, R4      ; add both input registers and store result in R0 to be pushed back to stack 
            JSR PUSH

EXIT_ADD
            LD R3, SAVE_R3_ADD
            LD R4, SAVE_R4_ADD
            LD R7, SAVE_R7_ADD ; save R7 so that we are able to return back to next instruction after initial JSR 
            RET



SAVE_R3_ADD         .BLKW #1
SAVE_R4_ADD         .BLKW #1
SAVE_R7_ADD         .BLKW #1	


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
                ST R3, SAVE_R3_MIN
                ST R4, SAVE_R4_MIN
                ST R7, SAVE_R7_MIN
                AND R3, R3, #0 ; initalize input registers 
                AND R4, R4, #0 ; 
                AND R5, R5, #0
                JSR POP
                ADD R5, R5, #0
                BRp EXIT_MIN ; check indicator R5
                ADD R3, R0, #0 ; R3 holds first value 
                JSR POP 
                ADD R5, R5, #0
                BRp EXIT_MIN ;check indicator R5
                ADD R4, R0, #0 ; second value is held by R4
                NOT R3, R3      ; order goes R4-R3 since LIFO
                ADD R3, R3, #1  ; make R3 negative 
                ADD R0, R3, R4 ; R0 = R4-R3 and push R0 
                JSR PUSH

EXIT_MIN
                LD R3, SAVE_R3_MIN
                LD R4, SAVE_R4_MIN
                LD R7, SAVE_R7_MIN
                RET





SAVE_R3_MIN             .BLKW #1        
SAVE_R4_MIN             .BLKW #1
SAVE_R7_MIN             .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
                ST R2, SAVE_R2_MULT
                ST R3, SAVE_R3_MULT
                ST R4, SAVE_R4_MULT
                ST R7, SAVE_R7_MULT
                AND R2, R2, #0
                JSR POP ; pop first number 
                ADD R5, R5, #0 ; check if pop was successful 
                BRp INVALID_M  ; if R5 = 1, pop was unsuccessful 
                ADD R3, R0, #0  ; first factor 
                BRzp NOT_NEG_1  ; check if positive 
                NOT R3, R3      ; make it positive 
                ADD R3, R3, #1
                ADD R2, R2, #1  ; signal that R3 was previously negative by making R2 = 1 
NOT_NEG_1
                JSR POP ; pop second number
                ADD R5, R5, #0 ; check pop and branch accordingly 
                BRp INVALID_M
                ADD R4, R0, #0 ; check if 2nd factor is negative 
                BRzp NOT_NEG_2 ; if not negative, branch 
                NOT R4, R4     ; if negative, make positive and add 1 to R2 to signal that R4 was previously negative 
                ADD R4, R4, #1
                ADD R2, R2, #1
NOT_NEG_2
                AND R0, R0, #0 ; clear R0 
                ADD R3, R3, #0  ; set PC to R3 
                ADD R0, R4, #0  ; ADD 2nd factor back to R0 
MULT_LOOP       
                ; ADD R4 to R0 (R4) until R3 is zero 
                ADD R3, R3, #-1 
                BRnz DONE_MULT ; branch when R3 is 0 
                ADD R0, R4, R0
                BR MULT_LOOP ; loop back 
DONE_MULT       
                ; check condition of R2 to see if we need to change the sign of the product
                ADD R2, R2, #0
                BRnz POS_OUT  ; if R2 is 2 the product is positive
                ADD R2, R2, #-2
                BRz POS_OUT ; if R2 is 0, the product is also positive 
                NOT R0, R0  ; R2 is 1 and therefore R0 is neegative
                ADD R0, R0, #1 ; making R0 negative
POS_OUT         JSR PUSH  ; push result 
INVALID_M
                LD R3, SAVE_R3_MULT
                LD R4, SAVE_R4_MULT
                LD R7, SAVE_R7_MULT
                RET

SAVE_R2_MULT            .BLKW #1
SAVE_R3_MULT            .BLKW #1
SAVE_R4_MULT            .BLKW #1
SAVE_R7_MULT            .BLKW #1
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
                ST R2, SAVE_R2_DIV
                ST R3, SAVE_R3_DIV
                ST R4, SAVE_R4_DIV
                ST R7, SAVE_R7_DIV
                JSR POP ;pop #1 (DIVISOR)
                ADD R5, R5, #0 ; check if underflow
                BRp EXIT_DIV
                ADD R3, R0, #0 ;R3 is the divisor 
                BRnz DIVI_ZERO
                JSR POP ; pop #2 (DIVIDEND)
                ADD R5, R5, #0
                BRp EXIT_DIV
                ADD R4, R0, #0  ; R4 has the dividend 
                BRn EXIT_DIV
                ADD R2, R3, #0 ; move divisor to R2 
                NOT R3, R3     ; make divisor negative 
                ADD R3, R3, #1
                AND R0, R0, #0

DIV_LOOP
                ADD R4, R4, R3  ; add dividend to divisor 
                BRn DONE_DIV    ; Once the dividend is no longer greater than or equal to divisor 
                ADD R0, R0, #1 ; Quotient or how many times the Dividend can be subtracted by the divisor before it the dividend is negative
                BR DIV_LOOP  ; loop back 
DONE_DIV
                JSR PUSH ; push quotient in R0 into stack 
                BR EXIT_DIV
DIVI_ZERO
                JSR POP
EXIT_DIV            
                LD R2, SAVE_R2_DIV
                LD R3, SAVE_R3_DIV
                LD R4, SAVE_R4_DIV
                LD R7, SAVE_R7_DIV
                RET

SAVE_R2_DIV             .BLKW #1
SAVE_R3_DIV             .BLKW #1
SAVE_R4_DIV             .BLKW #1
SAVE_R7_DIV	        .BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
        ST R2, SAVE_R2_EXP
        ST R3, SAVE_R3_EXP
        ST R4, SAVE_R4_EXP
        ST R7, SAVE_R7_EXP
        JSR POP ; pop out exponent
        ADD R5, R5, #0
        BRp INVALID
        ADD R3, R0, #0 ; check if exponent or number we exponent is negative
        BRz POWER_ZERO ; if x^0 
        BRn INVALID
        JSR POP ; pop out number we exponent
        ADD R5, R5, #0 ;check for underflow
        BRp INVALID
        ADD R4, R0, #0 ; move power to R4
        BRz BASE_ZERO ; if 0^x branch 
        BRn INVALID 
        ST R4, SAVE_R4_COUNT ; store number we exponent
        ADD R3, R3, #-1 ; decrement exponent 
EXP_LOOP_OUTER 
        ADD R4, R0, #0 ; move base to R4
        AND R0, R0, #0 ; clear R0
        LD R2, SAVE_R4_COUNT ; mult counter by exponent val
        BRz EXIT_EXP 
INNER_LOOP
        ADD R0, R0, R4 ; perform first multiplication
        ADD R2, R2, #-1 
        BRp INNER_LOOP ; loop back until first mult loop is done
        ADD R3, R3, #-1 ; decriment exponent counter
        BRp EXP_LOOP_OUTER
        BRnz EXIT_EXP
BASE_ZERO
        AND R0, R0, #0 ; push 0
        BR EXIT_EXP
POWER_ZERO
        AND R0, R0, #0
        ADD R0, R0, #1 ; push 1
        BR EXIT_EXP

EXIT_EXP
        JSR PUSH
INVALID 
        LD R2, SAVE_R2_EXP
        LD R3, SAVE_R3_EXP
        LD R4, SAVE_R3_EXP
        LD R7, SAVE_R7_EXP
        RET

SAVE_R4_COUNT           .BLKW #1
SAVE_R2_EXP             .BLKW #1
SAVE_R3_EXP             .BLKW #1
SAVE_R4_EXP             .BLKW #1
SAVE_R7_EXP             .BLKW #1



;


.END
