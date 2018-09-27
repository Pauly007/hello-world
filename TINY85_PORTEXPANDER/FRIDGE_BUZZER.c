/*
 * FRIDGE_BUZZER.c
 *
 * Created: 03.11.2012 14:47:32
 *  Author: paul van dirk
 */ 

#include <avr/io.h>
#define F_CPU 8000000ul
#include <util/delay.h>
#include <avr/interrupt.h>


#define BUZZ_PORT	PORTB
#define BUZZ_DDR	DDRB
#define BUZZ_PIN	4

#define LED_PORT	PORTB
#define LED_DDR		DDRB
#define LED_PIN		3



void init_TIMER0( void )
{
	TCCR0A = 0x02; // CTC (clear timer on compare match) mode only WGM01 is set --> TOP = OCRA, TOV=0xFF (overflow)
	TCCR0B = 0x03; // CS01 + CS00 is set prescaler = 64 --> F_CPU/64 = 125 kHz
	OCR0A = 125; // --> 1 kHz --> 1ms timebase for output compare interrupt
	TIMSK = 0x10; // Output compare match A interrupt enable is set
}



volatile unsigned char tb_1000ms_flag = 0 , tb_10ms_flag = 0;
volatile unsigned int tic_time_1000ms = 0 , tic_time_10ms = 0;


// ISR is executed every 1ms 
ISR(TIMER0_COMPA_vect)
{
	
	if( !tb_1000ms_flag )tic_time_1000ms++;
	if ( tic_time_1000ms > 1000 )
	{
		tb_1000ms_flag = 1;
	}

	
}

void init_IO(void)
{
	LED_DDR |= ( 1 << LED_PIN );
	BUZZ_DDR |= ( 1 << BUZZ_PIN );
}


void custom_delay( unsigned int delay )
{
	unsigned int cnt;
	
	for ( cnt = 0 ; cnt < delay ; cnt++ )
	{
		//_delay_us( 1 );
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
	}
	
	
}



void play_note( unsigned char note , unsigned char note_num , unsigned int duration_ms )
{
	unsigned int cnt, loops, delay_time=1000;
	// calculation: 300 * 1885/ desired frq = delay_time
	switch( note_num )
	{
		case 1:
		switch( note )
		{

			case 'h':
			delay_time = 1145; // 493.9 Hz
			break;
			case 'a':
			delay_time = 1285; // 440 Hz
			break;
			case 'g':
			delay_time = 1443; // 392.0 Hz
			break;
			case 'f':
			delay_time = 1619; // 349.2 Hz
			break;
			case 'e':
			delay_time = 1716; // 329.6 Hz
			break;
			case 'd':
			delay_time = 1925; // 293.7 Hz
			break;
			case 'c':
			delay_time = 2162; // 261.6 Hz
			break;
				
		}
		break;
			
			
	}

	loops = (unsigned int)( (double)duration_ms / ( (double)delay_time / 1000.0 ) );
		
	for ( cnt = 0 ; cnt < loops ; cnt++ )
	{
			
		custom_delay( delay_time );
			
		BUZZ_PORT ^= ( 1 << BUZZ_PIN );
			
	}

}



void haenschen_klein(void)
{
	unsigned int takt = 300;
	unsigned int pause = 65000;
	
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'f' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'c' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'f' , 1 , takt );
	custom_delay(pause);
	
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , 2*takt );
	custom_delay(pause);
	
	
	
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'f' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'c' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	
	play_note( 'c' , 1 , 4*takt );
	custom_delay(pause);
	
	
	
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'f' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'f' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , 2*takt );
	custom_delay(pause);
	
	
	
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'f' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , takt );
	custom_delay(pause);
	play_note( 'd' , 1 , 2*takt );
	custom_delay(pause);
	
	play_note( 'c' , 1 , takt );
	custom_delay(pause);
	play_note( 'e' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	play_note( 'g' , 1 , takt );
	custom_delay(pause);
	
	play_note( 'c' , 1 , 4*takt );
	custom_delay(pause);
}

int main(void)
{
	init_IO();
	init_TIMER0();
	sei();
	
	unsigned int time = 0, treshold1 = 15, increment = 2, treshold2 = 45;
	unsigned int duration = 200;
	unsigned char lock1 = 0, lock2 = 0, lock3 = 0, lock4 = 0, lock5 = 0, lock6 = 0, lock7 = 0, lock8 = 0;
	
    while(1)
	{
		
		if( tb_1000ms_flag )
		{
			
			//LED_PORT ^= ( 1 << LED_PIN );
			time++;
			tic_time_1000ms = 0;
			tb_1000ms_flag=0;
			
			
		}
		
		
		if ( !lock1 && ( time == ( treshold1 + increment * 0 ) ) )
		{
			play_note( 'c' , 1 , duration );
			lock1 = 1;
		}
		
		if ( !lock2 && ( time == ( treshold1 + increment * 1 ) ) )
		{
			play_note( 'd' , 1 , duration );
			lock2 = 1;
		}
		
		if ( !lock3 && ( time == ( treshold1 + increment * 2 ) ) )
		{
			play_note( 'e' , 1 , duration );
			lock3 = 1;
		}
		
		if ( !lock4 && ( time == ( treshold1 + increment * 3 ) ) )
		{
			play_note( 'f' , 1 , duration );
			lock4 = 1;
		}
		
		if ( !lock5 && ( time == ( treshold1 + increment * 4 ) ) )
		{
			play_note( 'g' , 1 , duration );
			lock5 = 1;
		}
		
		if ( !lock6 && ( time == ( treshold1 + increment * 5 ) ) )
		{
			play_note( 'a' , 1 , duration );
			lock6 = 1;
		}
		
		if ( !lock7 && ( time == ( treshold1 + increment * 6 ) ) )
		{
			play_note( 'h' , 1 , duration );
			lock7 = 1;
		}
		
		
		if ( !lock8 && ( time == treshold2 ) )
		{
			haenschen_klein();
			lock8 = 1;
		}
		
		
       	
    }
}