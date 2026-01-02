#ifndef SSD1306_h
#define SSD1306_h

#include <stdint.h>

#define SSD1306_ADDR 0x78  // (0x3C << 1)

// Writes a command byte to the SSD1306 controller
void SSD1306_Write_Command(unsigned char cmd);

// Writes a data byte to the SSD1306 display RAM
void SSD1306_Write_Data(unsigned char dat);

// Initializes and configures the SSD1306 display
void SSD1306_Init(void);

// Clears the entire display (fills with 0)
void SSD1306_Clear(void);

// Draws 8 vertical pixels at specified column 'x' and row 'y'
void SSD1306_Draw_Pixels(uint8_t x, uint8_t y, uint8_t data);

// Controls display on/off
// @param power_mode 0: off, 1: on
void SSD1306_Power(uint8_t power_mode);



#endif // SSD1306_h
