/*
 * main.c
 *
 *  Created on: 23 Sep 2020
 *      Author: Heba_Tharwat
 */


#include "adc.h"
#include "lcd.h"

void motor_init(void){
	DDRB|= 0x03;
	PORTB &= 0xFC;
}

void motor_direction(uint8 dir){

	if(dir==0)
			{

				PORTB |= (1<<PB0);
				PORTB &= (~(1<<PB1));
			}


			else
			{
				PORTB &= (~(1<<PB0));
				PORTB |= (1<<PB1);
			}
}




void INT0_init(void){
	SREG&=~(1<<7);
	DDRD&= ~(1<<PD2);
	GICR|=(1<<INT0);
	MCUCR|=(1<<ISC00)|(1<<ISC01);
	SREG|=(1<<7);
}

ISR(INT0_vect)
{
					PORTB ^= ((1<<PB0));
					PORTB ^= (1<<PB1);
}


void timer0_init_PWM_mode(unsigned char tick)
{
	TCNT0 = 0;
	OCR0  = tick;
	DDRB |=(1<<PB3);
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}


int main(void)
{
	uint16 res_value;
	LCD_init();
	ADC_init();
   motor_init();
   INT0_init();
	LCD_clearScreen();
	LCD_displayString("ADC Value = ");
    motor_direction(0);

    while(1)
    {
    	LCD_goToRowColumn(0,12);
    	res_value = ADC_readChannel(0);
    	LCD_intgerToString(res_value);
        timer0_init_PWM_mode(res_value);
   _delay_ms(100);
    }
}
