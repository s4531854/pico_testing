#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#define ONBOARD_LED 25
//Generalising code
#define FLASHES_PER_SEC 2 
#define SLEEP_TIME 1000/(FLASHES_PER_SEC*2)

int main() {
    //Initialise the onboard LED pin
    gpio_init(ONBOARD_LED);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);

    while (1) {
        gpio_put(ONBOARD_LED, true);
        sleep_ms(SLEEP_TIME);
        gpio_put(ONBOARD_LED, false);
        sleep_ms(SLEEP_TIME);
    }
    return 0;
}   