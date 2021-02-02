/*
 * embedded_proj.c
 *
 * Created: 08-Dec-17 5:00:13 PM
 * Author : E_AHMED UWK
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ADC.h"
#include "ultra.h"

void pir_sensor();
uint8_t LDR1;       //store for values of ldr1
uint8_t LDR2;      //store for values of ldr1

int main(void)
{
    /* Replace with your application code */	
	DDRA=0x00;             // port a for input PIR sensor  
	DDRC=0x0f;            // make port c output for relay
	DDRD|=(1<<PD1);           // make PD2 in for interrept 
	DDRD&=~(1<<PD2);
	DDRD&=~(1<<PD3);
	//DDRD=0x02;
	PORTD|=(1<<PD2)|(1<<PD3);   //ACTIVE THE PULL UP RESISTOR 
	MCUCR |=(1<<ISC10);        //adjust the interrupt to work at ant RIASING EDEGE
	GICR |=(1<<INT1);      //active interrupt at INT1
	sei();                //calling tge ISR function
	ADC_int();
	while (1) 
    {
	LDR1=LDR1_value(LDR1);
    LDR1=(LDR1*5)/255;                        //convert the value from digital to analog using referense volt
	LDR2=LDR2_value(LDR2);
	LDR2=(LDR2*5)/255;                        //convert the value from digital to analog using referense volt
	if (LDR1<2)
	   {
	   ultra_int();       //active the ultrasonic sensor and active the lamp at near objects
	   _delay_ms(500);
	   }
	   else
	   {
	   PORTC&=~(1<<PC0);  //shutdown the lamp at day light at out side
	   //_delay_ms(500);
	   }
	   if (LDR2<2)
	   {
	   pir_sensor();
	   _delay_ms(500);
	   }
	   else
	   {
	   PORTC&=~(1<<PC1);
	   }
    }
}

ISR(INT1_vect)
{
PORTC=0x03;
//while((PORTD))
}
void pir_sensor()
{
	if (PINA &(1<<PA4))
	{
		PORTC|=(1<<PC1);
		_delay_ms(500);
		//LDR2=0;
	}
	else
	{
		PORTC&=~(1<<PC1);
	}
}