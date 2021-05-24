#include "cond.h"
#include <stdbool.h>
#include <stdio.h>

#define eq 0
#define ne 1
#define ge 0b1010
#define lt 0b1011
#define gt 0b1100
#define le 0b1101
#define al 0b1110

unsigned char getCond (unsigned char c) {
	return c >> 4;
}

unsigned char get_NZCV (unsigned long int CPSR) {
	return CPSR >> 28;
}

unsigned char z_set (unsigned char NZCV) {
	return NZCV & (1 << 2);
}

unsigned char n_equal_v (unsigned char NZCV) {
	// printf("%x\n", NZCV);
	return (NZCV & 1) == ((NZCV >> 3) & 1) ;
}
unsigned char checkCond (unsigned char c, unsigned long int CPSR) {
	unsigned char NZCV = get_NZCV(CPSR);

	switch (c) 	{
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

int main (void) {

	unsigned long int CPSR = 0b0000 << 28;

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

