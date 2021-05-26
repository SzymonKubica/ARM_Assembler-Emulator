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

byte_t get_Rn (byte_t secondByte) {
    return secondByte & readBinary("1111");
}

byte_t get_Rd (byte_t thirdByte) {
    return thirdByte >> 4;
}

byte_t get_Set_Condition_Code (byte_t thirdByte) {
	return (thirdByte >> 4) & 1;
}


int main (void) {
    return 0;
}