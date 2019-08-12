/***********************************************************************************************
 * Very simple TWI/I2C library for AtMega168 or AtMega328                                       
 *  
 * 2019, Tibor Rojko
 * 
 * pinout:
 * A4 (SDA), A5 (SCL)                                                            
 **********************************************************************************************/

#include <avr/io.h>
#include "twimaster.h"

/*
    Setting the bit rate of TWI interface
    Enable TWI    
*/
void twiInit(void)
{
    TWBR = 0.5 * ( (F_CPU / SCL_FREQ) - 16 );     //Setting the clock rate of I2C interface                        
    TWCR |= ( 1 << TWEN);                         //Enable TWI
}

/*
    When the byte in progress has been transferred across the I2C line, the TWINT flag is set.
    Here, just loop until the transfer’s done.
*/
static void twiWaitForComplete(void)
{
    while (!(TWCR & (1 << TWINT)));            // Wait for TWI interrupt flag setting
                                               // TWINT flag not resetting by hardware!!!
}

/*
    I2C conversation starts by pulling the SDA line low before the clock is started up.
    This is the start signal.
*/
void twiStart(void)
{
    TWCR = ((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));      // Send START Condition
    twiWaitForComplete();                                     //Waiting for conversation
}

/*
    Stop signal is a rising edge with the clock high
*/
void twiStop(void)
{
    TWCR = ((1 << TWEN) | (1 << TWINT) | (1 << TWSTO));     // Send STOP condition
}

//Sending byte to slave
void twiSend(uint8_t data)
{
    TWDR = data;
    TWCR |= ((1 << TWINT) | (1 << TWEN));          //Clear int flag, and set enable flag to send byte
    twiWaitForComplete();                          //Waiting for conversation
}

/*
    After receiving send back ACK, for this use the twiReadWithAck() function, 
    this will sign for slave, that transmission was ok.
    In the end of communication, after the last received byte, use twiReadNoAck(),
    which means for slave, that the transaction will be end.
    Send stop condition (twiStop() function), after reading with NoACK
*/
uint8_t twiReadWithAck(void)
{
    TWCR |= ((1 << TWINT) | (1 << TWEN) | (1 << TWEA));
    twiWaitForComplete();                                //Waiting for conversation
    return(TWDR);
}

uint8_t twiReadNoAck(void)
{
    TWCR |= ((1 << TWINT) | (1 << TWEN));
    twiWaitForComplete();                                //Waiting for conversation
    return(TWDR);
}