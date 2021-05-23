#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	
	/* The memory has 64KB (65536 bytes), but it is 4 bytes aligned, 
	** so we need 65536 / 4 = 16384 memory locations each 4 bytes long.
	** each locations stores 32 bits which is equal to sizeof(int).
	*/
	static const int wordsInMemory = 16384;
	int *memory = calloc(wordsInMemory, sizeof(int));

	if (argc < 2) {
		printf("\n Error. \n No binary file provided.");
		return -1;
	}

	FILE *binaryInput = fopen(argv[1], "rb");
	fread(&memory, sizeof(int), wordsInMemory, binaryInput);

  return EXIT_SUCCESS;
}
