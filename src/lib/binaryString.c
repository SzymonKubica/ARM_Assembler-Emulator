#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../defns.h"

/*
 * Binary String module: implementation.
 */

/*
 * This function takes a string representing a binary number and returns 
 * a Byte equal to the given number.
 * Pre: the number is less than or equal 8 bits.
 */

static char * deleteSpaces(char *str);

byte_t readBinary(char *str) {
	byte_t byte = 0x0;
	str = deleteSpaces(str);
	for (int i = strlen(str), j = -1; i >= 0; i--, j++) {
		if (*(str + i) == '1') {
			byte += (1 << j);
		}
	}
	free (str);
	return byte;
}

byte_t readBinaryWord(char *str) {
	word_t word = 0x0;
	str = deleteSpaces(str);
	for (int i = strlen(str), j = -1; i >= 0; i--, j++) {
		if (*(str + i) == '1') {
			word += (1 << j);
		}
	}
	return word;
}

static int countSpaces(char *str) {
	int counter = 0;
	char *ptr = str;
	for (; *ptr != '\0'; ptr++) {
		if (*ptr == ' ') {
			counter++;
		}
	}
	return counter;
}

static char * deleteSpaces(char *str) {
	char *str2 = malloc(strlen(str) - countSpaces(str));
	char *ptr = str2;
	for (; *str != '\0'; str++) {
		if (*str != ' ') {
			*ptr = *str;
			ptr++;
		}
	}
	return str2;
}
