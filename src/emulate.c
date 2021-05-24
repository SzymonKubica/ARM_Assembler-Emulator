#include <stdlib.h>
#include <stdio.h>

#define PC 15
#define memorySize 65536


//returns number of words
void parse_file (unsigned char *fileArray, const char *arg, int *words) {
	
	FILE *file;
	file = fopen(arg,"rb");

	if(file) {
			
		unsigned char c = fgetc(file);

		for (int i = 0; !feof(file); i++) {
			// printf("%x ", c);

			if (i % 4 == 0) {
				(* words)++;
			}

			fileArray[i] = c;
			c = fgetc(file);
		
		}
	}
}

int main(int argc, char **argv) {
	
	FILE *file;

	file = fopen(argv[1],"rb");

	unsigned char *memory = malloc(memorySize); // holds entire file
	unsigned short registers[16];

	int num_words = 0;

	parse_file(memory, argv[1], &num_words);

	/*
	// print file as hex 
	for (int i =0; i < num_words * 4; i++) {
		printf("%x ", memory[i]);
	}

	printf("\n");
	*/

	// print addresses: words 
	for (int i = 0; i < num_words; i++) {
		printf("0x%08x: 0x", i * 4);
		for (int n = 0; n < 4 ; n++) {
			printf("%02x", memory[i * 4 + n]);
		}
		printf ("\n");
	}
	
	free(memory);

  	return EXIT_SUCCESS;
}
