/*
 * This code will flash the green LED if the button is pressed,
 * and if the time of press is long enough, it will change to flash the red LED.
 * If the button isn't pressed, the two LEDs neither flash.
 */

#include <msp430.h>
#define LED1 BIT0   //P1.0 to red LED
#define B1 BIT3     //P1.3 to button
#define LED2 BIT6

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
  P1OUT |= B1;
  P1DIR = LED1 + LED2; //Set pin with LED1 to output
  P1REN = B1;   //Set pin to use pull-up resistor
  volatile unsigned int delay, count;
  for(;;)
  {   //Loop forever
    if((P1IN & B1) ==0) //Is button down?
    {
    	count = 0;
    	while((P1IN & B1)==0)
    	{
    		count++;
    		if(count>10)
    		{
    			P1OUT &= ~LED2;
    			P1OUT ^= LED1;
    		}
    		else P1OUT ^= LED2;
    		delay = 50000;
    		do (delay--);
    		while (delay != 0);
    	}
	}
    else
    {
    	P1OUT &= ~LED1;
    	P1OUT &= ~LED2;
    }
  }
}
