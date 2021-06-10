#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <assert.h>
#include "assembler_defs.h"

#define MAX_LINE_LENGTH 512 
#define MAX_NUM_INSTRUCTIONS (65536 / 4)

typedef struct {
	char *label;
	int  address; 
} label_t;

void parse_first (label_t **labels_p, instruction_t **instructions_p, char *arg) {
	FILE *file;
	file = fopen(arg,"r");
	char line[MAX_LINE_LENGTH]; 
	int address = 0;
	instruction_t **instructions = instructions_p;
	label_t **labels = labels_p;

	if(file) {
		while (fgets(line, sizeof(line), file)) {
			if (strchr(line, ':') != NULL) {
				// *labels = (label_t) { .label = strtok(line, ":"), .address = address};
				 labels++; 
			} else {
				char *mnemonic = strtok(line, " ,\n");
				char **operand_fields = (char**) calloc (4, sizeof(char *));
				
				char *token = mnemonic;
				token = strtok(NULL, " ,\n");

				for(int i = 0; token != NULL; i++) {
					char *string = malloc (sizeof (char) *MAX_LINE_LENGTH);
					strcpy(string, token);

					operand_fields[i] = string;
					
					token = strtok(NULL, " ,\n");
				}

				instruction_t *inst = malloc(sizeof(instruction_t *));

				char *string = malloc(sizeof(char) *MAX_LINE_LENGTH);
				strcpy (string, mnemonic);

				inst->mnemonic = string;
				inst->operand_fields = operand_fields; 
				// (instruction_t) {.mnemonic = mnemonic,.operand_fields = operand_fields}
				*instructions = inst;
				// printf("%s",(*instructions_p)->mnemonic);
				instructions++;
			}
			address+= 4;
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

void free_instructions(instruction_t **instructions) {	
	for (; instructions != NULL && (*instructions != NULL); instructions++ ) {
		
		free((*instructions)->mnemonic);
		for (int i = 0; i < 4; i++)
			free((*instructions)->operand_fields [i]);
		
		free((*instructions)->operand_fields);
		free(*instructions);
	}

}

int main(int argc, char **argv) {
	setbuf(stdout, NULL);
	if (argc != 3) {
		perror("invalid number of arguments");
		return EXIT_FAILURE;
	}

	char *assembly = argv[1];

	instruction_t **instructions = calloc(MAX_NUM_INSTRUCTIONS, sizeof(instruction_t *));
	assert(instructions != NULL);
	label_t **labels = calloc(MAX_NUM_INSTRUCTIONS, sizeof(label_t *));
	assert(labels != NULL);
	
	parse_first (labels, instructions, assembly);

	printf("instructions\n");

	instruction_t **head = instructions;
	for (; (*head) != NULL && (head) != NULL; (head)++) {
		print_instruction(**head);
	}

	free_instructions(instructions);
	free(instructions);
	free(labels);

	return EXIT_SUCCESS;
}
