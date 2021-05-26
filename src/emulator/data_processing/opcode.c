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
    return (firstbyte & 2) >> 1;
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

// shifts bits according to shiftType
word_t shifter (byte_t shiftType, byte_t shiftAmount, word_t word) {
	switch (shiftType){
		case 0: // logical left
			return word << shiftAmount;
		case 1: // logical right
			return word >> shiftAmount;
		case 2: // arithmetic right
			return word /  (1 << shiftAmount);
		case 3: // rotate right
			return  (word >> shiftAmount) | (word << (32 - shiftAmount));
		default: // should never be reached
			return 0;
	}
} 

// short: 2 bytes
unsigned short get_Operand2 (byte_t thirdByte, byte_t fourthByte, 
byte_t immediate_operand, word_t * registers) {

	// Operand2 immediate value
	if (immediate_operand) {
		byte_t rotation = (thirdByte & readBinary("1111")) << 1; 
		return shifter (3, rotation, fourthByte);
	}

	// Operand2 register
	else {		
		byte_t Rm = fourthByte & readBinary("1111");

		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.

		byte_t shift = (thirdByte & readBinary("1111") << 4) | (fourthByte >> 4);
		byte_t shiftType = shift & readBinary("110") >> 1;

		//TODO: Issue: Compilation fails because registers is out of scope in the function.
		word_t wordToShift = registers[Rm];

			if (!(shift & 1)) { // Bit 4 is 0: shift by a constant.
				byte_t integer = shift >> 3;
				return shifter (shiftType, integer, wordToShift); 
			} else {// Bit 4 is 1: shift by a specified register.
				// This part is optional?
				byte_t shiftRegister = shift >> 4;
				return shifter (shiftType, registers[shiftRegister], wordToShift);
			}
	}
}

byte_t get_Set_Condition_Code (byte_t thirdByte) {
	return (thirdByte >> 4) & 1;
}

// TODO:
/*
void execute_operation (byte_t opCode, Word *registers, 
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

	word_t registers[17];
	memset (registers, 0, 1);

	byte_t tb = readBinary("10001000"), fob = readBinary("10000000");
	printf ("%d \n", get_Rd(tb));
	printf ("%d \n", get_Operand2(tb, fob));

	return 0;
}
*/
