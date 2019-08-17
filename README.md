# AVR-I2C-TWI-library
Very simple Two Wire / I2C library for AtMega168 & AtMega328

Add this function to main:
   
    twiInit();

Add this functions to anywhere in main, or while infinite loop:
    
    //For writing slave:
    twiStart();
    twiSend(SLAVE_ADDRESS_W); //LSB is 0 - write mode
    twiSend(data);
    twiSend(data);
    twiStop();

    //For reading slave:
    twiStart();
    twiSend(SLAVE_ADDRESS_R); //LSB is 1 - read mode
    data = twiReadWithAck();
    twiStop();
