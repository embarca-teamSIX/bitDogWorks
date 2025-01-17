#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/bootrom.h"  // Necessário para reset_usb_boot

#define ROWS 4
#define COLS 4

int row_pins[ROWS] = {16, 17, 18, 19};
int col_pins[COLS] = {20, 4, 9, 8};

#define LED_R_PIN 13
#define LED_G_PIN 11
#define LED_B_PIN 12
#define BUZZER_PIN 10

int keypad[ROWS][COLS] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};

int last_key = -1;

void setup_gpio() {
    gpio_init(LED_R_PIN);
    gpio_set_dir(LED_R_PIN, GPIO_OUT);
    gpio_init(LED_G_PIN);
    gpio_set_dir(LED_G_PIN, GPIO_OUT);
    gpio_init(LED_B_PIN);
    gpio_set_dir(LED_B_PIN, GPIO_OUT);

    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    for (int i = 0; i < ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 1);
    }

    for (int i = 0; i < COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }
}

int read_keypad() {
    static uint32_t last_press_time = 0;
    const uint32_t debounce_delay = 200000;

    for (int row = 0; row < ROWS; row++) {
        gpio_put(row_pins[row], 0);

        for (int col = 0; col < COLS; col++) {
            if (gpio_get(col_pins[col]) == 0) {
                if (time_us_64() - last_press_time > debounce_delay) {
                    last_press_time = time_us_64();
                    gpio_put(row_pins[row], 1);
                    return keypad[row][col];
                }
            }
        }
        gpio_put(row_pins[row], 1);
    }
    return -1;
}

void play_note(int frequency, int duration_ms) {
    int delay_us = 1000000 / (2 * frequency);
    int cycles = (duration_ms * 1000) / (2 * delay_us);

    for (int i = 0; i < cycles; i++) {
        gpio_put(BUZZER_PIN, 1);
        sleep_us(delay_us);
        gpio_put(BUZZER_PIN, 0);
        sleep_us(delay_us);
    }
}

void control_led(int key) {
    gpio_put(LED_R_PIN, 0);
    gpio_put(LED_G_PIN, 0);
    gpio_put(LED_B_PIN, 0);

    if (key == 1) gpio_put(LED_R_PIN, 1);
    else if (key == 2) gpio_put(LED_B_PIN, 1);
    else if (key == 3) gpio_put(LED_G_PIN, 1);
    else if (key == 5) {
        gpio_put(LED_R_PIN, 1);
        gpio_put(LED_G_PIN, 1);
        gpio_put(LED_B_PIN, 1);
   }
}

void control_buzzer(int key) {
   if (key == 4) {
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

   }
}

void enter_bootloader_mode() {
    printf("Entering bootloader mode...\n");
    gpio_put(LED_R_PIN, 1); // Indicação visual (opcional)
    sleep_ms(1000);         // Pequena pausa antes de reiniciar
    reset_usb_boot(0, 0);   // Reinicia no modo USB Bootloader
}

int main(){
    stdio_init_all();
    setup_gpio();

    while (true) {
        int key = read_keypad();
        if (key != -1 && key != last_key) {
            control_led(key);
            control_buzzer(key);

            if (key == 14) {
                enter_bootloader_mode();
            }

            last_key = key;
        }
        sleep_ms(100);
 }
}