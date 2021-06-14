#include "../../defns.h"
#include <stdbool.h>

/*
 * Test Utilities Module.
 */

void testcond(bool condition, char *test_name);

void print_binary_little_Endian(word_t word);

void print_binary_big_Endian(word_t word);

word_t get_word(byte_t buffer[4]);

void log_output(word_t output);
