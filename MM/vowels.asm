DATA SEGMENT
    MSG1 DB 10,13, 'ENTER THE STRING:$'
    MSG2 DB 10,13, 'NUMBER OF VOWELS: $'
    STR1 DB 50 DUP(0)        ; Reserve space for the input string
    VOWEL_COUNT DB 0         ; Variable to store the count of vowels
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    
    ; Display message to enter the string
    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    ; Read the input string
    LEA SI, STR1             ; SI points to the start of STR1
    MOV AH, 01H

READ_LOOP:
    INT 21H                  ; Read character
    CMP AL, 0DH              ; Check if Enter key (carriage return) is pressed
    JE TERMINATE_INPUT       ; If yes, terminate input
    MOV [SI], AL             ; Store the character in STR1
    INC SI                   ; Move to the next position in STR1
    JMP READ_LOOP            ; Continue reading characters

TERMINATE_INPUT:
    MOV AL, '$'              ; Add end-of-string marker
    MOV [SI], AL

    ; Initialize pointers for checking vowels
    LEA SI, STR1             ; SI points to the start of STR1
    MOV VOWEL_COUNT, 0       ; Reset the vowel counter

CHECK_VOWELS:
    MOV AL, [SI]             ; Load current character
    CMP AL, '$'              ; Check if end of string
    JE DISPLAY_RESULT        ; If end, display the result

    ; Check if the character is a vowel (A, E, I, O, U in uppercase or lowercase)
    MOV BL, AL               ; Copy character to BL for comparison
    CMP BL, 'A'
    JE IS_VOWEL
    CMP BL, 'E'
    JE IS_VOWEL
    CMP BL, 'I'
    JE IS_VOWEL
    CMP BL, 'O'
    JE IS_VOWEL
    CMP BL, 'U'
    JE IS_VOWEL
    CMP BL, 'a'
    JE IS_VOWEL
    CMP BL, 'e'
    JE IS_VOWEL
    CMP BL, 'i'
    JE IS_VOWEL
    CMP BL, 'o'
    JE IS_VOWEL
    CMP BL, 'u'
    JE IS_VOWEL

    ; If not a vowel, continue to the next character
    JMP NEXT_CHAR

IS_VOWEL:
    INC VOWEL_COUNT          ; Increment vowel count if it is a vowel

NEXT_CHAR:
    INC SI                   ; Move to the next character in the string
    JMP CHECK_VOWELS         ; Repeat vowel checking

DISPLAY_RESULT:
    ; Display the message "NUMBER OF VOWELS: "
    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    ; Display the vowel count as a single digit
    MOV AL, VOWEL_COUNT
    ADD AL, '0'              ; Convert to ASCII
    MOV DL, AL
    MOV AH, 02H              ; Function to display a single character
    INT 21H

    ; Exit program
    MOV AH, 4CH
    INT 21H

CODE ENDS
END START
