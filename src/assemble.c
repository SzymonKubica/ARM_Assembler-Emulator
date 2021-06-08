#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#include "assembler_defs.h"
#include "data_processing.h"

#define MAX_LINE_LENGTH 512 

typedef struct {
	char *label;
	int  address; 
} label_t;

// typedef struct {
// 	char *mnemonic;
// 	char **operand_fields; 
// } instruction_t;
/*
// returns number of lines
int parse_first(label_t *labels, instruction_t *instructions, const char *arg) {
	
	FILE *file;
	file = fopen(arg,"r");
	char line[MAX_LINE_LENGTH]; 
	int lineNumber = 0; 

	if(file) {
		while (fgets(line, sizeof(line), file)) {
			lineNumber++; 
			if (strchr(line, ':') != NULL) {
				*labels = (label_t) { .label = strtok(line, ":"), .address = lineNumber};
				labels++; 
			} else {
				char *mnemonic = strtok(line, " "); 
				char *operand_fields[4]; 
				for(int i = 0; i < 4; operand_fields[i] = strtok(line, ","), i++);
				*instructions = (instruction_t) {.mnemonic = mnemonic,.operand_fields = operand_fields};
				instructions++; 
			}
		}
		fclose(file);
	}

	return lineNumber;
}
*/

void parse_first (instruction_t *instructions, char *arg) {
	FILE *file;
	file = fopen(arg,"r");
	char line[MAX_LINE_LENGTH]; 

	if(file) {
		while (fgets(line, sizeof(line), file)) {
			char *mnemonic = strtok(line, " ,"); 
			char *operand_fields[4]; 

			char *token = mnemonic;
			token = strtok(NULL, " ,");

			for(int i = 0; i < 4; i++) {
				operand_fields[i] = token;
				// printf(operand_fields[i]), 
				token = strtok(NULL, " ,");
			}
			*instructions = (instruction_t) {.mnemonic = mnemonic,.operand_fields = operand_fields};
			instructions++; 
		}
		fclose(file);
	}

}

// void parse_second(label_t *labels, char **instructions);

void print_instruction (instruction_t instruction){
	printf("%s : ", instruction.mnemonic);

	for (int i = 0; i < 4; i++)
		printf("%s ", instruction.operand_fields[i]);
	printf("\n");


}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);

	if (argc != 3) {
		perror("invalid number of arguments");
		return EXIT_FAILURE;
	}

	char *assembly = argv[1];
	// char *output = argv[2];

	instruction_t *instructions = calloc(65536, sizeof(instruction_t));
	
	parse_first (instructions, assembly);

	instruction_t *head = instructions;

	printf("instructions\n");

	for (; instructions->mnemonic != NULL; instructions++) {
		print_instruction(*instructions);
	}
	
	free(head);
	

	return EXIT_SUCCESS;
}
