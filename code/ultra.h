#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void ultra_int();

void ultra_int()
{
  DDRD|=(1<<PIND0);
  DDRD&=~(1<<PIND1);
  PORTD |=(1<<PD2);         // active the internal resistor of pd2
  PORTD|=(1<<PD1);                     // make high pulse for triggering the sensor with signal width 10us
  _delay_us(10);
  MCUCR |=(1<<ISC01) | (1<<ISC11);    //adjust the interrupt signals to work at isc00 at zero and isc01 at 1 so at any logical change
  GICR |=(1<<INT0);                   //active interrupt at echo high
  sei();
  _delay_ms(100);                      //  finishing word of interrupt code and called the ISR function
}
ISR (INT0_vect)
{
  PORTC|=(1<<PC0);
}

