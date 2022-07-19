#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define ONBOARD_LED_PIN 25
#define MAX_BRIGHTNESS 255
#define MIN_BRIGHTNESS 0

/* ISR for PWM wrapping */
void wrap_isr() {
    static int brightness = MIN_BRIGHTNESS;  //Use counter to track brightness level
    static bool inc = true;     //Track increasing (inc) or descreasing brightness 

    //Clear interrupt flag
    pwm_clear_irq(pwm_gpio_to_slice_num(ONBOARD_LED_PIN)); 

    if (inc) {
        brightness++;
        
        if (brightness > MAX_BRIGHTNESS) {
            brightness = MAX_BRIGHTNESS;    
            inc = false;    //Set to decrease in brightness
        }
    } else {
        brightness--;

        if (brightness < MIN_BRIGHTNESS) {
            brightness = MIN_BRIGHTNESS; 
            inc = true; //Set to increase in brightness
        }
    }

    //NOTE: By default, counter wraps over max range of 0 -> 65535  
    //By squaring the brightness value, it achieves a similar range of 0 -> 65025
    pwm_set_gpio_level(ONBOARD_LED_PIN, brightness * brightness);
}


int main () {
    //Enable PWM for onboard LED Pin
    gpio_set_function(ONBOARD_LED_PIN, GPIO_FUNC_PWM);

    //Get the PWM slice for the onboard LED Pin
    uint slice = pwm_gpio_to_slice_num(ONBOARD_LED_PIN);

    pwm_clear_irq(slice);   //Clear our PWM channel for interrupt
    pwm_set_irq_enabled(slice, true);   //Enable single PWM interrupt 
    irq_set_exclusive_handler(PWM_IRQ_WRAP, wrap_isr); //Sets the interrupt handler 
    irq_set_enabled(PWM_IRQ_WRAP, true);    //Enable interrupt 

    //Use default slice configuration, set divider, initialise & run pwm 
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice, &config, true);

    while (1) {
        //Do nothing
    }
}
