#include <stdbool.h>

#include "../../defns.h"

#define GPIO_20_29_shifted 0x8 //0x20200008
#define GPIO_10_19_shifted 0x4 //0x20200004
#define GPIO_00_09_shifted 0x0 //0x20200000

#define GPIO_clearing_shifted 0x28 //0x20200028
#define GPIO_setting_shifted 0x1c //0x2020001c

#define GPIO_20_29 0x20200008
#define GPIO_10_19 0x20200004
#define GPIO_00_09 0x20200000

#define GPIO_clearing 0x20200028
#define GPIO_setting 0x2020001c

bool is_GPIO_address(word_t Rn);

void print_GPIO_access_message(word_t Rn);

enum pin_function {input, output};

void initialise_GPIO_pins(byte_t *memory);

void set_pin_function(word_t location, word_t value, byte_t *memory);

void clear_pin(word_t shifted_pin, byte_t *memory);
void set_pin(word_t shifted_pin, byte_t *memory);
