#ifndef STC_I2C_H
#define STC_I2C_H

#include <stdint.h>

// MCU: STC8G1K17


// Initializes the I2C peripheral in master mode
// i2c_speed_khz :  Desired I2C SCL clock frequency in kHz (typical range: 100-400 kHz)
void I2C_Init(uint16_t i2c_speed_khz);

// Creates a blocking delay for specified milliseconds
void Delay_ms(uint16_t ms);

// Generates I2C START condition on the bus
// Return 0: success , 1: error
uint8_t I2C_Start(void);

// Generates I2C STOP condition on the bus
// Return 0: success , 1: error
uint8_t I2C_Stop(void);

// Sends one byte over I2C bus
// Return 0: success , 1: error
uint8_t I2C_Send_Byte(uint8_t dat);

// Sends START condition and send one byte
// Return 0: success , 1: error
uint8_t I2C_Send_Start_Byte(uint8_t dat);



#endif // STC_I2C_H
