#include <avr/io.h>
#include <avr/interrupt.h>

void ADC_int()
{
 DDRA=0x00;
 ADCSRA |=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1);  //make adc enable and adjust the prescaller 8 at clock 1MHZ/8=125 khz
 ADMUX |=(1<<MUX0)|(1<<MUX1);     // enable adc at PA1 PA2 PA4
 ADMUX |=(1<<ADLAR);                          // use mode of 8bit for storing at ADCH only 
}

int LDR1_value(uint8_t LDR1)
{
  ADMUX |=(1<<MUX0);                            // ENABLE THE ADC1 AT PA1
  ADMUX |=(1<<ADLAR);                          // use mode of 8bit for storing at ADCH only
  ADCSRA|=(1<<ADSC);                      //start the conversion operation 
  while(ADCSRA & (1<<ADSC));              //poling loop waiting till the conversion finish
  LDR1=ADCH;
  LDR1=(LDR1*5)/255;                        //convert the value from digital to analog using referense volt
  return(LDR1)
}

int LDR2_value(uint8_t LDR2)
{
	ADMUX |=(1<<MUX2);                            // ENABLE THE ADC2 AT PA2
	ADMUX |=(1<<ADLAR);                          // use mode of 8bit for storing at ADCH only
	ADCSRA|=(1<<ADSC);                      //start the conversion operation
	while(ADCSRA & (1<<ADSC));              //poling loop waiting till the conversion finish
	LDR2=ADCH;                               // store the value at register as digital 8bit 
	LDR2=(LDR2*5)/255;                        //convert the value from digital to analog using referense volt

	return(LDR2)
}
