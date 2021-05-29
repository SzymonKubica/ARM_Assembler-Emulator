#include <stdio.h>
#include "../../defns.h"
#include "binaryString.h"
#include "data_processing.h"
#include "common.h"

#define and 0 // 0b0000
#define eor 1 // 0b0001
#define sub 2 // 0b0010
#define rsb 3 // 0b0011
#define add 4 // 0b0100
#define tst 8 // 0b1000
#define teq 9 // 0b1001
#define cmp 10// 0b1010
#define orr 12// 0b1100
#define mov 13// 0b1101

#define lsl 0 //0b00
#define lsr 1 //0b01
#define asr 2 //0b10
#define ror 3 //0b11

static byte_t get_immediate_operand (byte_t firstByte) {
	return (firstByte & 2) >> 1;
}

static byte_t get_OpCode (byte_t firstByte, byte_t secondByte) {
	return ((firstByte & 1) << 3) | ((secondByte) >> 5);
}

static byte_t get_Rn (byte_t secondByte) {
	return secondByte & readBinary("1111");
}

static byte_t get_Rd (byte_t thirdByte) {
	return thirdByte >> 4;
}

static byte_t get_S (byte_t secondByte) {
	return get_First_Nibble(secondByte) & 1;
}

static word_t shifter (byte_t shiftType, byte_t shiftAmount, word_t word, bit_t *carry) {
	switch (shiftType){
		case 0: // logical left
			*carry = (((word << shiftAmount) - 1) >> 31) & 1; 
			return word << shiftAmount;
		case 1: // logical right
			*carry = ((word >> shiftAmount) - 1) & 1; 
			return word >> shiftAmount;
		case 2: // arithmetic right
			*carry = ((word >> shiftAmount) -1) & 1; 
			return word / (1 << shiftAmount);
		case 3: // rotate right
			*carry = ((word >> shiftAmount) -1) & 1; 
			return  (word >> shiftAmount) | (word << (32 - shiftAmount));
		default: // ERROR: Should never be reached
			return -1;
	}
} 

static word_t get_Operand2 (byte_t thirdByte, byte_t fourthByte, 
		byte_t immediate_operand, word_t *registers, bit_t *carry) {

	// Operand2 immediate value
	if (immediate_operand) {
		byte_t rotation = (thirdByte & readBinary("1111")) << 1; 
		return shifter (3, rotation, fourthByte, carry);
	}

	// Operand2 register
	else {		
		byte_t Rm = fourthByte & readBinary("1111");

		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.

		byte_t shift = ((thirdByte & readBinary("1111")) << 4) | (fourthByte >> 4);
		byte_t shiftType = (shift & readBinary("110")) >> 1;

		word_t wordToShift = registers[Rm];

		if (!(shift & 1)) { // Bit 4 is 0: shift by a constant.
			byte_t integer = shift >> 3;
			return shifter (shiftType, integer, wordToShift, carry); 
		} else {
			// Bit 4 is 1: shift by a specified register.
			//(optional)
			byte_t Rs = get_First_Nibble (thirdByte);
			return shifter (shiftType, registers[Rs], wordToShift, carry);
		}
	}
}

// static byte_t get_Set_Condition_Code (byte_t thirdByte) {
// 	return (thirdByte >> 4) & 1;
// }

static void set_CPSR (word_t result, word_t *cpsr, bit_t logical_op, bit_t carry) {
	// Set N-bit
	*cpsr &= 0x7fffffff;
	*cpsr |= (result >> 31) << 31;
	// Set Z-bit -- DOUBLE CHECK if-and-only-if on page VI of spec
	if(!result) {
		*cpsr |= 0x40000000;
	} else {
		*cpsr &= 0xbfffffff;
	}

	// Set C-bit to 0
	*cpsr &= 0xdfffffff;
	*cpsr |= (carry << 28);

}


void execute_data_processing (byte_t *firstByte, word_t *registers) {

	bit_t carry = 0;
	word_t operand2 
		= get_Operand2(firstByte[2], firstByte[3], 
				get_immediate_operand(firstByte[0]), registers,
				&carry); 

	byte_t Rn = get_Rn(firstByte[1]);
	byte_t Rd = get_Rd(firstByte[2]);

	byte_t opCode = get_OpCode(firstByte[0], firstByte[1]);
	word_t result = 0; 
	bit_t logical_op = 0; 

	switch (opCode) {
		case and:
			registers[Rd] = registers[Rn] & operand2;
			result = registers[Rd];
			logical_op = 1;	
			break;
		case eor:
			registers[Rd] = registers[Rn] ^ operand2;
			result = registers[Rd];
			logical_op = 1;
			break;
		case sub:
			registers[Rd] = registers[Rn] - operand2;
			result = registers[Rd]; 
			//logical_op = -1;
			carry = (long int) result < 0 ? 0 : 1;
			break;
		case rsb:
			registers[Rd] = operand2 - registers[Rn];
			result = registers[Rd];
		       	//logical_op = -1;
			carry = (long int) result < 0 ? 0 : 1;
			break;
		case add:
			registers[Rd] = registers[Rn] + operand2;
			result = registers[Rd];
		       	
			// if carry set C to 1
			carry = (registers[Rn] + operand2) >> 31 ? 1 : 0;
			break;
		case tst:
			result = registers[Rn] & operand2; 
			logical_op = 1; 
			break;
		case teq: 
			result = registers[Rn] ^ operand2; 
			logical_op = 1;
			break;
		case cmp:
			// if borrow carry = 0
			result = registers[Rn] - operand2; 
			//logical_op = -1;
			carry = (long int) result < 0 ? 0 : 1;
			break;
		case orr:
			registers[Rd] = registers[Rn] | operand2; 
			result = registers[Rd];
			logical_op = 1; 
			break;
		case mov:
			registers[Rd] = operand2; 
			result = registers[Rd];
			logical_op = 1; 	
			break; 	
	}

	if (get_S(firstByte[1])) {
		set_CPSR(result, &registers[16], logical_op, carry); 
	}
}

