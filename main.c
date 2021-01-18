/*


L4- Interconectare PC si XMC4700 Relax kit.

Program afisare continua date A/D in virgula flota pe Terminal.

Intefata seriala peste DEBUG utilizeaza  P1.5 pentru Tx si P1.4 pentru Rx.

Convertorul A/D este configurat sa genereze intrupere la sfarsit
conversie, rutina de tratare fiind denumita adch.
Timpul de conversiei pe 12 biti este de aprox 1,5 microsecunde.
La intrarea P14.9 este conectat cursorul unui potentiometru conectat intre 3,3V si GND.
In acest mod pot fi generate tensiuni specifice unor senzori cu iesiri analogice.

! In etapa de generare proiect se vor activa optiunile pentru virgula flotanta a
functiei printf - altfel nu e posibila afisare, desi nu sunt erori la compilare.

*/

#include <DAVE.h>
#include<stdio.h>

float analog;                 // rezultat conversie AD

void adch()                   // rutina tratare intrerupere sfarsit conversie
{

analog = ADC_MEASUREMENT_GetResult(&ADC_MEASUREMENT_Channel_A);// lectura data

}

void delay(int j)
{
	for (int i=0;i<0xfff*j;i++); // temporizare
}


int main(void)
{
  char ad_float[6];           // bufer date convertor A/D
  float x;	// valoarea tensiunii de la intrare in volti

  DAVE_Init();		          // initializare DAVE
  ADC_MEASUREMENT_Init(&ADC_MEASUREMENT_0); // este inclusa si in DAVE_Init()
  while(1U)
  {
	ADC_MEASUREMENT_StartConversion(&ADC_MEASUREMENT_0);   // start conversie

	delay(1);                            // optional
    x=3.3*analog/4096;                       // conversie in volti
    sprintf(ad_float, "%1.4f", x);           // conversie in ASCII
    //sprintf(ad_float, "%1.4f", analog);    // vizualizare directa

    UART_Transmit(&UART_0, ad_float, sizeof(ad_float));// afisare tensiune

    if(!UART_IsTxBusy(&UART_0))        // liber transmisie
    UART_TransmitWord(&UART_0,'\r');   // inceput linie
    if(!UART_IsTxBusy(&UART_0))
    UART_TransmitWord(&UART_0,'\n');   // linie noua

    delay(400);

	}

  return 0;
}
