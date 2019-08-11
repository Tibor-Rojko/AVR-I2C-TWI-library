/***********************************************************************************************
 * Very simple TWI/I2C library for AtMega168 or AtMega328                                       
 *  
 * 2019, Tibor Rojko
 * 
 * pinout:
 * A4 (SDA), A5 (SCL)                                                            
 **********************************************************************************************/

#define F_CPU 16000000      //16 MHz
//#define PRESCALER 1         //1, 4, 16, 64
#define SCL_FREQ 100000     //100 <-> 400 kHz

/*
SCL_FREQ = 100kHz = 100000 Hz
F_CPU = 16MHz = 16000000 Hz
Prescaler = 1
TWBR = ?

SCL_FREQ = F_CPU/(16 + 2 * TWBR * Prescaler)
16 + 2 * TWBR = F_CPU / SCL_FREQ
TWBR = 0.5 ((F_CPU / SCL_FREQ) - 16)
TWBR = 0.5((16000000/100000) - 16) = 72
*/

/*
    Setting the bit rate of I2C bus
    Enable I2C
*/
void twiInit(void);

/*
    I2C conversation starts by pulling the SDA line low before the clock is started up.
    This is the start signal.
*/
void twiStart(void);

/*
    Stop signal is a rising edge with the clock high
*/
void twiStop(void);

//Sending byte to slave
void twiSend(uint8_t data);

/*
    After receiving send back ACK, for this use the twiReadWithAck() function, 
    this will sign for slave, that transmission was ok.
    In the end of communication, after the last received byte, use twiReadNoAck(),
    which means for slave, that the transaction will be end.
    Send stop condition (twiStop() function), after reading with NoACK
*/
uint8_t twiReadWithAck(void);
uint8_t twiReadNoAck(void);