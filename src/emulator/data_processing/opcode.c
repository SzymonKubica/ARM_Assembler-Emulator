#include <stdio.h>

#define and 0b0000
#define eor 0b0001
#define sub 0b0010
#define rsb 0b0011
#define add 0b0100
#define tst 0b1000
#define teq 0b1001
#define cmp 0b1100
#define mov 0b1101

#define lsl 0b00
#define lsr 0b01
#define asr 0b10
#define ror 0b11

typedef unsigned char Byte;
typedef unsigned long int Word;

Byte immediate_operand (Byte firstByte) {
    return firstByte & 1;
}

Byte get_OpCode (Byte firstByte, Byte secondByte) {
    return ((firstByte & 1) + secondByte) >> 4;
}

Byte get_Rn (Byte secondByte) {
    return secondByte & 0b1111;
}

Byte get_Rd (Byte thirdByte) {
    return thirdByte >> 4;
}

// shifts bits according to shiftType
Word shifter (Byte shiftType, Byte shiftAmount, Word word) {
    switch (shiftType){
        case 0: // logical left
            return word << shiftAmount;
        case 1: // logical right
            return word >> shiftAmount;
        case 2: // arithmetic right
            return word /  (1 << shiftAmount);
        case 3: // rotate right
            return  (word >> shiftAmount) | (word << (32 - shiftAmount));
    }
} 

// short: 2 bytes
unsigned short get_Operand2 (Byte thirdByte, Byte fourthByte, 
Byte immediate_operand, Word * registers) {

    // Operand2 immediate value
	if (immediate_operand) {
        Byte rotation = (thirdByte & 0b1111) << 1; 
        return shifter (3, rotation, fourthByte);
    }

	// Operand2 register
	else {
		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.

        Byte Rm = fourthByte & 0b1111;
    
		Byte shift = (thirdByte & 0b1111 << 4) | (fourthByte >> 4);
        Byte shiftType = shift & 0b110 >> 1;

        Word wordToShift = registers[Rm]
        
		if (!(shift & 0b1)) { // Bit 4 is 0: shift by a constant.
            Byte integer = shift >> 3;
            return shifter (shiftType, integer, wordToShift); //TODO: Rm needs to be modified by a specific shift and returned.
		} else {// Bit 4 is 1: shift by a specified register.
            // This part is optional.
            Byte shiftRegister = shift >> 4;
            return shifter (shiftType, registers[(shift >> 4)], wordToShift)
		}
    }
}



// TODO:
/*
void execute_operation (Byte opCode, unsigned long int *registers, 
Byte Rn, Byte Rd, unsigned short operand2) {
    
    // unsigned long int * destination = &registers[Rd];


    // TODO: implement CPSR manipulation
    switch (opCode) {
        case and:
            registers[Rd] = registers[Rn] & operand2;
            break;
        case eor:
            registers[Rd] = registers[Rn] ^ operand2;
            break;
        case sub:
            registers[Rd] = registers[Rn] - operand2;
            break;
        case add:
            registers[Rd] = operand2 - registers[Rn];
            break; 
        
    }

}
*/

int main (void) {

    Word registers[17];
    memset (registers, 0, 1);

    Byte tb = 0b10001000, fob = 0b10000000;
    printf ("%d \n", get_Rd(tb));
    printf ("%d \n", get_Operand2(tb, fob));

    return 0;
}



