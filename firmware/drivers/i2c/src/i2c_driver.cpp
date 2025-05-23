#include "i2c/i2c_driver.h"

namespace drivers::i2c {

i2c_driver::i2c_driver(uint8_t i2c_inst, uint8_t sda_pin, uint8_t scl_pin, uint8_t address, uint32_t speed)
    : i2c_inst_(i2c_inst == 0 ? i2c0 : i2c1)
    , sda_pin_(sda_pin)
    , scl_pin_(scl_pin)
    , address_(address)
    , speed_(speed)
{
}

uint32_t i2c_driver::init()
{
    gpio_set_function(sda_pin_, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin_, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin_);
    gpio_pull_up(scl_pin_);
    return i2c_init(i2c_inst_, speed_);
}

uint32_t i2c_driver::read_reg(uint32_t address)
{
    uint32_t value = 0;
    i2c_write_blocking(i2c_inst_, address_, reinterpret_cast<uint8_t*>(&address), 4, true);
    i2c_read_blocking(i2c_inst_, address_, reinterpret_cast<uint8_t*>(&value), 4, false);
    return value;
}

}  // namespace drivers::i2c
