#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//Prepare LED pin
void PortInit(void)
{
	//Initially LED OFF
	PORTD &= ~(1<<PD0);
	PORTD |= (1<<PD1);
	//PD0 as output
	DDRD |= (1<<PD0);
	DDRD |= (1<<PD1);
}

//Timer2 init acording datasheet
void RTCInit(void)
{
	//Disable timer2 interrupts
	TIMSK2 = 0;
	//Enable asynchronous mode
	//ASSR = (1<<AS2);
	//set initial counter value
	TCNT2 = 0;
	//set prescaller 128
	TCCR2B |= (1<<CS22)|(1<<CS00);
	//wait for registers update
	//while (ASSR & ((1<<TCN2UB)|(1<<TCR2BUB)));
	//clear interrupt flags
	TIFR2 = (1<<TOV2);
	//enable TOV2 interrupt
	TIMSK2 = (1<<TOIE2);
}

//Overflow ISR
ISR(TIMER2_OVF_vect)
{
	//Toggle pin PD0 every second
	PIND = (1<<PD1);
	PORTD |= (1<<PD0);
	asm volatile("nop"::);
	//_delay_us(10)
}

int main (void)
{
	SMCR |= (1<<SM1)|(1<<SM0);
	//Initialize port
	PortInit();
	//Initialise the timer2
	RTCInit();
	//Enable global interrupts
	PIND = (1<<PD1);
	sei();
	while(1)
	{
		//SMCR |= (1<<SE);
		//asm volatile("sleep"::);
		//SMCR &= ~(1<<SE);
		//Do nothing

	}
}
