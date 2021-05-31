#include <stdio.h> 
#include "../../defns.h"
#include "binaryString.h"
#include "../common_functions/common.h"

#define PC 15

static word_t get_offset (byte_t *secondByte) {
	return ((secondByte[0] << 16) | (secondByte[1] << 8)) | secondByte[2];
}

static int get_sign_extended_offset (word_t offset) {
	// Pre: Offset is precisely 24 bits long.
  if ((offset >> 24) == 1) { // If the most significant bit is non-zero.
		printf("Negative number");

		// We copy the leftmost bit 8 times.
		word_t filler = readBinaryWord("1111 1111 0000 0000 0000 0000 0000 0000");
		return (int) (filler | offset);
	} else {

		// The leftmost bit is zero, so adding it 8 times doesn't alter the offset.
		return offset;
	}
}

void execute_branch (byte_t *firstByte, word_t *registers) {
	word_t offset = get_offset((firstByte + 1)); 
	printf("Offset: %d\n", offset);
	offset = readBinaryWord("1111 1111 1111 1111 11111 1111") & offset << 2;
	printf("Shifted offset: %d\n", offset);
	word_t extended_offset = get_sign_extended_offset(offset);
	printf("Extended offset: %d\n", extended_offset);
	registers[PC] += extended_offset;
}


