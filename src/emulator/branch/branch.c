#include <stdio.h> 
#include "../../defns.h"
#include "binaryString.h"
#include "../common_functions/common.h"

#define PC 15

static word_t get_offset (byte_t *secondByte) {
	return ((secondByte[0] << 16) | (secondByte[1] << 8)) | secondByte[2];
}

static word_t get_sign_extended_offset (word_t offset) {
	// Pre: After shifting offset is precisely 26 bits long.
  if (offset >> 24) { // If the most significant bit is non-zero.

		// We copy the leftmost bit 8 times.
		word_t filler = readBinaryWord("1111 1100 0000 0000 0000 0000 0000 0000");
		return filler | offset;
	} else {

		// The leftmost bit is zero, so adding it 8 times doesn't alter the offset.
		return offset;
	}
}

void execute_branch (byte_t *firstByte, word_t *registers) {
	word_t offset = get_offset(firstByte); 
	offset = offset << 2;
	word_t extended_offset = get_sign_extended_offset(offset);
	registers[PC] += extended_offset;
}


