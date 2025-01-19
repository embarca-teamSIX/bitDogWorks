
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader


void somErro();
void somConfirmacao();
int retorna_buzz_valido();
void preenche_buzz(int *array_to_fill);
int retorna_led_valido();
void preenche_led(int *array_to_fill);
void operacao_inicial();
void executa_buzzer(int *linha_comando_buzz);
void executa_led(int *linha_comando_led);
void interrupcaoBotao(uint gpio, uint32_t events);