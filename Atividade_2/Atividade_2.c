#include "pico/stdlib.h"
#include "pico/time.h"
#include <stdio.h>

// Definição dos pinos conforme o enunciado:
// LED_AZUL no GPIO 12, LED_VERMELHO no GPIO 13, LED_VERDE no GPIO 11 e BOTAO_A no GPIO 5.
#define LED_AZUL       12
#define LED_VERMELHO   13
#define LED_VERDE      11
#define BOTAO_A        5

// Variáveis globais de controle da sequência
volatile bool sequencia_ativa = false;  // Indica se uma sequência já está em andamento
volatile int etapa = 0;                 // 0: inativa; 1: após início; 2: depois do 1º atraso; 3: depois do 2º atraso

/**
 * callback_desliga_led()
 * Função de callback para o temporizador one-shot.
 * Em cada chamada, desliga um LED conforme a ordem estabelecida:
 *   - Etapa 1: desliga o LED_AZUL (mantendo LED_VERMELHO e LED_VERDE ligados)
 *   - Etapa 2: desliga o LED_VERMELHO (mantendo somente LED_VERDE ligado)
 *   - Etapa 3: desliga o LED_VERDE, finalizando a sequência
 * Cada transição é agendada com um atraso de 3000ms.
 */
int64_t callback_desliga_led(alarm_id_t id, void *user_data) {
    if (etapa == 1) {
        gpio_put(LED_AZUL, 0);  // Desliga o LED_AZUL
        etapa = 2;
        add_alarm_in_ms(3000, callback_desliga_led, NULL, false);
    } else if (etapa == 2) {
        gpio_put(LED_VERMELHO, 0);  // Desliga o LED_VERMELHO
        etapa = 3;
        add_alarm_in_ms(3000, callback_desliga_led, NULL, false);
    } else if (etapa == 3) {
        gpio_put(LED_VERDE, 0);  // Desliga o LED_VERDE (finaliza a sequência)
        sequencia_ativa = false;
        etapa = 0;
        printf("Sequência finalizada\n");
    }
    return 0;  // Retorna 0 para indicar que este alarme não se repete automaticamente
}

int main() {
    stdio_init_all();
    sleep_ms(1000);  // Aguarda a inicialização completa do sistema

    // Inicializa os pinos dos LEDs como saída
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa o pino do botão como entrada com resistor pull-up
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_IN);
    gpio_pull_up(BOTAO_A);

    // Garante que os LEDs iniciem apagados.
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_VERDE, 0);

    printf("Aguardando pressionar o botão...\n");

    while (true) {
        // Se não houver sequência ativa e o botão for pressionado (nível 0)
        if (!sequencia_ativa && gpio_get(BOTAO_A) == 0) {
            // Debounce simples: espera 50ms e verifica novamente
            sleep_ms(50);
            if (gpio_get(BOTAO_A) == 0) {
                sequencia_ativa = true;
                etapa = 1;
                // Liga os três LEDs (nível alto)
                gpio_put(LED_AZUL, 1);
                gpio_put(LED_VERMELHO, 1);
                gpio_put(LED_VERDE, 1);
                printf("Sequência iniciada\n");
                // Agenda o primeiro alarme one-shot para 3000ms
                add_alarm_in_ms(3000, callback_desliga_led, NULL, false);
                // Aguarda até que o botão seja solto para evitar reentrada imediata
                while (gpio_get(BOTAO_A) == 0) {
                    sleep_ms(10);
                }
            }
        }
        sleep_ms(10);
    }

    return 0;
}
