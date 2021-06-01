#include <stdbool.h>
#include <stdio.h>

#include "binaryString.h"
#include "../../defns.h"

#define GPIO_20_29 0x20200008
#define GPIO_10_19 0x20200004
#define GPIO_00_09 0x20200000

#define GPIO_clearing 0x20200028
#define GPIO_setting 0x20200028

bool is_GPIO_address(word_t Rn);

void print_GPIO_access_message(word_t Rn);

enum pin_function {input, output};

enum pin_function from_binary_to_pin_function(nibble_t code);

void initialise_GPIO_pins(word_t *memory);

enum pin_function get_pin_functionality(int pin_number, word_t *memory);
