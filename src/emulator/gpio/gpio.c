#include "gpio.h"

bool is_GPIO_address(word_t Rn) {
	return (Rn == GPIO_00_09) || (Rn == GPIO_10_19) || (Rn == GPIO_20_29);
}

void print_GPIO_access_message(word_t Rn) {
	switch (Rn) {
		case GPIO_00_09:
			printf("One GPIO pin from 00 to 09 has been accessed\n");
			break;
		case GPIO_10_19:
			printf("One GPIO pin from 10 to 19 has been accessed\n");
			break;
		case GPIO_20_29:
			printf("One GPIO pin from 20 to 29 has been accessed\n");
			break;
  }
}

enum pin_function from_binary_to_pin_function(nibble_t code) {
	switch(code) {
		case 0: 
			return input;
		case 1: 
			return input;
		default:
			// Shold never be reached.
			return -1;
	}
}

void initialise_GPIO_pins(word_t *memory) {

	/* As outlined in the spec, each GPIO memory address
	 * should return the valuse of the address. Therefore, we
	 * need to initialise these addresses.
	 */

	 memory[GPIO_20_29] = GPIO_20_29;
	 memory[GPIO_10_19] = GPIO_10_19;
	 memory[GPIO_00_09] = GPIO_00_09;
}

enum pin_function get_pin_functionality(int pin_number, word_t *memory) {

	nibble_t pin_code;
	int pin_offset = 3 * (pin_number % 10);
	word_t mask = readBinaryWord("111") << pin_offset;

	if (0 <= pin_number && pin_number<= 9) {

		pin_code = (memory[GPIO_00_09] & mask) >> pin_offset;

	} else if (10 <= pin_number && pin_number <= 19) {

		pin_code = (memory[GPIO_10_19] & mask) >> pin_offset;

	} else if (20 <= pin_number && pin_number <= 29) {

		pin_code = (memory[GPIO_20_29] & mask) >> pin_offset;

	}

	return from_binary_to_pin_function(pin_code);
}




