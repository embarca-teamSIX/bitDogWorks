// Inclui bibliotecas padrão para o Raspberry Pi Pico
#include "pico/stdlib.h"      // Funções básicas (GPIO, temporização, etc.)
#include "hardware/gpio.h"    // Funções específicas para manipular GPIOs

// Define o número de linhas e colunas do teclado matricial
#define ROWS 4
#define COLS 4

// Define os pinos GPIO conectados às linhas e colunas do teclado
int row_pins[ROWS] = {16, 17, 28, 18};  // Linhas do teclado
int col_pins[COLS] = {19, 20, 9, 4};    // Colunas do teclado

// Define os pinos GPIO para o LED RGB e para o buzzer
#define LED_R_PIN 13  // LED Vermelho
#define LED_G_PIN 11  // LED Verde
#define LED_B_PIN 12  // LED Azul
#define BUZZER_PIN 10 // Buzzer

// Matriz representando as teclas do teclado
int keypad[ROWS][COLS] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

// Variável para armazenar a última tecla pressionada
int last_key = -1;

/*-----------------------------------------------
 * Função: setup_gpio
 * Objetivo: Inicializa todos os pinos GPIO utilizados
 *----------------------------------------------*/
void setup_gpio() {
    // Inicializa os pinos do LED RGB como saída
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    // Inicializa o pino do buzzer como saída
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicializa os pinos das linhas do teclado como saída e coloca em nível alto
    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1);  // Mantém as linhas em nível alto
    }

    // Inicializa os pinos das colunas como entrada com resistor de pull-up
    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);  // Ativa resistor de pull-up
    }
}

/*-----------------------------------------------
 * Função: read_keypad
 * Objetivo: Detectar qual tecla foi pressionada
 * Retorno: Número da tecla pressionada ou -1 se nenhuma tecla foi pressionada
 *----------------------------------------------*/
int read_keypad() {
    static uint32_t last_press_time = 0;  // Armazena o tempo da última tecla pressionada
    const uint32_t debounce_delay = 200000;  // Delay de debounce (200ms)

    // Percorre todas as linhas do teclado
    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 0);  // Define a linha atual como LOW

        // Percorre todas as colunas para verificar se alguma tecla está pressionada
        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col]) == 0) {  // Se a coluna estiver LOW, tecla foi pressionada
                if (time_us_64() - last_press_time > debounce_delay) {
                    last_press_time = time_us_64();  // Atualiza o tempo de debounce
                    gpio_put(row_pins[row], 1);      // Restaura a linha para HIGH
                    return keypad[row][col];         // Retorna o número da tecla pressionada
                }
            }
        }
        gpio_put(row_pins[row], 1);  // Restaura a linha para HIGH antes de passar para a próxima
    }
    return -1;  // Nenhuma tecla foi pressionada
}

/*-----------------------------------------------
 * Função: play_note
 * Objetivo: Tocar uma nota no buzzer
 * Parâmetros: frequency - frequência da nota (Hz)
 *             duration_ms - duração da nota (ms)
 *----------------------------------------------*/
void play_note(int frequency, int duration_ms) {
    int delay_us = 1000000 / (2 * frequency);               // Calcula o atraso para gerar a frequência
    int cycles = (duration_ms * 1000) / (2 * delay_us);     // Calcula o número de ciclos

    // Gera a frequência ligando e desligando o buzzer
    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER_PIN, 1);  // Liga o buzzer
        sleep_us(delay_us);
        gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
        sleep_us(delay_us);
    }
}

/*-----------------------------------------------
 * Função: control_led
 * Objetivo: Acionar o LED RGB com base na tecla pressionada
 *----------------------------------------------*/
void control_led(int key) {
    // Desliga todas as cores do LED
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);

    // Liga cores específicas dependendo da tecla pressionada
    if (key == 1) gpio_put(LED_R_PIN, 1);       // Vermelho
    else if (key == 2) gpio_put(LED_B_PIN, 1);  // Azul
    else if (key == 3) gpio_put(LED_G_PIN, 1);  // Verde
    else if (key == 5 || key == 7) {
        gpio_put(LED_R_PIN, 1);
        gpio_put(LED_G_PIN, 1);
        gpio_put(LED_B_PIN, 1);  // Branco (todas as cores ligadas)
    }
}

/*-----------------------------------------------
 * Função: control_buzzer
 * Objetivo: Tocar sequência de notas se a tecla 4 for pressionada
 *----------------------------------------------*/
void control_buzzer(int key) {
    if (key == 4) {
        play_note(262, 500);  // Dó
        play_note(294, 500);  // Ré
        play_note(330, 500);  // Mi
        play_note(349, 500);  // Fá
        play_note(392, 500);  // Sol
    }
}

/*-----------------------------------------------
 * Função: main
 * Objetivo: Ponto de entrada do programa
 *----------------------------------------------*/
int main() {
    stdio_init_all();  // Inicializa a comunicação padrão
    setup_gpio();      // Configura todos os GPIOs

    // Loop infinito para monitorar o teclado
    while (true) {
        int key = read_keypad();  // Lê a tecla pressionada

        // Se uma nova tecla for pressionada, controla o LED e o buzzer
        if (key != -1 && key != last_key) {
            control_led(key);       // Aciona o LED correspondente
            control_buzzer(key);    // Aciona o buzzer, se necessário
            last_key = key;         // Atualiza a última tecla pressionada
        }
        sleep_ms(100);  // Aguarda 100ms para evitar leitura rápida demais
    }
}
