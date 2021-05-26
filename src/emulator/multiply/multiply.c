#include <stdio.h> 
#include "../../defns.h"
#include "binaryString.h"
#include "../common_functions/common.h"

byte_t get_Rn_multiply (byte_t thirdByte) {
	return get_First_Nibble(thirdByte); 
}

byte_t get_Rd_multiply (byte_t secondByte) {
	return get_Second_Nibble(secondByte);
}

byte_t get_Rs (byte_t thirdByte) {
	return get_Second_Nibble(thirdByte); 
}

byte_t get_Rm (byte_t fourthByte) {
	return get_Second_Nibble(fourthByte);
}

byte_t get_A (byte_t secondByte) {
	return get_First_Nibble(secondByte) >> 1;
}

byte_t get_S (byte_t secondByte) {
	return get_First_Nibble(secondByte) & 1;
}

void set_CPSR (word_t result, word_t *cpsr) {
	*cpsr &= 0x7fffffff;
	*cpsr |= (result >> 31) << 31;
	if(!result) {
        	*cpsr |= 0x40000000;
	}	       
}

void execute_multiply (byte_t *firstByte, word_t *registers) {
	if (get_A(firstByte[1])) {
		registers[get_Rd(firstByte[1])] 
			= get_Rm(firstByte[3]) * get_Rs(firstByte[2]) + get_Rn(firstByte[2]);
	} else {
		registers[get_Rd(firstByte[1])]
			= get_Rm(firstByte[3]) * get_Rs(firstByte[2]); 
	}
	
	if (get_S(firstByte[1])) {
		set_CPSR(registers[get_Rd(firstByte[1])], &registers[16]);
	}
}

int main(void) {
	return 0; 
}
