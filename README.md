## PROJETO - Temporizadores com Raspberry Pi Pico W  
**(SUB GRUPO 6 - ATIVIDADE DA AULA SÍNCRONA)**

───────────────────────────────────────────────

*Idealizadora do Projeto:*  
**AMANDA CARDOSO LOPES**

───────────────────────────────────────────────

## OBJETIVO DO PROJETO

───────────────────────────────────────────────

Este projeto tem como finalidade demonstrar o uso de temporizadores utilizando o Pico SDK no Raspberry Pi Pico W. São apresentados dois experimentos distintos que evidenciam a implementação de técnicas de temporização e controle via callbacks, bem como a aplicação de debounce para botões.  
  
As atividades propostas são:  
- **Atividade 1:** Criação de um semáforo com temporização repetitiva, utilizando a função `add_repeating_timer_ms()`.  
- **Atividade 2:** Desenvolvimento de um temporizador one-shot, acionado por um botão, usando a função `add_alarm_in_ms()`.

───────────────────────────────────────────────

## FUNCIONALIDADES DO PROJETO

───────────────────────────────────────────────

1. **Atividade 1 – Semáforo com Temporização Repetitiva:**  
   - Inicia com o LED vermelho aceso.  
   - A cada 3 segundos, o semáforo muda de sinal na sequência: vermelho → amarelo → verde → vermelho.  
   - A função de callback é acionada repetidamente a cada 3000 ms, atualizando o estado dos LEDs e enviando mensagens pela porta serial.

2. **Atividade 2 – Temporizador One-Shot com Botão:**  
   - Ao pressionar o botão (BOTÃO_A no GPIO 5), os três LEDs (LED_AZUL, LED_VERMELHO e LED_VERDE nos GPIOs 12, 13 e 11, respectivamente) se acendem simultaneamente.  
   - Após o acionamento, uma sequência temporizada de 3000 ms é iniciada:  
     - Primeiro, o LED_AZUL é desligado (mantendo os LEDs vermelho e verde acesos).  
     - Em seguida, o LED_VERMELHO é apagado (ficando apenas o LED_VERDE ligado).  
     - Por fim, o LED_VERDE é desligado, concluindo a sequência.  
   - Durante a execução da sequência, novas pressões do botão são ignoradas até que ela seja finalizada.  
   - Um mecanismo simples de debounce (50ms) previne acionamentos indesejados devido ao efeito bouncing.

───────────────────────────────────────────────

## COMPONENTES UTILIZADOS

───────────────────────────────────────────────

### Elementos Comuns (para ambas as atividades)
- **Microcontrolador:** Raspberry Pi Pico W.
- **Resistores:** 3 unidades de 330 Ω (para limitar a corrente dos LEDs).
- **Fios de Conexão:**  
  - Fio Verde para o negativo.  
  - Fio Preto para o positivo.

### Atividade 1 – Semáforo
- **LEDs:**  
  - LED Vermelho, LED Amarelo e LED Verde, conectados aos GPIOs 11, 12 e 13 (utilizando o LED RGB disponível no BitDogLab).

### Atividade 2 – Temporizador One-Shot
- **LEDs:**  
  - LED Azul, LED Vermelho e LED Verde, conectados aos GPIOs 12, 13 e 11 (usando o LED RGB do BitDogLab).  
- **Botão:**  
  - BOTÃO_A, conectado ao GPIO 5, utilizado para iniciar a sequência temporizada.

───────────────────────────────────────────────

## TECNOLOGIAS UTILIZADAS

───────────────────────────────────────────────

- **Linguagem:** C  
- **Plataforma de Desenvolvimento:** Raspberry Pi Pico W com Pico SDK  
- **Simulação:** Plataforma Wokwi  
- **Componentes Eletrônicos:**  
  - LED RGB (GPIOs 11, 12 e 13)  
  - Botão (BOTÃO_A, GPIO 5)  
  - Resistores de 330 Ω  
  - Fios de conexão (Fio Verde e Fio Preto)

───────────────────────────────────────────────

## COMO EXECUTAR O PROJETO?

───────────────────────────────────────────────


### VIA VSCODE

1. **Configuração Inicial:**  
   - Clone o repositório:
     ```sh
     git clone https://github.com/4mandaCardoso/EmbarcaTech_Atv29_01.git
     ```  
   - Abra o projeto no VS Code ou no ambiente de sua preferência.

2. **Carregamento e Compilação:**  
   - Compile o código e gere o arquivo UF2.

3. **Upload e Simulação:**  
   - Carregue o arquivo UF2 na placa ou clique no arquivo "diagram.json" para efetuar a simulação por meio do wokwi.
   - Para a Atividade 1: Observe o comportamento do semáforo e as mensagens na porta serial.  
   - Para a Atividade 2: Pressione o botão (BOTÃO_A) para iniciar a sequência temporizada dos LEDs e monitore a execução pela porta serial.

### Possibilidade alternativa: 

   - Você pode executar os projetos no navegador via o simulador Wokwi clicando nos links abaixo:

1. **Atividade 1:**  
*link:* https://wokwi.com/projects/421977600200500225

2. **Atividade 2** 
*link:* https://wokwi.com/projects/421973619392236545 

───────────────────────────────────────────────

## CONCLUSÃO

───────────────────────────────────────────────

Este projeto demonstra, de maneira prática, o uso de temporizadores no Pico SDK para controlar dispositivos externos.  
- **Na Atividade 1,** foi implementado um semáforo com temporização repetitiva, evidenciando a alternância dos sinais com intervalos de 3 segundos.  
- **Na Atividade 2,** um temporizador one-shot acionado por botão foi criado, permitindo o controle sequencial dos LEDs com um mecanismo de debounce para garantir a estabilidade do acionamento.

A experiência reforça conceitos importantes sobre temporização, callbacks e técnicas de debouncing, proporcionando uma sólida base para projetos mais complexos envolvendo controle de dispositivos via microcontrolador.

───────────────────────────────────────────────

*Desenvolvido por: Amanda Cardoso Lopes*
