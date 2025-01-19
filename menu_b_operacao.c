#include "menu_b_operacao.h"
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Biblioteca para acessar o modo bootloader
#define MAX_LEDUZZING 100
const int ref ={1, 2, 3, 5, 6, 7, 9, 10, 11};
void somErro() {
    playNote(520, 100);  
    sleep_ms(100);       
    playNote(520, 100);  
    sleep_ms(100);
    playNote(440, 200);  
    sleep_ms(200);
}
void somConfirmacao() {
    playNote(440, 100);  // Lá (440 Hz) por 100 ms
    sleep_ms(50);        // Pausa curta de 50 ms
    playNote(520, 100);  // Dó# (520 Hz) por 100 ms
    sleep_ms(50);        // Pausa curta de 50 ms
    playNote(660, 150);  // Mi (660 Hz) por 150 ms
}
int retorna_buzz_valido()//auto explicativo
{
//todo: laço para verificar sé é valido    
    while(true)
    {
        int tecla = read_keypad();
        switch (tecla)
        {
            case 1:
          playNote(261, 200);
          return tecla;
          break;
            case 2:
         playNote(293, 200);  // Ré (293 Hz)
         return tecla;
        break;
            case 3: 
        playNote(329, 200);  // Mi (329 Hz)
        return tecla;
        break;
            case 5:
         playNote(349, 200);  // Fá (349 Hz)
         return tecla;
        break;
            case 6:
         playNote(392, 200);  // Sol (392 Hz)
         return tecla;
        break;
            case 7:
        playNote(440, 200);  // Lá (440 Hz)
        return tecla;
        break;
            case 9:
        playNote(493, 200);  // Si (493 Hz)
        return tecla;
        break;
            case 10:
        playNote(523, 200);  // Dó (oitava acima, 523 Hz)
        return tecla;
        break;
            case 11:
        playNote(587, 200);  // Ré (oitava acima, 587 Hz)
        return tecla;
        break;
            case 12:
        return tecla;
        break;
            default:
        somErro();
            break;
        }
    }
}
void preenche_buzz(int *array_to_fill)
{
    //ler até no maximo 100 posições de 1 a 9 tons
        int controle=0;
        do{
        int tecla_lida = retorna_buzz_valido();
        if(tecla_lida ==12){somConfirmacao();return;}
        array_to_fill[controle]=tecla_lida;
        controle++;
        }while (controle<100);
        somConfirmacao();
        return;
        
}
int retorna_led_valido()//auto explicativo
{
//todo: laço para verificar sé é valido    
    while(true)
    {
        int tecla = read_keypad();
        switch (tecla)
        {
            case 1://led 13
            gpio_put(13, 1);
          sleep_ms(100);
          gpio_put(13, 0);
          return tecla;
          break;
            case 2://led 11
           gpio_put(11, 1);
          sleep_ms(100);
          gpio_put(11, 0);
         return tecla;
        break;
            case 3: //lled 12
          gpio_put(12, 1);
          sleep_ms(100);
          gpio_put(12, 0);
        return tecla;
        break;
            case 12:
        return tecla;
        break;
            default:
        somErro();
            break;
        }
    }
}
void preenche_led(int *array_to_fill)
{
     int controle=0;
        do{
        int tecla_lida = retorna_led_valido();
        if(tecla_lida ==12){somConfirmacao();return;}
        array_to_fill[controle]=tecla_lida;
        controle++;
        }while (controle<100);
        somConfirmacao();
        return;
}
void operacao_inicial()
{
    int controle=0;//var para verificar se foi criado algum mini programa antes de 'D'
    int linha_comando_buzz[MAX_LEDUZZING];
    int linha_comando_led[MAX_LEDUZZING];
    while(true)
    {
    int tecla = read_keypad();
    if(tecla==4||tecla ==8)
    {
        //se tecla for a ou b
      
        if(tecla ==4){preenche_buzz(linha_comando_buzz);controle++;}
         if(tecla ==8){preenche_led(linha_comando_led);controle++;}
        //criar func para preencher led
        //cria func para preencher buzz
    }else{
        if(tecla ==15)
        {//se for sustenido # retornar ao menu de deividson
            return;
        }
        if(tecla ==16)
        {
            //tecla 'D' para iniciar
            //todo: por verificação se o programa  foi adicionado ou não
            if(controle!=0)
            {
                executa_buzzer(linha_comando_buzz);
                executa_leds(linha_comando_led);
                operacao_inicial();
            }
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
void executa_buzzer(int *linha_comando_buz)
{
    int i=0;
    do
    {
        
        switch (linha_comando_led[i])
        {
            case 1:
          playNote(261, 200);
          break;
            case 2:
         playNote(293, 200);  // Ré (293 Hz)
        break;
            case 3: 
        playNote(329, 200);  // Mi (329 Hz)
        break;
            case 5:
         playNote(349, 200);  // Fá (349 Hz)
        break;
            case 6:
         playNote(392, 200);  // Sol (392 Hz)
        break;
            case 7:
        playNote(440, 200);  // Lá (440 Hz)

        break;
            case 9:
        playNote(493, 200);  // Si (493 Hz)
        break;
            case 10:
        playNote(523, 200);  // Dó (oitava acima, 523 Hz)
        break;
            case 11:
        playNote(587, 200);  // Ré (oitava acima, 587 Hz)
        break;
        }
        i++;
    }while(i<MAX_LEDUZZING);
}
void executa_led(int *linha_comando_led)
{
int i=0;
    do{
        switch (linha_comando_led[i])
        {
            case 1://led 13
            gpio_put(13, 1);
          sleep_ms(1000);
          gpio_put(13, 0);
          break;
            case 2://led 11
           gpio_put(11, 1);
          sleep_ms(1000);
          gpio_put(11, 0);
        break;
            case 3: //lled 12
          gpio_put(12, 1);
          sleep_ms(1000);
          gpio_put(12, 0);
        break;
        }
    }while(i<MAX_LEDUZZING);
}
void interrupcaoBotao(uint gpio, uint32_t events);