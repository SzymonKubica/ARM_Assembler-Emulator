#include <stdio.h>

#define and 0b0000
#define eor 0b0001
#define sub 0b0010
#define rsb 0b0011
#define add 0b0100
#define tst 0b1000
#define teq 0b1001
#define cmp 0b1100
#define mov 0b1101

unsigned char immediate_operand (unsigned char firstByte) {
    return firstByte & 1;
}

unsigned char get_OpCode (unsigned char firstByte, unsigned char secondByte) {
    return (firstByte & 1) + secondByte >> 4;
}

unsigned char get_Rn (unsigned char secondByte) {
    return secondByte & 0b1111;
}

unsigned char get_Rd (unsigned char thirdByte) {
    return thirdByte >> 4;
}

// short: 2 bytes
unsigned short get_Operand2 (unsigned char thirdByte, unsigned char fourthByte) {
    return ((thirdByte & 0b1111) << 8) | fourthByte;
}

int main (void) {
    unsigned char tb = 0b10001000, fob = 0b10000000;
    printf ("%d \n", get_Rd(tb));
    printf ("%d \n", get_Operand2(tb, fob));

    return 0;
}



