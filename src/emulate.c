#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
	
static const int MEMORY_CAPACITY = 65536;
static const int BYTES_IN_A_WORD = 4;
static const int BITS_IN_A_CHAR = 8;
static const int BITS_IN_A_WORD = 32;


void readChars(char *source, unsigned char* destination) {
	FILE *ptr;
	ptr = fopen(source, "rb");
	fread(destination, MEMORY_CAPACITY, 1, ptr);
}

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
	for (int i = 0; i < BYTES_IN_A_WORD; i++) {
		printf("%c", *(word + i));
	}
	printf("\n");
}

void printMemory(unsigned char *memory, int occupiedLength) {
	for (int i = 0; i < occupiedLength; i++) {
		printChar(*(memory + i));
		printf(" ");
		if (i % 2 == 1) {
			printf("\n");
		}
	}
	printf("\n");
}

void printMemoryHex(unsigned char *memory, int occupiedLength) {
	for (int i = 0; i < occupiedLength; i++) {
		printf("%x ", *(memory + i));
	}
	printf("\n");
}

bool wasFileProvided(int argc) {
	return argc >= 2;
}

// This function abstracts out a single word from the memory and returns
// a binary string. 
char * readWordFromMemoryAt(int address, unsigned char *memory) {
	char *str = malloc(BITS_IN_A_WORD);
	char *ptr = str;
	for (int i = address; i < address + BYTES_IN_A_WORD ; i++) {
		strcpy(ptr, charToBinaryString(*(memory + i)));
		ptr+=8;
	} 
	return str;
}

int main(int argc, char **argv) {
	/*
	** As specified in the spec, the binary files are represented in little-endian
	** byte order. Hence as bytes are loaded on the memory, first byte in the 
	** binary file (LSB) is loaded onto the lowest address in memory array.  	
	*/
	
	unsigned char memory[MEMORY_CAPACITY]; 

	if (!wasFileProvided(argc)) {
		printf("Error. No binary file provided.");
		return -1;
	}

	readChars(argv[1], memory);

	int len = countChars(argv[1]);

	printMemory(memory, len);

	printMemoryHex(memory, len);

	char *word = readWordFromMemoryAt(0, memory);

	printWord(word);

  return EXIT_SUCCESS;
}
