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

// short: 2 bytes
unsigned short get_Operand2 (Byte thirdByte, Byte fourthByte, 
Byte immediate_operand) {


    // Operand2 immediate value
	if (immediate_operand) {
        Byte rotation = thirdByte & 0b1111; 
        return (fourthByte >> rotation) | (fourthByte << (32 - rotation));
    }

	// Operand2 register
	else {
		// The shift is specified by the second half of the thirdByte and the 
		// first half of the fourthByte.
		Byte shift = (thirdByte & 0b1111 << 4) | (fourthByte >> 4);
		if (!(shift * 0b1)) { // Bit 4 is 0: shift by a constant.
		} else {// Bit 4 is 1: shift by a specified register.
					
		}
    }
	return Byte;
}

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

int main (void) {
    Byte tb = 0b10001000, fob = 0b10000000;
    printf ("%d \n", get_Rd(tb));
    printf ("%d \n", get_Operand2(tb, fob));

    return 0;
}



