#include "menu_b_operacao.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader


void operacao_inicial()
{
    int tecla = read_keypad();
}
void executa_leds(int *linha_comando_led);
void executa_buzzer(int *linha_comando_buzz);
void interrupcaoBotao(uint gpio, uint32_t events);