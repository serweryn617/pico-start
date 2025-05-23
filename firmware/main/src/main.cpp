#include "bsp/board_api.h"
#include "tusb.h"

int main() {
    tusb_rhport_init_t dev_init = {
        .role = TUSB_ROLE_DEVICE,
        .speed = TUSB_SPEED_AUTO
    };
    tusb_init(BOARD_TUD_RHPORT, &dev_init);

    while (true) {
        tud_task();
    }
}
