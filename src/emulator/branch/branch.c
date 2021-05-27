#include <stdio.h> 
#include "../../defns.h"
#include "binaryString.h"
#include "../common_functions/common.h"

word_t get_offset (byte_t *secondByte) {
	return ((secondByte[0] << 16) | (secondByte[1] << 8)) | secondByte[2];
}

void execute_branch (byte_t *firstByte, word_t *registers) {
	//word_t offset = get_offset(firstByte); 
	// TO DO: Branch Execution Implementation
}

int main(void) {
	return 0; 
}
