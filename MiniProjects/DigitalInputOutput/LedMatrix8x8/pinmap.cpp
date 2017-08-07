/*!
* This file is used to confirm hardware pin map
*/

#include "mbed.h"

enum {
  Low = 0,
  High = 1,
  DelayInMSec = 500
};

DigitalOut low_1(PB_6);
DigitalOut low_2(PA_4);
DigitalOut low_3(PB_7);
DigitalOut low_4(PB_1);
DigitalOut low_5(PA_9);
DigitalOut low_6(PB_0);
DigitalOut low_7(PA_10);
DigitalOut low_8(PA_12);

DigitalOut col_1(PB_3);
DigitalOut col_2(PA_11);
DigitalOut col_3(PA_8);
DigitalOut col_4(PB_5);
DigitalOut col_5(PA_3);
DigitalOut col_6(PB_4);
DigitalOut col_7(PA_0);
DigitalOut col_8(PA_1);

void pinmap() {

    low_1 = High;
    low_2 = High;
    low_3 = High;
    low_4 = High;
    low_5 = High;
    low_6 = High;
    low_7 = High;
    low_8 = High;

    while(1) {
        col_1 = High;
        col_2 = High;
        col_3 = High;
        col_4 = High;
        col_5 = High;
        col_6 = High;
        col_7 = High;
        col_8 = High;
        wait_ms(DelayInMSec);

        col_1 = Low;
        col_2 = Low;
        col_3 = Low;
        col_4 = Low;
        col_5 = Low;
        col_6 = Low;
        col_7 = Low;
        col_8 = Low;
        wait_ms(DelayInMSec);
    }
}

int main()
{
  pinmap();
}
