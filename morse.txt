#include "pico/stdlib.h"

#define DOT_DURATION 200  // Duração de um ponto (curto)
#define DASH_DURATION 600 // Duração de um traço (longo)
#define LETTER_SPACE 600  // Espaço entre letras
#define WORD_SPACE 1200   // Espaço entre palavras

// Função para piscar o LED em código morse.
void morse_code(const char* message) {
    while (*message) {  // Percorre a mensagem
        if (*message == ' ') {
            sleep_ms(WORD_SPACE); // Pausa entre palavras
        } else {
            char letter = *message;
            const char* morse = NULL;
            
            // Mapeamento de cada letra para código Morse
            switch (letter) {
                case 'O': morse = "---"; break;
                case 'L': morse = ".-.."; break;
                case 'A': morse = ".-"; break;
                case 'M': morse = "--"; break;
                case 'U': morse = "..-"; break;
                case 'N': morse = "-."; break;
                case 'D': morse = "-.."; break;
                case 'I': morse = ".."; break;
                case 'P': morse = ".--."; break;
                default: break; // Ignora caracteres não mapeados
            }

            // Pisca o LED de acordo com o código Morse
            for (int i = 0; morse && morse[i] != '\0'; i++) {
                if (morse[i] == '.') {  // Ponto
                    gpio_put(LED_R_PIN, 1);
                    sleep_ms(DOT_DURATION);
                    gpio_put(LED_R_PIN, 0);
                } else if (morse[i] == '-') {  // Traço
                    gpio_put(LED_R_PIN, 1);
                    sleep_ms(DASH_DURATION);
                    gpio_put(LED_R_PIN, 0);
                }
                sleep_ms(DOT_DURATION);  // Intervalo entre os sinais (ponto e traço)
            }
            
            sleep_ms(LETTER_SPACE);  // Intervalo entre as letras
        }
        message++;  // Avança para o próximo caractere
    }
}


/*int main() {
    stdio_init_all();   // Inicializa a entrada e saída padrão.
    setup_gpio();       // Configura os pinos GPIO.

    while (true) {
        // Envia a mensagem "Ola Mundo" em código Morse.
        morse_code("OLA MUNDO");
        sleep_ms(2000);  // Pausa entre repetições
    }
}
*/
