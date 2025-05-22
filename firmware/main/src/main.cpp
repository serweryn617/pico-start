// #include "defs/defs.hpp"
// #include "i2c/i2c_driver.h"


// using namespace drivers::i2c;

// int main()
// {
//     // TinyUSB t_usb(global_tinyusb_callback);
//     i2c_driver main_i2c(defs::i2c::inst, defs::i2c::sda_pin, defs::i2c::scl_pin, defs::i2c::slave_address, defs::i2c_baudrate);

// }



#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
