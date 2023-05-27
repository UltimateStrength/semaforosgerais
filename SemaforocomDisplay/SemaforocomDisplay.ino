                                    //** */ // Traffic Light with Display Project//** */ //
                                    //** */ // Created by: Ulti
//** */ //                          My Discord: Ultimate Strength#2307 //** */ // 
                                    //** */ // Github: https://github.com/UltimateStrength
//** */ //                          If you use the Scripts Credit it with:
                                    //** */ // "Made by Ulti" or "FINISAUTEMPOTENTIAE ©" 
                                        //** */ // End Title //** */ //

#define botao 2
#define LED_VERDE_CAR 0
#define LED_AMARELO_CAR 1
#define LED_VERMELHO_CAR 3
#define LED_VERDE_PED 4
#define LED_VERMELHO_PED 5

int modo = 0;

bool displaySeteSeg[10][7] = {
 { 1, 1, 1, 1, 0, 1, 1 }, //DIGITO 0
 { 1, 0, 0, 0, 0, 1, 0 }, //DIGITO 1
 { 0, 1, 1, 0, 1, 1, 1 }, //DIGITO 2
 { 1, 0, 1, 0, 1, 1, 1 }, //DIGITO 3
 { 1, 0, 0, 1, 1, 1, 0 }, //DIGITO 4
 { 1, 0, 1, 1, 1, 0, 1 }, //DIGITO 5
 { 1, 1, 1, 1, 1, 0, 1 }, //DIGITO 6
 { 1, 0, 0, 0, 0, 1, 1 }, //DIGITO 7
 { 1, 1, 1, 1, 1, 1, 1 }, //DIGITO 8
 { 1, 0, 1, 1, 1, 1, 1 } //DIGITO 9
};
void setup() {
 /* Loop para configurar os pinos como saída. */
 for (int i = 0; i <= 13; i++) {
 pinMode(i, OUTPUT);
 }
 /* Configuramos o pino do botão como entrada. */
 pinMode(botao, INPUT);
 /* Ativa a função de interrupção no pino que o botão está conectado. v */
 attachInterrupt(digitalPinToInterrupt(botao), botaoAcionado, CHANGE);
 /* Comando para o Display de Ânodo Comum iniciar desligado.
*/
    
 if (modelo == "ânodo comum") {
 for (int i = 7; i <= 13; i++) {
 digitalWrite(i, HIGH);
 }
 }
}
void loop() {
 switch (modo) {
 case 0:
 /* Caso o botão não for pressionado mantém o semáforo
 aberto para os carros chamando a função "carros()". */
 carros();
 break;
 case 1:
 /* Caso o botão seja pressionado, o semáforo entrará no */
 /* modo de travessia chamando a função "travessia()". */
 travessia();
 modo = 0;
 break;
 }
}
/* Após pressionar o botão, será executada essa função, ela
 seleciona o modo de operação do semáforo. */
void botaoAcionado() {
 modo = 1;
}
/* Função que mantém o semáforo aberto para os carros. */
void carros() {
 digitalWrite(LED_VERDE_CAR, HIGH);
 digitalWrite(LED_VERMELHO_PED, HIGH);
 digitalWrite(LED_VERMELHO_CAR, LOW);
 /* Desliga o display. */
 if (modelo == "ânodo comum") {
 for (int i = 7; i <= 13; i++) {
 digitalWrite(i, HIGH);
 }
 } else {
 for (int i = 7; i <= 13; i++) {
 digitalWrite(i, LOW);
 }
 }
}

/* Função que controla o semáforo para a travessia de pedestre. */
void travessia() {
 /* Aguarda 1 segundo para entrar no modo travessia. */
 delay(1000);
 /* Aciona o amarelo do semáforo dos carros. */
 digitalWrite(LED_VERDE_CAR, LOW);
 digitalWrite(LED_AMARELO_CAR, HIGH);
 delay(3000);
 /* Aciona vermelho para os carros e verde para pedestre. */
 digitalWrite(LED_AMARELO_CAR, LOW);
 digitalWrite(LED_VERMELHO_CAR, HIGH);
 digitalWrite(LED_VERDE_PED, HIGH);
 digitalWrite(LED_VERMELHO_PED, LOW);
 /* Inicia a contagem de 9 a 0 para a travessia. */
 boolean led = HIGH;
 for (int contador = 9; contador >= 0; contador--) {
 /* Chama a função para acionar o display. */
 ligaSegmentosDisplay(contador);
 if (contador <= 6) {
 digitalWrite(LED_VERDE_PED, LOW);
 digitalWrite(LED_VERMELHO_PED, led);
 led = !led;
 }
 }
}
/* Função para acionar o display com o dígito correspondente. */
void ligaSegmentosDisplay(int digito) {
 byte pino = 7;
 for (byte contadorSegmentos = 0; contadorSegmentos <= 6; ++contadorSegmentos) {
 if (modelo == "ânodo comum") {
 // displaySeteSeg[linha][coluna]
 digitalWrite(pino, !displaySeteSeg[digito][contadorSegmentos]);
 } else {
 digitalWrite(pino, displaySeteSeg[digito][contadorSegmentos]);
 }
 pino++; /* Incrementa o valor do pino (vai de 7 a 13). */
 }
 delay(1000); /* Aguarda 1 segundo para reiniciar a contagem. */
}

