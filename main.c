

#include <msp430.h> 
#include "CC1101.h"
#include "Pinouts.h"
#include "Registers.h"
#include "debug.h"
#include <stdint.h>
#include <Timer0_A3.h>
#include <Timer1_A3.h>
#include <GPIO.h>
#include <main.h>
#include <USCI.h>
#include <BasicClockSystem.h>
#include <time.h>



/*
 * main.cpp
 */

/* TODO:
 * - P1.0: LED1 (red)
 * - P1.1: UC0ARXD (input)
 * - P1.2: UCA0TXD (output)
 * - P1.3: SW2 (pushbutton)
 * - P1.4: LED2 (green); Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P1.5: UCB0CLK (SPI/CLK)
 * - P1.6: UCB0SOMI (SPI/GDO1/MISO)
 * - P1.7: UCB0SIMO (SPI/MOSI)
 * - P2.0: TA1.0 (buzzer)
 * - P2.1: Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P2.2: (SPI/CSn)
 * - P2.3: (GDO0)
 * - P2.4: (GDO2)
 * - P2.5: Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P2.6: 32.768kHz Crystal
 * - P2.7: 32.768kHz Crystal
*/

#define SW2FLAG 		(0x01)			//flag for SW2 being pressed
#define GDO0FLAG		(0x02)			//flag for GDO0 (running in nIRQ mode) pin going low
#define RESET_MESSAGE	("RESET\r\n")
#define LED2_TOGGLE		(LED2_PxOUT ^= LED2_PIN)
#define LED2_ON			(LED2_PxOUT |= LED2_PIN)
#define LED2_OFF		(LED2_PxOUT &= ~LED2_PIN)

char txBuffer[4];
char rxBuffer[4];
unsigned char FLAGS = 0;   //char to hold flags generated by ISR
unsigned char periodicTXFlag = 0;
unsigned int i;
char string[] = RESET_MESSAGE;
time_t currentTime;

enum {
	STATE_UNUSED,
	STATE_IDLE,
	STATE_TRANSMIT,
	STATE_RECEIVE
};

uint8_t volatile STATE = STATE_IDLE;	// Default state is STATE_IDLE


void One_Shot (void);
void periodicTX (void);
void LEDShutdown (void);
void TA0CCR1_ISR_Handler (void);
void APP_GPIO_init (void);
void APP_POST (void);
void SW2_callback (void);
void GDO0_callback (void);


void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    gpio_port1_init();
    gpio_port2_init();
    APP_GPIO_init();
    BCS_init();

    USCI_A0_init_UART(9600, USCI_A0_CLK_SRC_SMCLK);

	GPIO_PORT1_registerCallback(SW2_PIN_NUM, &SW2_callback, LPM_NO_EXIT);		// Should toggle the LED when the button is pressed.
	GPIO_PORT2_registerCallback(GDO0_PIN_NUM, &GDO0_callback, LPM0_bits);
	//Timer0_A1_registerCallback (1, &TA0CCR1_ISR_Handler);
	Timer0_A3_registerCallback (TA0CC0, &periodicTX, LPM0_bits);
	Timer0_A3_registerCallback (TA0CC1, &LEDShutdown, LPM_NO_EXIT);
    Timer0_A3_init();			// Used for event scheduling
    Timer1_A3_init();			// Used for buzzer

    APP_POST();					// Last step before setting CC1101 to receive data
    CC1101_init();				// Initialize CC1101
    CC1101_setReceive();		// Set CC1101 to receive data

	GDO0_PxIFG &= ~GDO0_PIN;

	while(1)
	{
	    switch(STATE)
		{
			case STATE_IDLE:				// this is the idle state
			{
				__bis_SR_register(LPM0_bits + GIE);

				if (FLAGS & GDO0FLAG)
				{
					STATE = STATE_RECEIVE;
					FLAGS &= ~GDO0FLAG;
				}

				break;
			}

			case STATE_TRANSMIT:
			{
				//temporarily disable GDO0 interrupt
				GDO0_PxIE &= ~GDO0_PIN;

				char size = 3;				// this is the size of the entire packet being sent, including the size byte
				txBuffer[0] = 2;			// this is the size byte (it lets the receiver know how many bytes are following)
				txBuffer[1] = 0x01;			// first byte
				txBuffer[2] = 0xAA;			// second byte
				CC1101_sendPacket(txBuffer, size);
				STATE = STATE_IDLE;			// return to IDLE state
				GDO0_PxIFG &= ~GDO0_PIN;	// Clear flag
				GDO0_PxIE |= GDO0_PIN;		// Enable int on end of packet
				FLAGS = 0;					// clear flag buffer
				SW2_PxIFG &= ~SW2_PIN;		// Ensure SW2 interrupt flag is clear
				SW2_PxIE |= SW2_PIN;		// Re-enable SW2 interrupt
				break;
			}

			case STATE_RECEIVE:
			{
				//temporarily disable GDO0 interrupt
				GDO0_PxIE &= ~GDO0_PIN;
				char len = 4;

				if(CC1101_receivePacket(rxBuffer, &len))
				{
					short s = CC1101_getRSSI();
					LED1_PxOUT ^= LED1_PIN;
					CC1101_setReceive();
				}

				else
				{
					//CRC did not check out or buffer was too small to hold received packet
					_NOP();		// For setting breakpoint
				}

				STATE = STATE_IDLE;				// return to idle state
				GDO0_PxIFG &= ~GDO0_PIN;		// Clear flag
				GDO0_PxIE |= GDO0_PIN;			// Enable int on end of packet
				FLAGS = 0;						// clear flag buffer
				break;
			}

			default:
			{
				STATE = STATE_IDLE;				// return to IDLE state
				break;
			}
		}
	}
}


