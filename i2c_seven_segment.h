#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H


// Point
#define SEVEN_SEGMENT_DP    128

// Line segment visual thickness divisor (5=bold  12=light)
// Actual thickness = (BaseValue / this_divisor). Default 8 = medium
#define SEGMENT_THICKNESS_DIVISOR 8


// Renders a 7-segment digit at position (px,py) with specified size
uint16_t Segment_Render(uint8_t px,uint8_t py,uint8_t nb_size,uint8_t digit);




#endif // SEVEN_SEGMENT_H
