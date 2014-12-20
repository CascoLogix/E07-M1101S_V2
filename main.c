#include <msp430.h> 

/*
 * main.cpp
 */

#include "CC1101.h"
#include "Pinouts.h"
#include "Registers.h"
#include "debug.h"
#include <stdint.h>
#include <Timer0_A3.h>
#include <Timer1_A3.h>
#include <GPIO.h>
#include <main.h>


#define SW2FLAG 		0x01			//flag for SW2 being pressed
#define GDO0FLAG		0x02			//flag for GDO0 (running in nIRQ mode) pin going low

#define S2_PIN		3
#define S2_BIT		BIT3
#define LED2_PIN	6
#define LED2_BIT	BIT6

#define BUZZER_PORT	PORT2
#define BUZZER_BIT	BIT0


char txBuffer[4];
char rxBuffer[4];
unsigned char FLAGS = 0;   //char to hold flags generated by ISR

unsigned int i;


void LED2_One_Shot (void);
void TA0CCR1_ISR_Handler (void);


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    gpio_port1_init();
    Timer0_init();
    Timer1_init();

    USCI_A0_init_UART(9600, USCI_A0_CLK_SRC_SMCLK);
    USCI_A0_UART_write_TX_buffer('T');

	GPIO_PORT1.out = S2_BIT;					// Set S2 pin out register for pullup
	GPIO_PORT1.direction = ~S2_BIT;				// Set LED pin to output mode
	GPIO_PORT1.resistor_enable = S2_BIT;		// Enable S2 pin pullup
	GPIO_PORT1.select = LED2_BIT;				// Select TA0.1
	GPIO_PORT1.select_2 = 0;
	GPIO_PORT1.interrupt_edge_select = S2_BIT;	// Set for falling edge
	GPIO_PORT1.interrupt_flag = 0;				// Clear interrupt flags
	GPIO_PORT1.interrupt_enable = S2_BIT;		// Enable interrupt

	GPIO_PORT2.direction = BUZZER_BIT;			// Set buzzer pin to output mode
	GPIO_PORT2.select = BUZZER_BIT;				// Select TA1.0
	GPIO_PORT2.select_2 = 0;

	GPIO_PORT1_registerCallback(S2_PIN, &LED2_One_Shot);		// Should blink the LED when the button is pressed.
	Timer0_A1_registerCallback (1, &TA0CCR1_ISR_Handler);

	UARTInit();					//for debug purposes
    CC1101_init();
    CC1101_setReceive();

    //Configure ports -- switch inputs, LEDs, GDO0 to RX packet info from CC1101
    SW_PxIES = ~SW2;			//Int on falling edge
    SW_PxIFG &= ~(SW2);			//Clr flags
    SW_PxIE = SW2;				//Activate enables
    SW_PxREN |= SW2;			//enable pullup/pulldown resistor
    SW_PxOUT |= SW2;			//pullup the resistor
    LED_PxOUT |= LED1; 			//Set LED1 on
    LED_PxDIR = LED1; 			//set led1 to output
    volatile unsigned int count;
    for(count = 50000; count > 0; count--);
    LED_PxOUT &= ~(LED1); 		//Set LED1 off

    GDO0_PxIES |= GDO0_PIN;       // Int on falling edge (end of pkt)
    GDO0_PxREN |= GDO0_PIN;		  //enable pullup/pulldown resistor
    GDO0_PxOUT |= GDO0_PIN;		  //now pull resistor up
    GDO0_PxIFG &= ~GDO0_PIN;      // Clear flag
    GDO0_PxIE |= GDO0_PIN;        // Enable int on end of packet

    unsigned char STATE = 1;	  //default state is 1

	while(1)
	{
	    switch(STATE)
		{

			case 1:		//this is the idle state
			// __bis_SR_register(LPM3_bits + GIE);
			_EINT();
			LPM0;		// TODO: Change to LPM3?

			 //
			 if(FLAGS & SW2FLAG)
			 {
				 STATE = 2;
				 FLAGS &= ~SW2FLAG;
			 }
			 else if (FLAGS & GDO0FLAG)
			 {
				 STATE = 3;
				 FLAGS &= ~GDO0FLAG;
			 }
				 break;
			case 2:
			{
				//temporarily disable GDO0 interrupt
				GDO0_PxIE &= ~GDO0_PIN;

				char size = 3;			//this is the size of the entire packet being sent, including the size byte
				txBuffer[0] = 2;		//this is the size byte (it lets the receiver know how many bytes are following)
				txBuffer[1] = 0x01;		//first byte
				txBuffer[2] = 0xAA;		//second byte
				CC1101_sendPacket(txBuffer, size);
				STATE = 1;				//return to IDLE state
				GDO0_PxIFG &= ~GDO0_PIN;      // Clear flag
				GDO0_PxIE |= GDO0_PIN;        // Enable int on end of packet
				FLAGS = 0;					//clear flag buffer
				break;
			}
			case 3:
			{
				//temporarily disable GDO0 interrupt
				GDO0_PxIE &= ~GDO0_PIN;
				char len = 4;
				if(CC1101_receivePacket(rxBuffer, &len))
				{
					short s = CC1101_getRSSI();
					LED_PxOUT ^= LED1;
					CC1101_setReceive();
				}
				else
				{
					//CRC did not check out or buffer was too small to hold received packet
				}
				STATE = 1;		//return to idle state
				GDO0_PxIFG &= ~GDO0_PIN;      // Clear flag
				GDO0_PxIE |= GDO0_PIN;        // Enable int on end of packet
				FLAGS = 0;						//clear flag buffer
				break;
			}
		}
	}

	return 0;
}


void LED2_One_Shot (void)
{
	GPIO_PORT1.interrupt_enable &= ~S2_BIT;		// Disable interrupt
	Timer0_armOneShot(25000, 1);				// Should cause a 200mS blink

	// TODO:
	// - replace with a function call to Timer1_A3 library
	TA1CCR0 = 300;								// Set compare 0 register to set frequency
}


void TA0CCR1_ISR_Handler (void)
{
	GPIO_PORT1.interrupt_enable |= S2_BIT;		// Enable P1.3 pin interrupt
	TA0CCTL1 &= ~CCIE;							// Disable TA0CCR1 interrupt

	// TODO:
	// - replace with a function call to Timer1_A3 library
	TA1CCR0 = 0;								// Set compare 0 register to turn off tone
}

