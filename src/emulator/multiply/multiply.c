#include <stdio.h> 
#include "../../defns.h"
#include "binaryString.h"
#include "common.h"

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

int main(void) {
	// DUMMY
}
