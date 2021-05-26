#include <stdio.h>
#include "../../defns.h"
#include "binaryString.h"


byte_t get_First_Nibble (byte_t byte) {
	reutrn byte >> 4; 
}

byte_t get_Second_Nibble (byte_t byte) {
	return byte & readBinary("1111");
}

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
