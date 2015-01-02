#include "CC1101.h"
#include "SPI.h"
#include "Pinouts.h"
#include "Registers.h"


void CC1101_writeSettings(void);


//this function initializes both the cc1101 and the MSP430
void CC1101_init(void)
{
	SPI_setup();			//configure SPI
	SPI_wait(5000);			//wait for CC1101 power-on reset
	CC1101_powerupReset();	//Reset CC1101
	CC1101_writeSettings();	//Send configuration commands
}

void CC1101_powerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  SPI_wait(45);
  CSn_PxOUT &= ~CSn_PIN;
  SPI_wait(45);
  CSn_PxOUT |= CSn_PIN;
  SPI_wait(45);

  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = SRES;               			// Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         			// /CS disable
  while (SPI_USCIB0_PxIN & SPI_USCIB0_SOMI);// CAS: Wait for SO to go low (see section 10.4 on pg 32)
}

//
void CC1101_sendPacket(char *txBuffer, char size)
{
	SPI_writeBurstReg(TXFIFO, txBuffer, size); // Write TX data
	SPI_strobe(STX);           				// Change state to TX, initiating
                                            // data transfer

	while (!(GDO0_PxIN & GDO0_PIN));
											// Wait GDO0 to go hi -> sync TX'ed
	while (GDO0_PxIN & GDO0_PIN);
											// Wait GDO0 to clear -> end of pkt
	GDO0_PxIFG &= ~GDO0_PIN;      			// After pkt TX, this flag is set.
											// Has to be cleared before existing
	SPI_strobe(SIDLE);
}

char CC1101_receivePacket(char *rxBuffer, char *length)
{
  char status[2];
  char pktLen;
  char returnval = 0;

  if ((SPI_readStatus(RXBYTES) & NUM_RXBYTES))
  {
    pktLen = SPI_readReg(RXFIFO); 			// Read length byte

    if (pktLen <= *length)                  // If pktLen size <= rxBuffer
    {
      SPI_readBurstReg(RXFIFO, rxBuffer, pktLen); // Pull data
      *length = pktLen;                     // Return the actual size
      SPI_readBurstReg(RXFIFO, status, 2);
                                            // Read appended status bytes
      returnval = (char)(status[LQI_RX] & CRC_OK);
    }                                       // Return CRC_OK bit
    else
    {
      *length = pktLen;                     // Return read size
      SPI_strobe(SFRX);      				// Flush RXFIFO
    }
  }

      return returnval;							//1 = good, 0 = bad
}

char CC1101_pollReceiveFlag(void)
{
	char returnval = 0;
	if(GDO0_PIN & GDO0_PxIN)
	{
		while(GDO0_PIN & GDO0_PxIN){}
		returnval = 1;
	}
	return returnval;
}

void CC1101_setReceive(void)
{
	SPI_strobe(SRX);			//put into RX mode
}

void CC1101_setIdle(void)
{
	SPI_strobe(SIDLE);		//put int IDLE mode
}

void CC1101_setSleep(void)
{
	SPI_strobe(SXOFF);		//turn off
}




//Description: This function will get the RSSI from the CC1101 and return it.
//The RSSI value read from the RSSI status register is a 2’s complement number and is in
//dBm with ½ dB resolution. Praise him. (pardon this random Dr. Who reference)
short CC1101_getRSSI(void)
{
	unsigned char RSSI_dec;			//base ten reading
	short RSSI_dBm;			//dbm value
	const char RSSI_offset = 74;
	const unsigned char NEGATIVE = 128;

	//get RSSI
	RSSI_dec = SPI_readStatus(RSSI);
	//if negative, convert to dBm
	if (RSSI_dec >= NEGATIVE)
	{
		RSSI_dBm = (( RSSI_dec - 256) / 2) - RSSI_offset;
	}
	//If positive, convert to dBm
	else
	{
		RSSI_dBm = (RSSI_dec / 2) - RSSI_offset;
	}
	return RSSI_dBm;
}


void CC1101_writeSettings(void)
{
	// Data rate = 1.19948
	// RX filter BW = 58.035714
	// Device address = 0
	// TX power = 0
	// Sync word qualifier mode = 30/32 sync word bits detected
	// CRC autoflush = false
	// Preamble count = 4
	// Deviation = 5.157471
	// Modulated = true
	// CRC enable = true
	// Channel spacing = 199.951172
	// Data format = Normal mode
	// Channel number = 0
	// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word
	// Manchester enable = false
	// Modulation format = GFSK
	// Address config = No address check
	// Packet length = 255
	// Base frequency = 432.999817
	// Carrier frequency = 432.999817
	// PA ramping = false
	// Whitening = true
	// PA table
	//#define PA_TABLE {0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,}
	//
	// Rf settings for CC1101
	//
	SPI_writeReg(IOCFG0,0x06); //GDO0 Output Pin Configuration
	SPI_writeReg(FIFOTHR,0x47);//RX FIFO and TX FIFO Thresholds
	SPI_writeReg(FSCTRL1,0x06);//Frequency Synthesizer Control
	SPI_writeReg(FREQ2,0x10);  //Frequency Control Word, High Byte
	SPI_writeReg(FREQ1,0xA7);  //Frequency Control Word, Middle Byte
	SPI_writeReg(FREQ0,0x62);  //Frequency Control Word, Low Byte
	SPI_writeReg(MDMCFG4,0xF5);//Modem Configuration
	SPI_writeReg(MDMCFG3,0x83);//Modem Configuration
	SPI_writeReg(MDMCFG2,0x13);//Modem Configuration
	SPI_writeReg(DEVIATN,0x15);//Modem Deviation Setting
	SPI_writeReg(MCSM0,0x18);  //Main Radio Control State Machine Configuration
	SPI_writeReg(FOCCFG,0x16); //Frequency Offset Compensation Configuration
	SPI_writeReg(WORCTRL,0xFB);//Wake On Radio Control
	SPI_writeReg(FSCAL3,0xE9); //Frequency Synthesizer Calibration
	SPI_writeReg(FSCAL2,0x2A); //Frequency Synthesizer Calibration
	SPI_writeReg(FSCAL1,0x00); //Frequency Synthesizer Calibration
	SPI_writeReg(FSCAL0,0x1F); //Frequency Synthesizer Calibration
	SPI_writeReg(TEST2,0x81);  //Various Test Settings
	SPI_writeReg(TEST1,0x35);  //Various Test Settings
	SPI_writeReg(TEST0,0x09);  //Various Test Settings

	char PA[] =  {0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	const unsigned char PA_LEN = 8;
	SPI_writeBurstReg(PATABLE, PA, PA_LEN);
}
