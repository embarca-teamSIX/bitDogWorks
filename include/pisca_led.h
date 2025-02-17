#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader

void blink_led(uint8_t pin, uint32_t duration);
void piscar_todos_os_leds_finalizando(uint8_t LED_R_PIN, uint8_t LED_G_PIN, uint8_t LED_B_PIN);
void run_pisca_led_diferentes_frequencias(uint8_t LED_R_PIN, uint8_t LED_G_PIN, uint8_t LED_B_PIN);