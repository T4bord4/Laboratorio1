/*
  Sistemas Embarcados - Laboratório 1
  
  Aluno: Matheus Taborda Carneiro

  Apos o programa ser ajustado para que o LED D4 pisque na frequência de 1Hz com
  clock de 24MHz e otimização LOW, foi trocado o modo de otimização do compilador,
  para NONE, MEDIUM e HIGH.
  Em NONE, foi observado que a frequência se tornava menor com o tempo entre as piscadas 
  aumentado em alguns décimos de segundo, portanto foi diminuido as repetições dos laços,
  enquanto em MEDIUM foi notado que a frequência se tornou maior, diminuindo em alguns 
  décimos de segundo o período, requerindo que os laços fossem aumentados.
  Já com otimização em HIGH, perdeu-se o controle da frequência, por habilitar a
  otimização de loop unrolling.
  Ao aumentar a frequência do clock foi observado um aumento de frequência de
  3,5 vezes no LED D4 em comparação com o clock anterior
*/
#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#define DELAY_NONE_24MHz        1540000
#define DELAY_LOW_24MHz         1600000
#define DELAY_MEDIUM_24MHz      2800000
#define DELAY_HIGH_24MHz        1600000000

#define DELAY_NONE_120MHz       5390000
#define DELAY_LOW_120MHz        5600000
#define DELAY_MEDIUM_120MHz     14000000
#define DELAY_HIGH_120MHz       1600000000

uint8_t LED_D1 = 0;

void SysTick_Handler(void){
  LED_D1 ^= GPIO_PIN_1; // Troca estado do LED D1
  GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, LED_D1); // Acende ou apaga LED D1
} // SysTick_Handler

void main(void){
  SysTickPeriodSet(16000000); // f = 1Hz para clock = 24MHz

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D3 = PF4, LED D4 = PF0)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)); // Aguarda final da habilitação
    
  GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como saída
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
  GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

  while(1){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); // Apaga LED D4
    for(int i = 0; i < DELAY_LOW_120MHz; i++)
    {
  
    }// for
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // Acende LED D4
    for(int i = 0; i < DELAY_LOW_120MHz; i++)
    {
  
    }// for
  } // while
} // main