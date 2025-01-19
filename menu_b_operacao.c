#include "menu_b_operacao.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader


void operacao_inicial()
{
    while(true)
    {
    int tecla = read_keypad();
    int controle=0;//var para verificar se foi criado algum mini programa antes de 'D'
    if(tecla==4||tecla ==8)
    {
        //se tecla for a ou b
    }else{
        if(tecla ==15)
        {//se for sustenido # retornar ao menu de deividson
            return;
        }
        if(tecla ==16)
        {
            //tecla 'D' para iniciar
            //todo: por verificação se o programa  foi adicionado ou não
        }
        if(tecla ==13)
        {
            //se pressionar '*' zerar a contagem do programa e reiniciar iteração
            operacao_inicial();
            //todo: fazer melhor 
        }
    }
    }
}
void executa_leds(int *linha_comando_led);
void executa_buzzer(int *linha_comando_buzz);
void interrupcaoBotao(uint gpio, uint32_t events);