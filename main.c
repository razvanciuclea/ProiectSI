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
