#include "gpio.h"

bool is_GPIO_address(word_t Rn) {
	return (Rn == GPIO_00_09) || (Rn == GPIO_10_19) || (Rn == GPIO_20_29);
}

void print_GPIO_access_message(word_t Rn) {
	switch (Rn) {
		case GPIO_00_09:
			printf("One GPIO pin from 0 to 9 has been accessed\n");
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
			return output;
		default:
			// Shold never be reached.
			return -1;
	}
}


static void write_word_to_memory_at(word_t address, word_t word, byte_t *memory) {
	for (int i = 0; i < 4; i++) {
		memory[address + i] = word;
		word >>= 8;
	}
}

static word_t read_word_from_memory_at(word_t address, byte_t *memory) {
		word_t loadWord;
	for (int i = 3; i >= 0; i--) {
		loadWord = loadWord << 8;
		loadWord |= memory[address + i];
	}
	return loadWord;
}

void initialise_GPIO_pins(byte_t *memory) {

	/* As outlined in the spec, each GPIO memory address
	 * should return the valuse of the address. Therefore, we
	 * need to initialise these addresses.
	 */

	 write_word_to_memory_at(GPIO_20_29_shifted, GPIO_20_29, memory);
	 write_word_to_memory_at(GPIO_10_19_shifted, GPIO_10_19, memory);
	 write_word_to_memory_at(GPIO_00_09_shifted, GPIO_00_09, memory);
}
enum pin_function get_pin_functionality(int pin_number, byte_t *memory) {

	nibble_t pin_code;
	int pin_offset = 3 * (pin_number % 10);
	word_t mask = readBinaryWord("111") << pin_offset;
	word_t pin_range;

	if (0 <= pin_number && pin_number<= 9) {

		pin_range = read_word_from_memory_at(GPIO_00_09_shifted, memory);

	} else if (10 <= pin_number && pin_number <= 19) {

		pin_range = read_word_from_memory_at(GPIO_10_19_shifted, memory);

	} else if (20 <= pin_number && pin_number <= 29) {

		pin_range = read_word_from_memory_at(GPIO_20_29_shifted, memory);

	}
		pin_code = (pin_range &  mask) >> pin_offset;

	return from_binary_to_pin_function(pin_code);
}

void set_pin_functionality(word_t location, word_t value, byte_t *memory) {
  word_t past_value = read_word_from_memory_at(location, memory);
	write_word_to_memory_at(location, (past_value | value), memory);
}

void clear_pin(word_t shifted_pin, byte_t *memory) {
	// TODO: fix the assertions.
	//assert(get_pin_functionality(pin_number, memory) == output);
	
	// Setting a bit in clear area corresponding to the pin number clears the pin.
	write_word_to_memory_at(GPIO_clearing_shifted, shifted_pin, memory);

	printf("PIN OFF\n");
}

void set_pin(word_t shifted_pin, byte_t *memory) {
	//assert(get_pin_functionality(pin_number, memory) == output);
	
	// Setting a bit in set area corresponding to the pin number sets the pin.
	write_word_to_memory_at(GPIO_setting_shifted, shifted_pin, memory);

	printf("PIN ON\n");
}




