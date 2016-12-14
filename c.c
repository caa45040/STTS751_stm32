
#include "mbed.h"
 
#define ADDR     (0x39<<1) //  address
 
I2C i2c(I2C_SDA, I2C_SCL);
 
DigitalOut myled(LED1);
 
Serial pc(SERIAL_TX, SERIAL_RX);
 
volatile char TempCelsiusDisplay[] = "+abc.d C";
 
//i2cdetect -y 9
//     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
//00:          -- -- -- -- -- -- -- -- -- -- -- -- --
//10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//30: -- -- -- -- -- -- -- -- -- 39 -- -- -- -- -- --
//40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//70: -- -- -- -- -- -- -- --
//i2cget -y 9 0x39
//0x1c

int tempval;

int main()
{
 
    char data_read[2];
  
    while (1) {
        // Read temperature register

        i2c.read(ADDR, data_read,1,false);
 
        // Calculate temperature value in Celcius
        int tempval =  data_read[0];

 
 
        // Integer part

    //TempCelsiusDisplay[0] = '+';
        TempCelsiusDisplay[1] = (tempval / 100) + 0x30;
        TempCelsiusDisplay[2] = ((tempval % 100) / 10) + 0x30;
        TempCelsiusDisplay[3] = ((tempval % 100) % 10) + 0x30;
    //TempCelsiusDisplay[4] = '.';
    TempCelsiusDisplay[5] = '0';
 
        // Display result
        pc.printf("temp = %s\n", TempCelsiusDisplay);
        myled = !myled;
        wait(1.0);
    }
 
}
