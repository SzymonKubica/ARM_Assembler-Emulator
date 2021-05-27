#include <stdlib.h>
#include <stdio.h>

#include "cond.h"
#include "defns.h"

#define PC 15
#define CPSR 16
#define memorySize 65536

enum instruction{data_processing, multiply, single_data_transfer, branch};

// parse file into fileArray and update num words
void parse_file (byte_t *fileArray, const char *arg, int *words) {
	
	FILE *file;
	file = fopen(arg,"rb");

	if(file) {
			
		byte_t c = fgetc(file);

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
	
	byte_t *memory = malloc(memorySize); // holds entire file
	word_t registers[17];

	for (int i = 0; i < 17; i++){
		registers[i] = 0;
	}

	int num_words = 0;

	parse_file (memory, argv[1], &num_words);

	/*
	// print file as hex 
	for (int i =0; i < num_words * 4; i++) {
		printf("%x ", memory[i]);
	}

	printf("\n");
	*/

	// print output
	// print program state
	for (int i = 0; i < 13; i++) {
		printf("$%d : %ld (0x%08lx)\n", i, registers[i],registers[i]);
	}

	printf("PC : %ld (0x%08lx)\n", registers[PC], registers[PC]);
	printf("CPSR : %ld (0x%08lx)\n", registers[CPSR], registers[CPSR]);

	printf("Non-zero memory:\n");
	// printf("%d\n", num_words);
	
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
