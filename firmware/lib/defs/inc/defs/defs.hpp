#ifndef LIB_DEFS_DEFS_HPP
#define LIB_DEFS_DEFS_HPP

#include <cstdint>

namespace defs::i2c {

constexpr uint8_t inst = 1;
constexpr uint8_t scl_pin = 3;
constexpr uint8_t sda_pin = 2;
constexpr uint32_t baudrate = 1'000'000;
constexpr uint8_t slave_address = 0x55;

}

#endif  // LIB_DEFS_DEFS_HPP
