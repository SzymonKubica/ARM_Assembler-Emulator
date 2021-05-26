#include "../../defns.h"
#include "binaryString.h"
#include "common.h"

byte_t immediate_operand (byte_t firstByte) {
	return (firstbyte & readBinary("00000010")) >> 1;
}

byte_t get_pre/post_indexing_bit(byte_t firstByte) {
	return firstbyte & readBinary("00000001");	
}

byte_t get_up_bit(byte secondByte) {
	return secondByte & readBinary("10000000");
}

byte_t get_load/store_bit(byte secondByte) {
	return secondByte & readBinary("00010000");
}

byte_t get_shifted_register(byte thirdByte) {
	return get_Second_Nibble(thirdByte);
}

// short: 2 bytes (16b), we need 12 bits for the offset or register.
unsigned short get_offset(byte_t thirdByte, byte_t fourthByte, 
		byte_t immediate_offset, word_t * registers) {

	if (immediate_offset) {
		// Offset is a shifted register
		// Shift value is the last byte of the registers content
		return registers[get_shifted_register(thirdByte)] & readBinary("11111111");
	} else {
		// Offset is an immediate offset.
		return ((thirdByte & readBinary("1111")) << 8) | fourthByte;
	}
}

void execute_single_data_transfer (byte_t *firstByte, word_t *registers) {
	if (get_pre/post_indexing_bit(firstByte[1])) {
		// Offset added/subtracted to the base register before transferring the data.
		if (get_up_bit(firstByte[1])) {
			// Offset added to the base register.
		} else {
			// Offset subtracted from the base register. 
		}
  }
	 else {
		// Offset added/subtracted to the register after transferring the data.	
		if (get_up_bit(firstByte[1])) {
			// Offset added to the base register.
		} else {
			// Offset subtracted from the base register. 
		}
	}
}



int main(void) {

}


