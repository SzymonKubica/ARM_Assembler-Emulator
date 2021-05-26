#include <stdio.h>
#include "../defns.h"

/*
 * Binary String module: implementation.
 */

/*
 * This function takes a string representing a binary number and returns 
 * a Byte equal to the given number.
 * Pre: the number is less than or equal 8 bits.
 */


// NOT NECESSARY: use strlen(str) funciton
int length(char *str) {
	int length = 0;
	for (; *str != '\0'; str++) {
		length++;
	}
	return length;
}

byte_t readBinary(char *str) {
	byte_t byte = 0x0;
	for (int i = length(str), j = -1; i >= 0; i--, j++) {
		if (*(str + i) == '1') {
			byte += (1 << j);
		}
	}
	return byte;
}
