#include <stdio.h>
#include <stdbool.h>

#include "../../defns.h"
#include "common.h"

void testcond(bool condition, char *testname) {
	printf("T %s: %s\n", testname, (condition ? "OK" : "FAIL"));
}

void test1() {
	// Test 1: testing readBinary.
	byte_t byte = readBinary("1111");
	testcond (byte == 15, "readBinary");
}

void test2() {
	// Test 2: testing readBinary with spaces.
	byte_t byte = readBinary("1001 0000");
	testcond (byte == 144, "readBinary with spaces");
}

void test3() {
	// Test3: testing readBinaryWord.
	word_t word1 = readBinaryWord("100000000000");
	testcond (word1 == 2048, "readBinaryWord");
}

void test4() {
	// Test4: testing readBinaryWord with spaces.
	word_t word1 = readBinaryWord("1000 0000 0000");
	testcond (word1 == 2048, "readBinaryWord with spaces");
}

int main (void) {

	test1();
	test2();
	test3();
	test4();

	return 0;
}