void One_Shot (void)
{
	//GPIO_PORT1.interrupt_enable &= ~SW2_PIN;	// Disable interrupt
	//Timer0_armOneShot(25000, 1);				// Should cause a 200mS blink

	// TODO:
	// - replace with a function call to Timer1_A3 library
	//TA1CCR0 = 121;								// Set compare 0 register to set frequency

	// TODO: Merge below code into code above
}


void SW2_callback (void)
{
	periodicTXFlag ^= SW2FLAG;
	if(periodicTXFlag & SW2FLAG)
	{
		TIMER0_A3_Stop;								// Clear Timer mode bits
		TIMER0_A3_SetCountMode(MC_1);				// Start Timer in "Up" mode
	}

	else
	{
		TIMER0_A3_Stop;
		STATE = STATE_IDLE;
	}

	//LED1_PxOUT |= LED1_PIN; 				// Turn on LED1
    if(!USCI_A0_UART_read_busy_flag())
    {
    	USCI_A0_UART_write_TX_buffer('S');
    }
}


void GDO0_callback (void)
{
	FLAGS |= GDO0FLAG;
	//LED1_PxOUT &= ~LED1_PIN; 				// Turn off LED1
    if(!USCI_A0_UART_read_busy_flag())
    {
    	USCI_A0_UART_write_TX_buffer('G');
    }
}


void periodicTX (void)
{
	uint16_t CC_val;

	STATE = STATE_TRANSMIT;						// Will cause a transmit
	CC_val = 1638;								// 3276 should yield a 100mS duration
	TIMER0_A3_SetCaptureCompare(TA0CC1, CC_val);
	TIMER0_A3_EnableCCInterrupt(TA0CC1);
	LED2_ON;

	TIMER0_A3_ClearCCInterruptFlag(TA0CC1);
	//LED2_TOGGLE;
	// TODO:
	// - Put software timer tick here
	// - Check software timer for scheduled events here
	// - Put periodic transmit here
}


void LEDShutdown (void)
{
	TIMER0_A3_DisableCCInterrupt(TA0CC1);
	LED2_OFF;
}


void TA0CCR1_ISR_Handler (void)
{
	//GPIO_PORT1.interrupt_enable |= SW2_PIN;		// Enable P1.3 pin interrupt
	//TA0CCTL1 &= ~CCIE;							// Disable TA0CCR1 interrupt

	// TODO:
	// - replace with a function call to Timer1_A3 library
	//TA1CCR0 = 0;								// Set compare 0 register to turn off tone
}


void APP_GPIO_init (void)
{
	SW2_PxOUT = SW2_PIN;						// Set S2 pin out register for pullup

    // P1.6 is used for SPI, so can't use LED2
	//LED2_PxDIR |= LED2_PIN;						// Set LED pin to output mode
	//LED2_PxSEL = LED2_PIN;						// Select TA0.1 pin function
	//LED2_PxSEL2 = 0;							// Select TA0.1 pin function

	BUZZ_PxDIR = BUZZ_PIN;						// Set buzzer pin to output mode
	BUZZ_PxSEL = BUZZ_PIN;						// Select TA1.0
	BUZZ_PxSEL2 = 0;

    //Configure ports -- switch inputs, LEDs, GDO0 to RX packet info from CC1101
    SW2_PxREN |= SW2_PIN;						// enable pullup/pulldown resistor
    SW2_PxOUT |= SW2_PIN;						// pullup the resistor
    SW2_PxDIR &= ~SW2_PIN;						// set direction as input
    SW2_PxIES |= SW2_PIN;						// Int on falling edge
    SW2_PxIFG &= ~(SW2_PIN);					// Clr flags
    SW2_PxIE = SW2_PIN;							// Activate enables

    LED1_PxDIR |= LED1_PIN;						// set led1 to output

    // P1.6 is used for SPI, so remap LED2 to P1.4 via jumper
    LED2_PxDIR |= LED2_PIN;						// set led1 to output

    GDO0_PxIES |= GDO0_PIN;						// Int on falling edge (end of pkt)
    GDO0_PxREN |= GDO0_PIN;						// enable pullup/pulldown resistor
    GDO0_PxOUT |= GDO0_PIN;						// now pull resistor up
    GDO0_PxIFG &= ~GDO0_PIN;					// Clear flag
    GDO0_PxIE |= GDO0_PIN;						// Enable int on end of packet
}


void APP_POST (void)
{
    volatile uint16_t delayCount;
    volatile uint16_t toggleCount;
    volatile char * pString;

    TA1CCR0 = 121;								// Set compare 0 register to start tone

    pString = string;

    while(*pString)
    {
       	USCI_A0_UART_write_TX_buffer(*pString);			// Send reset message
       	while(!USCI_A0_UART_get_TX_int_flag());
       	pString++;
    }

    LED1_PxOUT &= ~LED1_PIN; 					// Set LED1 off

    for(toggleCount = 0; toggleCount < 8; toggleCount++)
    {
		LED1_PxOUT ^= LED1_PIN; 				// Toggle LED1
		for(delayCount = 0; delayCount < 10000; delayCount++);
    }

    TA1CCR0 = 0;								// Clear compare 0 register to stop tone
}

