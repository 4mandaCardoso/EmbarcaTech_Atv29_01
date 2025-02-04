#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>

// Definição dos pinos dos LEDs
#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_VERDE 11

// Estados do semáforo
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} EstadoSemaforo;

// Estado atual do semáforo
volatile EstadoSemaforo estado_atual = VERMELHO;

// Função chamada pelo temporizador para alternar os LEDs
bool alternar_semaforo(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);
    
    // Alterna o estado do semáforo
    switch (estado_atual) {
        case VERMELHO:
            gpio_put(LED_AMARELO, 1); // Liga o amarelo
            estado_atual = AMARELO;
            break;
        case AMARELO:
            gpio_put(LED_VERDE, 1); // Liga o verde
            estado_atual = VERDE;
            break;
        case VERDE:
            gpio_put(LED_VERMELHO, 1); // Liga o vermelho
            estado_atual = VERMELHO;
            break;
    }
    return true; // Mantém o temporizador em execução
}

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();
    sleep_ms(1000); // Aguarda 1 segundo para garantir a inicialização
    
    // Configuração dos pinos como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    
    // Estado inicial do semáforo: vermelho ligado
    estado_atual = VERMELHO;
    gpio_put(LED_VERMELHO, 1);
    
    // Configuração do temporizador para alternar o semáforo a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, alternar_semaforo, NULL, &timer);
    
    // Loop principal: imprime o estado do semáforo a cada 1 segundo
    while (true) {
        switch (estado_atual) {
            case VERMELHO:
                printf("Semáforo: VERMELHO - Pare!\n");
                break;
            case AMARELO:
                printf("Semáforo: AMARELO - Atenção!\n");
                break;
            case VERDE:
                printf("Semáforo: VERDE - Siga!\n");
                break;
        }
        sleep_ms(1000); // Aguarda 1 segundo antes de exibir novamente.
    }
    return 0;
}

