#include "binaryUtils.h"	

/*
 * Binary utilities module: implementation.
 */

char * charToBinaryString(unsigned char input) {
	char *binStr = (char *) malloc(BITS_IN_A_CHAR);
	unsigned char mask = 1 << (BITS_IN_A_CHAR - 1); 
	for (int i = 0; i < BITS_IN_A_CHAR; i++) {
		if ((input & mask) != 0) {
			*(binStr + i) = '1';
		} else {
			*(binStr + i) = '0';
		}
		mask = mask >> 1;
	}
	*(binStr + BITS_IN_A_CHAR) = '\0';
	return binStr;
}

void printChar(unsigned char input) {
	char *binStr = charToBinaryString(input);	
	while (*binStr != '\0') {
		printf("%c", *binStr);
		binStr++;
	}
}

void printWord(char *word) {
	for (int i = 0; i < BITS_IN_A_WORD; i++) {
		printf("%c", *(word + i));
		if (i % BITS_IN_A_CHAR == 7) {
			printf(" ");
		}
	}
	printf("\n");
}

