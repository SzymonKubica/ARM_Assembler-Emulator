#include <stdio.h>
#include <stdbool.h>

#include "../../defns.h"
#include "common.h"

void testcond(bool condition, char *testname) {
	printf("T %s: %s\n", testname, (condition ? "OK" : "FAIL"));
}

void test1() {
	// Test 1: testing parse_binary.
	byte_t byte = parse_binary("1111");
	testcond (byte == 15, "parse_binary");
}

void test2() {
	// Test 2: testing parse_binary with spaces.
	byte_t byte = parse_binary("1001 0000");
	testcond (byte == 144, "parse_binary with spaces");
}

void test3() {
	// Test3: testing parse_binary_word.
	word_t word1 = parse_binary_word("100000000000");
	testcond (word1 == 2048, "parse_binary_word");
}

void test4() {
	// Test4: testing parse_binary_word with spaces.
	word_t word1 = parse_binary_word("1000 0000 0000");
	testcond (word1 == 2048, "parse_binary_word with spaces");
}

int main (void) {

	test1();
	test2();
	test3();
	test4();

	return 0;
}

