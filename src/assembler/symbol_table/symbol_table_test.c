#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "symbol_table.h"

void testcond(bool condition, char *test_name) {
	printf( "T %s: %s\n", test_name, (condition ? "OK" : "FAIL"));
}

int main(void) {
	symbol_table_t *test_table = malloc(sizeof(symbol_table_t));

	symbol_table_init(test_table);

	add_entry(test_table, "label1", 1);
	add_entry(test_table, "label2", 2);
	add_entry(test_table, "label3", 3);
	add_entry(test_table, "label4", 4);
	add_entry(test_table, "label5", 5);

	int address1 = 0;
	int address2 = 0;
	int address3 = 0;
	int address4 = 0;
	int address5 = 0;

	get_address(test_table, "label1", &address1);
	get_address(test_table, "label2", &address2);
	get_address(test_table, "label3", &address3);
	get_address(test_table, "label4", &address4);
	get_address(test_table, "label5", &address5);

	testcond(address1 == 1, " get address 1");
	testcond(address2 == 2, " get address 2");
	testcond(address3 == 3, " get address 3");
	testcond(address4 == 4, " get address 4");
	testcond(address5 == 5, " get address 5");

	table_destroy(test_table);
}
