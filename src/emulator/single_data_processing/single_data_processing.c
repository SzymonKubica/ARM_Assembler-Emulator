#include "../../defns.h"
#include "binaryString.h"
#include "common.h"

byte_t immediate_operand (byte_t firstByte) {
	return (firstByte & readBinary("00000010")) >> 1;
}

byte_t get_pre_post_indexing_bit(byte_t firstByte) {
	return firstByte & readBinary("00000001");	
}

byte_t get_up_bit(byte_t secondByte) {
	return secondByte & readBinary("10000000");
}

byte_t get_load_store_bit(byte_t secondByte) {
	return secondByte & readBinary("00010000");
}

byte_t get_shifted_register(byte_t thirdByte) {
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

static byte_t add_offset(byte_t Rn, byte_t offset) {
	return Rn + offset;	
}

static byte_t subtract_offset(byte_t Rn, byte_t offset) {
	return Rn - offset;
}

static void load(byte_t Rn, byte_t Rd, word_t *registers, byte_t *memory) {
	registers[Rn] = memory[registers[Rd]];
}

static void store(byte_t Rn, byte_t Rd, word_t *registers, byte_t *memory) {
	memory[registers[Rd]] = registers[Rn];
}

static void execute_pre_indexing(byte_t *firstByte, 
	word_t *registers, byte_t*memory
) {
	byte_t Rn = get_Rn(firstByte[1]);

	if (get_up_bit(firstByte[1])) {
		Rn = add_offset(
				Rn, 
				get_offset(firstByte[2], firstByte[3], immediate_operand(firstByte[0]), registers) 
		);	
	} else {
		Rn = subtract_offset(
				Rn, 
				get_offset(firstByte[2], firstByte[3], immediate_operand(firstByte[0]), registers)
		);	
	}

	if (get_load_store_bit(firstByte[1])) {
		load(Rn, get_Rd(firstByte[2]), registers, memory);
	} else {
		store(Rn, get_Rd(firstByte[2]), registers, memory);
	}
}

static void execute_post_indexing(byte_t *firstByte, word_t *registers,
 byte_t *memory
) {
	byte_t Rn = get_Rn(firstByte[1]);

	if (get_load_store_bit(firstByte[1])) {
		load(Rn, get_Rd(firstByte[2]), registers, memory);
	} else {
		store(Rn, get_Rd(firstByte[2]), registers, memory);
	}

	if (get_up_bit(firstByte[1])) {
		registers[Rn] = add_offset(
				Rn, 
				get_offset(firstByte[2], firstByte[3], immediate_operand(firstByte[0]), registers)
		);	
	} else {
		registers[Rn] = subtract_offset(
				Rn, 
				get_offset(firstByte[2], firstByte[3], immediate_operand(firstByte[0]), registers)
		);	
	}

}



void execute_single_data_transfer (byte_t *firstByte, word_t *registers, byte_t *memory) {
	if (get_pre_post_indexing_bit(firstByte[1])) {

		// Offset added/subtracted to the base register before transferring the data.
		execute_pre_indexing(firstByte, registers, memory);

	} else {

		// Offset added/subtracted to the register after transferring the data.	
		execute_post_indexing(firstByte, registers, memory);
	}
}



int main(void) {

}


