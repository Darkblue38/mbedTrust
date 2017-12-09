/*
 * The basic test codes to check the AnglogIn.
 */

#include "mbed.h"

static AnalogIn ain_x(A6); // connect joistics' x axis to A6 pin of mbed
static AnalogIn ain_y(A5); // connect joistics' y axis to A5 pin of mbed

static void printAnalogInput(AnalogIn *xin, AnalogIn *yin)
{
  uint8_t point[2] = { 0 };
  point[0] = (uint8_t)(xin->read()*100.0f + 0.5);
  point[1] = (uint8_t)(yin->read()*100.0f + 0.5);
  printf("x: %d, y: %d\n", point[0], point[1]);
}

int main()
{
    while(1)
    {
        printAnalogInput(&ain_x, &ain_y);
        wait(0.2f);
    }
}
