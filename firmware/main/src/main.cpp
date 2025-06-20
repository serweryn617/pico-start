#include <stdio.h>
#include "pico/stdlib.h"

#include "i2c/i2c_driver.h"
#include "uart/uart_driver.h"
#include "defs/defs.hpp"

#include "ssd1306/ssd1306.h"

using namespace drivers::i2c;
using namespace drivers::uart;

int main() {
    stdio_init_all();

    i2c_driver main_i2c(defs::i2c::inst, defs::i2c::sda, defs::i2c::scl, defs::i2c::slave_address, defs::i2c::baudrate);
    uart_driver main_uart(defs::uart::inst, defs::uart::rx, defs::uart::tx, defs::uart::baudrate);

    ssd1306 main_oled(main_i2c);

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
