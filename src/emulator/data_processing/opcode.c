#include <stdio.h>
#include "../../defns.h"
#include "binaryString.h"

#define and 0 // 0b0000
#define eor 1 // 0b0001
#define sub 2 // 0b0010
#define rsb 3 // 0b0011
#define add 4 // 0b0100
#define tst 8 // 0b1000
#define teq 9 // 0b1001
#define cmp 12// 0b1100
#define mov 13// 0b1101

#define lsl 0 //0b00
#define lsr 1 //0b01
#define asr 2 //0b10
#define ror 3 //0b11


byte_t immediate_operand (byte_t firstByte) {
    return firstByte & 1;
}

byte_t get_OpCode (byte_t firstByte, byte_t secondByte) {
    return ((firstByte & 1) + secondByte) >> 4;
}

byte_t get_Rn (byte_t secondByte) {
    return secondByte & readBinary("1111");
}

byte_t get_Rd (byte_t thirdByte) {
    return thirdByte >> 4;
}

// short: 2 bytes
unsigned short get_Operand2 (byte_t thirdByte, byte_t fourthByte, 
byte_t immediate_operand) {


    // Operand2 immediate value
	if (immediate_operand) {
        byte_t rotation = thirdByte & readBinary("1111"); 
        return (fourthByte >> rotation) | (fourthByte << (32 - rotation));
    }

	// Operand2 register
	// Commenting everything out so that compiler doesn't complain.
	/*
	else {
		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.
		byte_t shift = (thirdByte & readBinary("1111") << 4) | (fourthByte >> 4);
        byte_t shiftType = shift & readBinary("110");
		if (!(shift & 1)) { // Bit 4 is 0: shift by a constant.
            //unsigned int shiftValue = shift >> 3;
            return shift; //TODO: Rm needs to be modified by a specific shift and returned.
		} else {// Bit 4 is 1: shift by a specified register.
            // This part is optional.
            byte_t shiftRegister = shift >> 4;
		}
  }
	*/
	unsigned short dummy = 0;
	return dummy;
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
    byte_t tb = readBinary("10001000"), fob = readBinary("10000000");
    printf ("%d \n", get_Rd(tb));
    printf ("%d \n", get_Operand2(tb, fob, 0));

    return 0;
}



