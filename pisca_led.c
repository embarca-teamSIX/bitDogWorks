#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader

// Intervalos de tempo para alternar a frequência dos leds piscando (em milissegundos)
int intervals[] = {10, 1000, 750, 500, 250};
const int num_intervals = sizeof(intervals) / sizeof(intervals[0]);

void run_pisca_led_diferentes_frequencias(uint8_t LED_R_PIN, uint8_t LED_G_PIN, uint8_t LED_B_PIN)
{
    // Para cada frequência definida
    for (int i = 0; i < num_intervals; i++) {
        // Pisca os LEDs na sequência
        blink_led(LED_R_PIN, intervals[i]);
        blink_led(LED_B_PIN, intervals[i]);
        blink_led(LED_G_PIN, intervals[i]);
    }
}