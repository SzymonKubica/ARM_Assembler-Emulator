#include <stdlib.h>
#include <stdio.h>
#include <string.h> 

#define MAX_LINE_LENGTH 512 

typedef struct {
	char *label;
	int  address; 
} label_t;

typedef struct {
	char *mnemonic;
	char **operand_fields; 
} instruction_t;

void parse_first(label_t *labels, instruction_t *instructions, const char *arg) {
	
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
}

void parse_second(label_t *labels, char **instrcutions);

int main(int argc, char **argv) {
	return EXIT_SUCCESS;
}
