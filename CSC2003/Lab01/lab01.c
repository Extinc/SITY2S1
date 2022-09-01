#include <stdio.h>
#include "pico/stdlib.h"

// This lab to is to learn how to use gpio_put and let onboard led blinks.
int main() {

    // LED - GP25
    const uint led_pin = 25;

    // Initialize LED pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    // Initialize chosen serial port
    stdio_init_all();

    // Loop forever
    while (true) {

        // Blink Effect

        // Set GP25 to true
        gpio_put(led_pin, true);
        sleep_ms(500);

        // Set GP25 to false
        gpio_put(led_pin, false);
        sleep_ms(500);
    }
}
    