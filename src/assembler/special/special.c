#include <stdio.h>

#include "../../assembler_defs.h"
#include "special.h"

void assemble_andeq(FILE *file) {
	write_to_file(file, 0x0, 0x0, 0x0, 0x0);
}

void assembler_lsl(instruction_t instruction, FILE *file) {
}
