#include <stdbool.h>
#include <stdio.h>
#include "binaryString.h"
#include "cond.h"
#include "../../defns.h"

#define eq 0
#define ne 1
#define ge 10 //0b1010
#define lt 11 //0b1011
#define gt 12 //0b1100
#define le 13 //0b1101
#define al 14 //0b1110

byte_t getCond (byte_t c) {
	return c >> 4;
}

byte_t get_NZCV (word_t CPSR) {
	return CPSR >> 28;
}

byte_t z_set (byte_t NZCV) {
	return NZCV & (1 << 2);
}

byte_t n_equal_v (byte_t NZCV) {
	// printf("%x\n", NZCV);
	return (NZCV & 1) == ((NZCV >> 3) & 1) ;
}

byte_t checkCond (byte_t byte, word_t CPSR) {
	
	byte_t NZCV = get_NZCV(CPSR);

	switch (getCond(byte)) 	{
		case al:
			return 1;
		case eq:
			return z_set(NZCV); 
		case ne:
			return !(z_set(NZCV));
		case ge: 
			return n_equal_v(NZCV);
		case lt:
			return !(n_equal_v(NZCV));
		case gt:
			return !(z_set(NZCV)) && n_equal_v(NZCV); 
		case le:
			return z_set(NZCV) || !n_equal_v(NZCV);
		default:
			return 0;
	}

}

// debugging
/*
int main (void) {

	unsigned long int CPSR = readBinary("0000") << 28;

	printf("%ld\n", CPSR);

	if (checkCond(0, CPSR)) {
		printf ("eq execute\n");
	}
	
	if (checkCond(1, CPSR)) {
		printf ("ne execute\n");
	}

	if (checkCond(ge, CPSR)) {
		printf ("ge execute\n");
	}

	
	if (checkCond(lt, CPSR)) {
		printf ("lt execute\n");
	}

	
	if (checkCond(gt, CPSR)) {
		printf ("gt execute\n");
	}

	
	if (checkCond(le, CPSR)) {
		printf ("le execute\n");
	}

	if (checkCond(al, CPSR)) {
		printf ("al execute\n");
	}

	// printf(CPSR);
	// printf(CPSR >> 1);
	// printf("%ld\n", CPSR);

	return 0;
}
*/

