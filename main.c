
/*

    MIT License

    Copyright (c) 2025 Cetin Atila

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

*/


#include <stdint.h>
#include <mcs51/at89x051.h>

#include "stc_i2c.h"
#include "ssd1306.h"
#include "i2c_seven_segment.h"
#include "stc8g_reg.h"



uint8_t Print_Number(uint8_t x,uint8_t y,uint8_t size,uint16_t number){
    uint8_t pos_x;

    // Calculate segment size
    uint8_t segment_width=size/2;
    uint8_t segment_thickness=size/SEGMENT_THICKNESS_DIVISOR;
    uint8_t space=4; // Space between digits
    uint8_t width;

    // Total width for per digit = (segment width) + (segment thickness for DP) + space
    width = segment_width + segment_thickness + space;

    // Print switch
    // 0: draw necessary digits
    // 1: draw 5 digits (Max 16 bit =65535 : 5 digits)
    uint8_t  print_sw =1;
    uint16_t div_dec  =10000;

    pos_x = x;

    for(uint8_t i=5;i>0;i--){
        uint8_t digit=(number/div_dec)%10;
        div_dec=div_dec/10;

        // If digit diffrent from 0
        // Blanks zeros to the left of the most significant digit
        if(digit) print_sw=1;

        if(print_sw){
             // Print one digit on the screen
             Segment_Render(pos_x,y,size,digit);
             pos_x+=width;
        }
    }

    // Return next caret x position
    return pos_x;
}




#define ADC_POWER   0x80
#define ADC_START   0x40
#define ADC_FLAG    0x20


void ADC_Init(void) {
    P1M0 = 0x00;    // Set P1.0 for input
    P1M1 = 0x01;

    ADCTIM = 0xCf;

    ADCCFG = 0x2F;  // ADC value set right side
    ADC_CONTR = ADC_POWER;

    Delay_ms(1);
}


uint16_t ADC_Read(uint8_t channel) {
    uint16_t result;
    uint8_t low, high;

    // Select channel (0-7)
    ADC_CONTR |= channel & 0x07;

    // Start ADC conversation
    ADC_CONTR |= ADC_POWER | ADC_START;

    // Wait for conversation
    while (!(ADC_CONTR & ADC_FLAG));

    // Clear ADC flag
    ADC_CONTR &= ~ADC_FLAG;

    // Read ADC value (10-bit)
    low  = ADC_RESL;
    high = ADC_RES & 0x03;
    result = (high << 8) | low;

    return result;
}




void main(void) {

    // Enable XDATA access
    P_SW2  = 0x80;

    // Init I2C; set pin configration and speed
    I2C_Init(400); // Speed at 400Khz

    // Init SSD1306 display
    SSD1306_Init();

    // Clear display
    SSD1306_Clear();

    // Init ADC
    ADC_Init();


    uint8_t pos_x = 0;
    uint8_t pos_y = 0;
    uint8_t size  = 32;

    // ADC value read from MCU
    uint16_t adc_value = 0;

    while(1){

        adc_value=ADC_Read(0);

        // Calculate voltage (assume Vref = 3.0V)
        // voltage = (adc_value * 3.0) / 1024;

        // Print adc value
        Print_Number(pos_x,pos_y,size,adc_value);
    }


}


