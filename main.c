#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

int main() {
    const uint onboardLED = 25;

    //Initialise the onboard LED pin
    gpio_init(onboardLED);
    gpio_set_dir(onboardLED, GPIO_OUT);

    while (1) {
        gpio_put(onboardLED, true);
        sleep_ms(250);
        gpio_put(onboardLED, false);
        sleep_ms(250);
        gpio_put(onboardLED, true);
        sleep_ms(250);
        gpio_put(onboardLED, false);
        sleep_ms(250);
    }
    return 0;
}   