#include "pico/stdlib.h"
#include "bsp/board_api.h"
#include "tusb.h"

int main() {
    gpio_init(2);
    gpio_init(3);
    gpio_set_dir(2, GPIO_OUT);
    gpio_set_dir(3, GPIO_OUT);

    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
    };
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    while (true) {
        tud_task();
    }
}
