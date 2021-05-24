#ifndef FILE_IO_H
#define FILE_IO_H
#include <stdbool.h>
#include <stdio.h>

/*
 * File Input/Output module.
 */

extern void readChars(
	char *source, unsigned char* destination, int destinationSize
);
extern int countChars(char *source);
extern bool wasFileProvided(int argc);

#endif
