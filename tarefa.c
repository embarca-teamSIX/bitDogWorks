#include "pico/stdlib.h"              // Inclui a biblioteca padrão do Pico para entrada e saída.
#include "hardware/gpio.h"            // Inclui a biblioteca de controle GPIO do hardware.
#include "pico/bootrom.h"             // Necessário para funções como reset_usb_boot.
#include "menu_b_operacao.h"            //include de Gleison F.
#define ROWS 4                        // Define o número de linhas do teclado matricial.
#define COLS 4                        // Define o número de colunas do teclado matricial.

int row_pins[ROWS] = {16, 17, 18, 19}; // Define os pinos GPIO usados para as linhas do teclado.
int col_pins[COLS] = {20, 4, 9, 8};    // Define os pinos GPIO usados para as colunas do teclado.

#define LED_R_PIN 13                  // Define o pino GPIO do LED vermelho.
#define LED_G_PIN 11                  // Define o pino GPIO do LED verde.
#define LED_B_PIN 12                  // Define o pino GPIO do LED azul.
#define BUZZER_PIN 10                 // Define o pino GPIO do buzzer.

int keypad[ROWS][COLS] = {            // Mapeia os valores associados a cada tecla do teclado.
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int last_key = -1;                    // Armazena a última tecla pressionada (-1 significa nenhuma).
int current_mode = 0;                 // Define o modo atual do sistema (0: principal, 1: alternativo).
//prototipos
void menu_switch_feedback();
void setup_gpio();
int read_keypad();
void play_note(int frequency, int duration_ms);
void control_mode_0(int key);
void control_mode_1(int key);

void menu_switch_feedback() {         // Função para fornecer feedback ao alternar menus.
    for (int i = 0; i < 2; i++) {     // Realiza duas piscadas dos LEDs.
        gpio_put(LED_R_PIN, 1);       // Acende o LED vermelho.
        gpio_put(LED_G_PIN, 1);       // Acende o LED verde.
        gpio_put(LED_B_PIN, 1);       // Acende o LED azul.
        sleep_ms(200);                // Aguarda 200 ms.
        gpio_put(LED_R_PIN, 0);       // Apaga o LED vermelho.
        gpio_put(LED_G_PIN, 0);       // Apaga o LED verde.
        gpio_put(LED_B_PIN, 0);       // Apaga o LED azul.
        sleep_ms(200);                // Aguarda 200 ms.
    }

    play_note(1000, 100);             // Toca um tom de 1 kHz por 100 ms.
    sleep_ms(100);                    // Aguarda 100 ms.
    play_note(1200, 100);             // Toca um tom de 1.2 kHz por 100 ms.
}

void setup_gpio() {                   // Configuração inicial dos pinos GPIO.
    gpio_init(LED_R_PIN);             // Inicializa o pino do LED vermelho.
    gpio_set_dir(LED_R_PIN, GPIO_OUT); // Define o pino do LED vermelho como saída.
    gpio_init(LED_G_PIN);             // Inicializa o pino do LED verde.
    gpio_set_dir(LED_G_PIN, GPIO_OUT); // Define o pino do LED verde como saída.
    gpio_init(LED_B_PIN);             // Inicializa o pino do LED azul.
    gpio_set_dir(LED_B_PIN, GPIO_OUT); // Define o pino do LED azul como saída.

    gpio_init(BUZZER_PIN);            // Inicializa o pino do buzzer.
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); // Define o pino do buzzer como saída.

    for (int i = 0; i < ROWS; i++) {  // Itera sobre cada linha do teclado.
        gpio_init(row_pins[i]);       // Inicializa o pino da linha atual.
        gpio_set_dir(row_pins[i], GPIO_OUT); // Define o pino como saída.
        gpio_put(row_pins[i], 1);     // Define o pino como alto (1).
    }

    for (int i = 0; i < COLS; i++) {  // Itera sobre cada coluna do teclado.
        gpio_init(col_pins[i]);       // Inicializa o pino da coluna atual.
        gpio_set_dir(col_pins[i], GPIO_IN);  // Define o pino como entrada.
        gpio_pull_up(col_pins[i]);    // Ativa o resistor de pull-up no pino.
    }
}

int read_keypad() {                   // Função para ler a entrada do teclado.
    static uint32_t last_press_time = 0; // Armazena o tempo da última tecla pressionada.
    const uint32_t debounce_delay = 200000; // Define um atraso para debouncing (200 ms).

    for (int row = 0; row < ROWS; row++) { // Itera sobre as linhas do teclado.
        gpio_put(row_pins[row], 0);   // Define a linha atual como baixa (ativa).

        for (int col = 0; col < COLS; col++) { // Itera sobre as colunas do teclado.
            if (gpio_get(col_pins[col]) == 0) { // Verifica se a tecla foi pressionada.
                if (time_us_64() - last_press_time > debounce_delay) { // Verifica o debounce.
                    last_press_time = time_us_64(); // Atualiza o tempo da última pressão.
                    gpio_put(row_pins[row], 1);     // Define a linha como alta novamente.
                    return keypad[row][col];        // Retorna o valor da tecla pressionada.
                }
            }
        }
        gpio_put(row_pins[row], 1);   // Define a linha como alta novamente.
    }
    return -1;                        // Retorna -1 se nenhuma tecla foi pressionada.
}

void play_note(int frequency, int duration_ms) { // Função para tocar uma nota no buzzer.
    int delay_us = 1000000 / (2 * frequency);    // Calcula o atraso baseado na frequência.
    int cycles = (duration_ms * 1000) / (2 * delay_us); // Calcula o número de ciclos.

    for (int i = 0; i < cycles; i++) {          // Itera para gerar os ciclos da onda sonora.
        gpio_put(BUZZER_PIN, 1);                // Liga o buzzer.
        sleep_us(delay_us);                     // Aguarda pelo tempo do ciclo.
        gpio_put(BUZZER_PIN, 0);                // Desliga o buzzer.
        sleep_us(delay_us);                     // Aguarda pelo tempo do ciclo.
    }
}


