#include <stdlib.h>
#include <stdio.h>

#include "cond.h"
#include "defns.h"


#include "data_processing.h"
#include "multiply.h"
#include "single_data_transfer.h"
#include "branch.h"

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
		fclose(file); 
	}
}

enum instruction decode (byte_t * word) {
	// code - bit 27 26
	byte_t code = (word[0] >> 2) & 3;

	switch (code) {
		case 1 :
			return single_data_transfer;
		case 3: 
			return branch;
		default:
			// data processing or multiply
			if (((word[0] & 3) == 0) 
					&& ((word[1] >> 6) == 0)
				       	&& ((word[3] >> 4) == 9)) {
				return multiply;
			} else {
				return data_processing;
			}
	}
}

void execute (byte_t *word, word_t *registers, byte_t *memory) {
	enum instruction code = decode (word);
	switch (code) {
		case data_processing:
			execute_data_processing (word, registers);
			break;
		case multiply:
			execute_multiply (word, registers);
			break;
		case single_data_transfer:
			execute_single_data_transfer (word, registers, memory);
			break;
		case branch:
			execute_branch (word, registers);
			break;
	}

}

void reverse_instruction (byte_t *fetched_Instruction, byte_t *decoded_Instruction) {
	for (int i = 0; i< 4; i++) {
		decoded_Instruction[i] = fetched_Instruction[3-i];
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


	// 3 stage pipeline
	byte_t *fetched_Instruction;
	byte_t decoded_Instruction[4] = {0,0,0,0};
	byte_t *execute_Instruction;

	// initialisation:
	fetched_Instruction = memory;
	registers[PC] += 4;

	reverse_instruction (fetched_Instruction, decoded_Instruction);
	int n = registers[PC];
	fetched_Instruction = memory + n;
	registers[PC] += 4;

	// main loop
	while (decoded_Instruction[0] 
		|| decoded_Instruction[1]
		|| decoded_Instruction[2]
		|| decoded_Instruction[3]) {
		
		execute_Instruction = decoded_Instruction;
		
		if (checkCond(decoded_Instruction[0], registers[CPSR])) {
			execute(execute_Instruction, registers, memory);
		}

		//decode instruction
		reverse_instruction (fetched_Instruction, decoded_Instruction);

		int n = registers[PC];
		fetched_Instruction = memory + n;

		registers[PC] += 4;
	}
	// Print Output  
	// print program state
	printf("Registers:\n"); 
	for (int i = 0; i < 13; i++) {
		printf("$%-3d: %10d (0x%08x)\n", i, registers[i],registers[i]);
	}

	printf("PC  : %10d (0x%08x)\n", registers[PC], registers[PC]);
	printf("CPSR: %10d (0x%08x)\n", registers[CPSR], registers[CPSR]);

	printf("Non-zero memory:\n");
	
	for (int i = 0; i < num_words; i++) {
		if (!(memory[i*4] || memory[i*4 + 1] || memory[i*4 + 2] || memory[i*4 + 3])) {
			continue;
		}

		printf("0x%08x: 0x", i * 4);
		for (int n = 0; n < 4 ; n++) {
			printf("%02x", memory[i * 4 + n]);
		}
		printf ("\n");
	}
	
	free(memory);
  	return EXIT_SUCCESS;
}
