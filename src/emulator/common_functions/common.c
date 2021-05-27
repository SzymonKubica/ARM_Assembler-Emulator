#include <stdio.h>
#include "../../defns.h"
#include "binaryString.h"


byte_t get_First_Nibble (byte_t byte) {
	return byte >> 4; 
}

byte_t get_Second_Nibble (byte_t byte) {
	return byte & readBinary("1111");
}

