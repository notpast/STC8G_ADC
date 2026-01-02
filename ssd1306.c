

#include <stdint.h>
#include "stc_i2c.h"
#include "ssd1306.h"



void SSD1306_Write_Command(unsigned char cmd)
{
    //I2C_Start();
    //I2C_Send_Byte(SSD1306_ADDR);
    I2C_Send_Start_Byte(SSD1306_ADDR);
    I2C_Send_Byte(0x00);  // 0x00 command mode
    I2C_Send_Byte(cmd);
    I2C_Stop();
}


void SSD1306_Write_Data(unsigned char dat)
{
    //I2C_Start();
    //I2C_Send_Byte(SSD1306_ADDR);
    I2C_Send_Start_Byte(SSD1306_ADDR);
    I2C_Send_Byte(0x40); // 0x40 data mode
    I2C_Send_Byte(dat);
    I2C_Stop();
}


// === SSD1306 init ===
void SSD1306_Init(void)
{
    Delay_ms(100);
    //SSD1306_Write_Command(0xAE); // Display OFF
    SSD1306_Write_Command(0x00); // Low column
    SSD1306_Write_Command(0x10); // High column
    SSD1306_Write_Command(0x40); // Start line 0

    SSD1306_Write_Command(0x81); SSD1306_Write_Command(0xCC); // Contrast
    SSD1306_Write_Command(0xA1); // Seg remap
    SSD1306_Write_Command(0xC8); // COM scan dec
    SSD1306_Write_Command(0xA6); // Normal display
    SSD1306_Write_Command(0xA4); // Display all on resume
    SSD1306_Write_Command(0xA8); SSD1306_Write_Command(0x3F); // Multiplex 1/64
    SSD1306_Write_Command(0xD3); SSD1306_Write_Command(0x00); // Display offset
    SSD1306_Write_Command(0xD5); SSD1306_Write_Command(0xF0); // Display clock div / osc
    SSD1306_Write_Command(0xD9); SSD1306_Write_Command(0xF1); // Precharge
    SSD1306_Write_Command(0xDA); SSD1306_Write_Command(0x12); // COM pins
    SSD1306_Write_Command(0xDB); SSD1306_Write_Command(0x40); // VCOMH detect
    SSD1306_Write_Command(0x20); SSD1306_Write_Command(0x00); // Memory addressing: horizontal
    SSD1306_Write_Command(0x8D); SSD1306_Write_Command(0x14); // Charge Pump ON
    SSD1306_Write_Command(0x20); SSD1306_Write_Command(0x00); // Multiplex 1/64
    SSD1306_Write_Command(0xAF); // Display ON

    Delay_ms(100);
}


void SSD1306_Power(uint8_t power_mode) {
	if (power_mode == 1) {
		 SSD1306_Write_Command(0xAF); // Display ON command
	} else if (power_mode == 0) {
		 SSD1306_Write_Command(0xAE); // Display OFF command
	}
	return;
}


// --- Clear display ---
void SSD1306_Clear(void) {
    uint8_t page, col;

    for (page = 0; page <8; page++) {
        SSD1306_Write_Command(0xB0 + page); // page address
        SSD1306_Write_Command(0x00);        // lower col
        SSD1306_Write_Command(0x10);        // higher col

        I2C_Send_Start_Byte(SSD1306_ADDR);
        I2C_Send_Byte(0x40);  // data mode
        for (col = 0; col < 128; col++) {
            I2C_Send_Byte(0x00);
        }
        //I2C_Stop();
    }
}


void SSD1306_Draw_Pixels(uint8_t x, uint8_t y, uint8_t data) {

    // Check in screen boundary
    if(x>127 || y>63){
        return;
    }

    uint8_t page = (64-y) / 8;

    I2C_Send_Start_Byte(SSD1306_ADDR);  // start + adres (write)
    I2C_Send_Byte(0x00);                // Start send command (0x00)
    I2C_Send_Byte(0xB0 + page);         // Page address
    I2C_Send_Byte(x & 0x0F);            // Lower  col
    I2C_Send_Byte(0x10 | (x >> 4));     // Higher col


    I2C_Send_Start_Byte(SSD1306_ADDR);
    I2C_Send_Byte(0x40); // Data mode
    I2C_Send_Byte(data); // Draw 8 pixels
    I2C_Stop();
}