// Função para controlar o modo principal do sistema.
void control_mode_0(int key) {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    switch (key)
    {
    case  1:
        gpio_put(LED_R_PIN, 1);
        break;
    case 2:
        gpio_put(LED_B_PIN, 1);
        break;
    case 3:
        gpio_put(LED_G_PIN, 1);
        
        
        break;
    case 4:
           // 🎮 Tema do Super Mario Bros 🎮

    // Primeira parte
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(510, 100);  // Si
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(770, 100);  // Fá#
        sleep_ms(300);
        play_note(380, 100);  // Sol
        sleep_ms(300);

       // Segunda parte
        play_note(510, 100);  // Si
        sleep_ms(100);
        play_note(380, 100);  // Sol
        sleep_ms(100);
        play_note(320, 100);  // Mi
        sleep_ms(300);

        play_note(440, 100);  // Lá
        sleep_ms(100);
        play_note(480, 80);   // Si
        sleep_ms(80);
        play_note(450, 100);  // Lá#
        sleep_ms(100);
        play_note(430, 100);  // Lá
        sleep_ms(100);

        play_note(380, 100);  // Sol
        sleep_ms(100);
        play_note(660, 80);   // Mi
        sleep_ms(80);
        play_note(760, 50);   // Fá#
        sleep_ms(50);
        play_note(860, 100);  // Sol#
        sleep_ms(300);

        // Final da melodia
        play_note(700, 100);  // Fá
        sleep_ms(100);
        play_note(760, 100);  // Fá#
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(520, 100);  // Dó#
        sleep_ms(100);
        play_note(580, 100);  // Ré#
        sleep_ms(100);
        play_note(480, 100);  // Si

        sleep_ms(300);

       // Repetição da parte principal
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(510, 100);  // Si
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(770, 100);  // Fá#
        sleep_ms(300);
        play_note(380, 100);  // Sol
        sleep_ms(300);

       // Segunda parte (repetida)
        play_note(510, 100);  // Si
        sleep_ms(100);
        play_note(380, 100);  // Sol
        sleep_ms(100);
        play_note(320, 100);  // Mi
        sleep_ms(300);

        play_note(440, 100);  // Lá
        sleep_ms(100);
        play_note(480, 80);   // Si
        sleep_ms(80);
        play_note(450, 100);  // Lá#
        sleep_ms(100);
        play_note(430, 100);  // Lá
        sleep_ms(100);

        play_note(380, 100);  // Sol
        sleep_ms(100);
        play_note(660, 80);   // Mi
        sleep_ms(80);
        play_note(760, 50);   // Fá#
        sleep_ms(50);
        play_note(860, 100);  // Sol#
        sleep_ms(300);

    // Final com pausa
        play_note(700, 100);  // Fá
        sleep_ms(100);
        play_note(760, 100);  // Fá#
        sleep_ms(100);
        play_note(660, 100);  // Mi
        sleep_ms(100);
        play_note(520, 100);  // Dó#
        sleep_ms(100);
        play_note(580, 100);  // Ré#
        sleep_ms(100);
        play_note(480, 100);  // Si
        sleep_ms(300);


        break;
    case 5:
        gpio_put(LED_R_PIN, 1);
        gpio_put(LED_G_PIN, 1);
        gpio_put(LED_B_PIN, 1);
       
        break;
    case 6:

        break;

    case 7:

        break;
    case 8:
        operacao_inicial();//função de Gleison F presente no menu_B_operacao
        break;
    case 9:

        break;
    case 10:

        break;
    case 11:

        break;
    case 12:

        break;
    case 13:
        current_mode = 1;
        menu_switch_feedback();
        break;
    case 14:
       //entrando no modo bootloader
        printf("Entering bootloader mode...\n");
    gpio_put(LED_R_PIN, 1); // Indicação visual (opcional)
    sleep_ms(1000);         // Pequena pausa antes de reiniciar
    reset_usb_boot(0, 0);   // Reinicia no modo USB Bootloader

        break;
    case 15:

        break;
    case 16:

        break;
  
    
    default:
        break;
   }
    
}

//Função para controlar o modo alternativo do sistema.
void control_mode_1(int key) {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);
    switch (key)
    {
    case  1:
        gpio_put(LED_R_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_R_PIN,0);
        break;
    case 2:
        
        break;
    case 3:
        
        break;
    case 4:
  
        break;
    case 5:

        break;
    case 6:

        break;

    case 7:

        break;
    case 8:

        break;
    case 9:

        break;
    case 10:

        break;
    case 11:

        break;
    case 12:

        break;
    case 13:
        current_mode = 0;
        menu_switch_feedback();
        break;
    case 14:
    
        break;
    case 15:

        break;
    case 16:

        break;
  
    
    default:
        break;
   }
    
}


int main(){
    stdio_init_all();// Inicializa a entrada e saída padrão.
    setup_gpio(); // Configura os pinos GPIO.

    while (true) {
        int key = read_keypad(); // Lê a tecla pressionada.
        if (key != -1 && key != last_key) { // Se houver tecla pressionada diferente da última.
            if (current_mode == 0) { // Executa o modo principal.
                control_mode_0(key);
            } else if (current_mode == 1) { // Executa o modo alternativo.
                control_mode_1(key);
            }
            //last_key = key; // Atualiza a última tecla pressionada.(tirar essa parte depois)
        }
        sleep_ms(100);
    }
}


