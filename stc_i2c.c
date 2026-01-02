
#include <stdint.h>

#include "stc_i2c.h"
#include "stc8g_reg.h"



static void I2C_Pin_Init(void) {

    // P3.2 / P3.3 set alternatif function to I2C for STC8G1K17 DIP16 Pack
    P_SW2 |=0x30;

    // Set quasi bidirectional weak push-pull
    // port 3.2 - 3.3
    P3M1 &= ~0x0C;
    P3M0 &= ~0x0C;
}




void I2C_Init(uint16_t i2c_speed_khz) {

    // Enable XDATA access
    P_SW2 |= 0x80;

    I2C_Pin_Init();

    if(i2c_speed_khz == 0){
        i2c_speed_khz = 100; // If speed is zero set it to 100Khz standart value
    }

    uint8_t msspeed=0;

    // This is I2C's speed formula from original STC document
    // Note: sysclk and i2c_speed values are in kHz
    // speed = ( (F_OSC / i2c_speed / 2) - 4 ) / 2
    uint16_t sysclk=24000/((uint16_t)(CLKDIV)+1);

    // msspeed = (((sysclk/i2c_speed_khz)/2)-4)/2;
    uint16_t calc_val=((sysclk/i2c_speed_khz)/2);

    if(calc_val<4){
        msspeed=0;
    }else{
        msspeed = (calc_val-4)/2;
    }

    if(msspeed > 63){
        msspeed = 63;
    }

    // I2CCFG setting
    // Set bit 7: Enable I2C
    // Set bit 6: Select master mode
    I2CCFG = 0xC0;

    // Set i2c speed, mask bit[5:0]
    I2CCFG |= msspeed & 0x3F;

    // Disable WDTA
    I2CMSAUX &= ~0x01;

    // Disable I2C interrupt
    I2CMSCR &= ~0x80;
}



// @24Mhz
void Delay_ms(uint16_t ms) {
    uint16_t i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1000; j++);
}



static uint8_t I2C_Wait(void)
{
    uint8_t timeout = 200; // timeout value

    while ( (I2CMSST & 0x40) == 0)
    {
        if (--timeout == 0) return 1;
    }
    I2CMSST &= ~0x40;
    return 0;
}



uint8_t I2C_Start(void)
{
    I2CMSCR = 0x01; // START
    return I2C_Wait();
}



uint8_t I2C_Stop(void)
{
    I2CMSCR = 0x06; // STOP
    return I2C_Wait();
}



/* START + SEND + RECV_ACK */
uint8_t I2C_Send_Start_Byte(uint8_t dat)
{
    I2CTXD = dat;
    I2CMSCR = 0x09;  // START + SEND + RECV_ACK
    if (I2C_Wait()==0) return 0;
    return !((I2CMSST & 0x02) == 0); // bit[1] = 0 ACK OK
}



/* SEND + RECV_ACK */
uint8_t I2C_Send_Byte(uint8_t dat)
{
    I2CTXD = dat;
    I2CMSCR = 0x0A;  // SEND + RECV_ACK
    if (I2C_Wait()==0) return 0;
    return !((I2CMSST & 0x02) == 0); // 0 = ACK OK
}






