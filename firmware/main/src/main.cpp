#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();

    i2c_driver main_i2c(defs::i2c::inst, defs::i2c::sda_pin, defs::i2c::scl_pin, defs::i2c::slave_address, defs::i2c_baudrate);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
