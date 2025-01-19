#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader

// Intervalos de tempo para alternar a frequência dos leds piscando (em milissegundos)
int intervals[] = {10, 1000, 750, 500, 250};
const int num_intervals = sizeof(intervals) / sizeof(intervals[0]);

void blink_led(uint8_t pin, uint32_t duration) {
    gpio_put(pin, 1);         // Liga o LED
    sleep_ms(duration);       // Aguarda pelo tempo especificado
    gpio_put(pin, 0);         // Desliga o LED
    sleep_ms(duration);       // Tempo para desligado
}

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