#include <stdio.h>
#include "../../defns.h"

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


byte_t immediate_operand (byte_t firstByte) {
    return firstByte & 1;
}

byte_t get_OpCode (byte_t firstByte, byte_t secondByte) {
    return ((firstByte & 1) + secondByte) >> 4;
}

byte_t get_Rn (byte_t secondByte) {
    return secondByte & 0b1111;
}

byte_t get_Rd (byte_t thirdByte) {
    return thirdByte >> 4;
}

// short: 2 bytes
unsigned short get_Operand2 (byte_t thirdByte, byte_t fourthByte, 
byte_t immediate_operand) {


    // Operand2 immediate value
	if (immediate_operand) {
        byte_t rotation = thirdByte & 0b1111; 
        return (fourthByte >> rotation) | (fourthByte << (32 - rotation));
    }

	// Operand2 register
	else {
		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.
		byte_t shift = (thirdByte & 0b1111 << 4) | (fourthByte >> 4);
        byte_t shiftType = shift & 0b110;
		if (!(shift * 0b1)) { // Bit 4 is 0: shift by a constant.
            unsigned int shiftValue = shift >> 3;
            return shift; //TODO: Rm needs to be modified by a specific shift and returned.
		} else {// Bit 4 is 1: shift by a specified register.
            // This part is optional.
            byte_t shiftRegister = shift >> 4;
		}
    }
	// TODO: return in the second case.
}

void execute_operation (byte_t opCode, unsigned long int *registers, 
byte_t Rn, byte_t Rd, unsigned short operand2) {
    
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

int main (void) {
    byte_t tb = 0b10001000, fob = 0b10000000;
    printf ("%d \n", get_Rd(tb));
    printf ("%d \n", get_Operand2(tb, fob));

    return 0;
}



