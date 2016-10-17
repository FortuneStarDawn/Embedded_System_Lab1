/*
 * This code will flash the red LED first,
 * and once the button is pressed, it will change to flash the green LED.
 * Every time the button is pressed, it will change the color of LED to flash.
 */

#include <msp430.h>
#define LED1 BIT0   //P1.0 to red LED
#define B1 BIT3     //P1.3 to button
#define LED2 BIT6

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD; //Stop watchdog timer
  P1OUT |= LED1 + B1;
  P1DIR = LED1 + LED2; //Set pin with LED1 to output
  P1REN = B1;   //Set pin to use pull-up resistor
  volatile unsigned int down, color, i, delay;
  down=0;
  color=0;
  for(;;)
  {   //Loop forever
    if((P1IN & B1) ==0) //Is button down?
    {
    	down=1;
	}
    else
    {
    	if(down==1)
    	{
    		if(color==0)
    		{
    			P1OUT &= ~LED1;
    			color = 1;
    		}
    		else
    		{
    			P1OUT &= ~LED2;
    			color = 0;
    		}
    		down = 0;
    		i = P1IN;
    	}
    }
	if(color==0)
	{
		P1OUT ^= LED1;
	}
	else
	{
		P1OUT ^= LED2;
	}
	delay = 50000;
	do (delay--);
	while (delay != 0);
  }
}
