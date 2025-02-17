## 📋 Instruções de Funcionamento

Este projeto utiliza o Raspberry Pi Pico W para implementar um sistema interativo baseado em um teclado matricial 4x4, LEDs, buzzer e diferentes modos de controle.

### 🔧 Configuração de Hardware

- **Teclado Matricial (4x4):**
  - **Linhas:** GPIO 16, 17, 18, 19.
  - **Colunas:** GPIO 20, 4, 9, 8.
- **LEDs RGB:**
  - **LED Vermelho:** GPIO 13.
  - **LED Verde:** GPIO 11.
  - **LED Azul:** GPIO 12.
- **Buzzer:** GPIO 10.

### 🚀 Inicialização

1. Conecte o hardware conforme especificado.
2. Compile e envie o código para o Raspberry Pi Pico W.
3. O sistema será inicializado no **Modo Principal** (Mode 0) por padrão.

---

### 🕹️ Modos de Operação

#### **Modo 0 - Principal**
- Cada tecla do teclado tem uma função específica:
  - **Tecla 1:** Acende o LED vermelho.
  - **Tecla 2:** Acende o LED azul.
  - **Tecla 3:** Acende o LED verde.
  - **Tecla A:** Toca o tema de "Super Mario Bros".
  - **Tecla 4:** Acende todos os LEDs (RGB).
  - **Tecla B:** Acende os LEDs enquanto executa no Buzzer uma musiquinha.
  - **Tecla "*":** Alterna para o **Modo 1**.
  - **Tecla 0:** Entra no modo bootloader.
  - **Tecla #:** OLA MUNDO em codigo morse.
  - **Tecla D:** SOS em codigo morse.

#### **Modo 1 - Alternativo**
- Similar ao Modo 0, mas com comportamento diferenciado:
  - **Tecla 1:** Acende o LED vermelho por 1 segundo.
  - **Tecla C:** Aciona o pisca led em várias frequências e finaliza piscando os 3 de vez.
  - **Tecla "*":** Retorna ao **Modo 0**.

---

### 🔹 Comandos Especiais
- **Trocar de Modo:**
  - Pressione a tecla **"*"** para alternar entre os modos.
  - O feedback de troca inclui piscadas dos LEDs e sons do buzzer.
- **Entrar no Bootloader:**
  - Pressione a tecla **0** para entrar no modo bootloader. Um LED acenderá como indicação antes de reiniciar.

---

### Link do vídeo - Apresentação da tarefa
- https://youtu.be/EGRNe30qIlA

---

### ⚠️ Observações
- **Debouncing:** O código utiliza um atraso de 200 ms para evitar múltiplas leituras ao pressionar uma tecla.
- **Modificações:** Novas funcionalidades podem ser adicionadas ao mapear as teclas restantes no teclado.
