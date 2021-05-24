#include"fileInput.h"

/*
 * File Input/Output module: implementation.
 */

// Reads characters from a binary input file.
void readChars(char *source, unsigned char* destination, int destinationSize) {
	FILE *ptr;
	ptr = fopen(source, "rb");
	fread(destination, destinationSize, 1, ptr);
}

// Counts chars that can be read from the source binary file.
int countChars(char *source) {
	FILE *ptr;
	ptr = fopen(source, "rb");
	char ch = getc(ptr);
	int len = 0;
	while (ch != EOF) {
		len++;
		ch = getc(ptr);
	}
	return len;
}

// Determines whether a binary file was supplied to program arguments.
bool wasFileProvided(int argc) {
	return argc >= 2;
}

