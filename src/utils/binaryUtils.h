#include <stdlib.h>
#include <stdio.h>

#define MEMORY_CAPACITY 65536
#define BYTES_IN_A_WORD 4
#define BITS_IN_A_WORD 32
#define BITS_IN_A_CHAR 8

/*
 * Binary utilities module: tools for printing 32b words as binary strings.
 */

extern char * charToBinaryString(unsigned char input);
extern void printChar(unsigned char input);
extern void printWord(char *word);