/* Baixe a biblioteca através do link abaixo */
/* */
/* http://librarymanager/All#TM1637#I2C-Like */
/* */
/***************************************************/
/* Inclui a biblioteca de controle do display. */
#include <TM1637Display.h>
/* Cria a variável para armazenar a contagem. */
int contador;
/* Definições dos pinos utilizados. O módulo aceita*/
/* pinos analógicos e digitais. */
#define CLK A4
#define DIO A5
/* Definição dos pinos de controle dos LEDs do */
/* semáforo. */
#define Verde_Carros 2
#define Amarelo_Carros 3
#define Vermelho_Carros 4
#define Verde_Pedestres 5
#define Vermelho_Pedestres 6

/* Definição do pino de controle do botão. */
#define botao 1
/* Cria o objeto de controle para o display */
/* mencionando os pinos utilizados do Arduino. */
TM1637Display display(CLK, DIO);
/* Início das configurações. */
void setup() {
 /* Define o brilho do display (0 a 15). */
 display.setBrightness(15);
 /* Garantimos que o display inicie desligado. */
 display.clear();
 /* Definimos o pino do botão como entrada. */
 pinMode(botao, INPUT);
 /* Definimos os pinos dos LEDs como saídas. */
 pinMode(Verde_Carros, OUTPUT);
 pinMode(Amarelo_Carros, OUTPUT);
 pinMode(Vermelho_Carros, OUTPUT);
 pinMode(Verde_Pedestres, OUTPUT);
 pinMode(Vermelho_Pedestres, OUTPUT);
}/* Fim das configurações. */
/* Início do looping infinito. */
void loop() {
 /* Se o botão for pressionado, faça... */
 if (digitalRead(botao) == 0) {
 /* Aguarda 2 segundos. */
 delay(2000);
 /* Desliga o LED Verde dos carros. */
 digitalWrite(Verde_Carros, 0);
 /* Liga o LED Amarelo dos carros. */
 digitalWrite(Amarelo_Carros, 1);
 /* Aguarda 5 segundos. */
 delay(5000);
 /* Inicia o contador em 15 segundos. */
 contador = 15;
 /* Inicia a contagem até 15. */
 for (int count = 0; count < 16; count++) {
     
 /* Se o contador for maior que 5, faça... */
 if (contador > 5) {
 /* Desliga o LED Amarelo dos carros. */
 digitalWrite(Amarelo_Carros, 0);
 /* Liga o LED Vermelho dos carros. */
 digitalWrite(Vermelho_Carros, 1);
 /* Liga o LED Verde dos pedestres. */
 digitalWrite(Verde_Pedestres, 1);
 /* Desliga o LED Vermelho dos pedestres. */
 digitalWrite(Vermelho_Pedestres, 0);
 /* Se o contador não for maior que 5, então*/
 /* inicia a sequência que faz o LED */
 /* Vermelho dos pedestres piscar, indicando*/
 /* o fim do tempo de travessia. */
 } else {
 /* Desliga o LED Verde dos pedestres. */
 digitalWrite(Verde_Pedestres, 0);
 if (fmod(contador, 2) == 0) {
 /* Desliga o LED Vermelho dos pedestres. */
 digitalWrite(Vermelho_Pedestres, 0);
 } else {
 /* Liga o LED Vermelho dos pedestres. */
 digitalWrite(Vermelho_Pedestres, 1);
 }
 }
 /* Mostra no display o tempo restante de */
 /* travessia, sem os zeros à esquerda do */
 /* número. */
 display.showNumberDec(contador, false);
 /* Após, decrementa 1 do tempo restante. */
 contador += -1;
 /* Espera 1 segundo para atualizar o contador*/
 delay(1000);
 }
 /* Limpa o display. */
 display.clear();
     
 /* Se o botão não for pressionado, mantenha os */
 /* LEDs da seguinte forma: */
 } else {
 /* Liga o LED Verde dos carros. */
 digitalWrite(Verde_Carros, 1);
 /* Desliga o LED Amarelo dos carros. */
 digitalWrite(Amarelo_Carros, 0);
 /* Desliga o LED Vermelho dos carros. */
 digitalWrite(Vermelho_Carros, 0);
 /* Desliga o LED Verde dos pedestres. */
 digitalWrite(Verde_Pedestres, 0);
 /* Liga o LED Vermelho dos pedestres. */
 digitalWrite(Vermelho_Pedestres, 1);
 }
}/* Fim do looping infinito. 