#include "ssd1306/ssd1306.h"
#include "ssd1306/font.hpp"

#include <cstring>

void ssd1306::write_command(uint8_t cmd)
{
    uint8_t command_bytes[2] = {0x80, cmd};
    i2c_driver.write_data(command_bytes, sizeof(command_bytes));
}

void ssd1306::init()
{
    write_command(0xAE);  // Set Display OFF
    write_command(0x20);  // Set Memory Addressing Mode
    write_command(0x00);  // horizontal
    write_command(0x40);  // Set Display Start Line
    write_command(0xA1);  // Set Segment Re-map
    write_command(0xA8);  // Set Multiplex Ratio
    write_command(0x3F);  // 31 multiplex
    write_command(0xC8);  // Set COM Output Scan Direction
    write_command(0xD3);  // Set Display Offset
    write_command(0x00);  // offset 0
    write_command(0xDA);  // Set COM Pins Hardware Configuration
    write_command(0x02 | 0x1 << 4 | 0x0 << 5);  // default com pins
    write_command(0xD5);  // Set Display Clock Divide Ratio/Oscillator Frequency
    write_command(0x80);  // default frreq
    write_command(0xD9);  // Set Pre-charge Period
    write_command(0xF1);  // period
    write_command(0xDB);  // Set V COMH Deselect Level
    write_command(0x30);  // 0.83 x VCC
    write_command(0x81);  // Set Contrast Control
    write_command(0xFF);  // max contrast
    write_command(0xA4);  // Entire display ON - displays RAM contents
    write_command(0x8D);  // Enable charge pump regulator
    write_command(0x14);  // ^
    write_command(0xA6);  // Set normal mode (not inversed)

    sleep_ms(100);
    fill(0);
    display();

    write_command(0xAF);  // Set Display ON
}

void ssd1306::set_cursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;
}

void ssd1306::set_pixel(uint8_t x, uint8_t y, bool val)
{
    uint8_t page = y / 8;
    uint8_t y_in_page = y % 8;

    if (val) {
        displayBuffer[page][x] |= (1 << y_in_page);
    } else {
        displayBuffer[page][x] &= ~(1 << y_in_page);
    }
}

void ssd1306::display()
{
    write_command(0x21);
    write_command(0x00);
    write_command(0x7F);
    write_command(0x22);
    write_command(0x00);
    write_command(0x07);

    constexpr uint32_t data_len = oledWidth * oledPages;
    uint8_t data_bytes[data_len + 1];

    data_bytes[0] = 0x40;
    memcpy(&(data_bytes[1]), displayBuffer, data_len);

    i2c_driver.write_data(data_bytes, sizeof(data_bytes));
}

void ssd1306::fill(bool val)
{
    for (size_t i = 0; i < oledWidth; i++)
    {
        for (size_t page = 0; page < oledPages; page++)
        {
            displayBuffer[page][i] = val ? 0xFF : 0x00;
        }
    }
}


void ssd1306::print_string(const char *str, uint8_t font_size)
{
    constexpr uint limit = 11;  // TODO: not updated for templated fonts
    for (uint i = 0; i < limit && str[i] != '\0'; i++)
    {
        if (font_size == 8) {
            print_char(font_8x5, str[i]);
            cursor_x += font_8x5.width + 1;
        }
        else if (font_size == 16) {
            print_char(font_16x10, str[i]);
            cursor_x += font_16x10.width + 2;
        }
        else if (font_size == 32) {
            print_char(font_32x20, str[i]);
            cursor_x += font_32x20.width + 4;
        }
    }
}
