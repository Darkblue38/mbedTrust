/*!
* This file is used to scroll string to test
*/

#include "mbed.h"

#define SPACE { \
    {0, 0, 0, 0, 0, 0, 0, 0},  \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0} \
}

#define H { \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}  \
}

#define E  { \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define L { \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 1, 1, 1, 1, 1, 0}  \
}

#define O { \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}  \
}

#define V { \
    {0, 0, 0, 0, 0, 0, 0, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 1, 0, 0, 0, 0, 1, 0}, \
    {0, 0, 1, 0, 0, 1, 0, 0}, \
    {0, 0, 1, 0, 0, 0, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 0, 1, 1, 0, 0, 0}, \
    {0, 0, 0, 0, 0, 0, 0, 0}  \
}

enum {
  Low = 0,
  High = 1,
  MaxNumOfCol = 8,
  MaxNumOfRow = 8
};

static uint8_t col = 0;
static uint8_t leds[8][8];

static const int numPatterns = 6;
static uint8_t patterns[numPatterns][8][8] = {
  H,E,L,L,O,SPACE
};

// Hardware Digital Ouptut initialization
static DigitalOut rows[8] = {PA_1, PA_0, PB_4, PA_3, PB_5, PA_8, PA_11, PB_3 };
static DigitalOut cols[8] = {PB_6, PA_4, PB_7, PB_1, PA_9, PB_0, PA_10, PA_12 };

void clearLeds() {
  // Clear display array
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = Low;
    }
  }
}

void setPattern(int pattern) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      leds[i][j] = patterns[pattern][i][j];
    }
  }
}

// forward moving
void slidePattern(int pattern, int delay) {
  for (int l = 0; l < 8; l++) {
    for (int j = 0; j < 7; j++) {
      for (int i = 0; i < 8; i++) {
        leds[i][j] = leds[i][j+1];
      }
    }
    for (int i = 0; i < 8; i++) {
      leds[i][7] = patterns[pattern][i][0 + l];
    }
    wait_ms(delay);
  }
}

// reverse sliding
void slidePattern_reverse(int pattern, int delay) {
  for (int l = 7; l >= 0; l--)
  {
    for (int j = 6; j >= 0; j--) {
      for (int i = 0; i < 8; i++) {
        leds[i][j] = leds[i][j-1];
      }
    }
    for (int i = 0; i < 8; i++) {
      leds[i][0] = patterns[pattern][i][0 + l];
    }
    wait_ms(delay);
  }
}

//Interrupt routine
void display() {
  cols[col] = Low;  // Turn whole previous column off
  col++;
  if (col == MaxNumOfCol) {
    col = 0;
  }
  for (int row = 0; row < MaxNumOfRow; row++) {
    if (leds[col][7 - row] == 1) {
      rows[row] = Low;  // Turn on this led
    }
    else {
      rows[row] = High; // Turn off this led
    }
  }
  cols[col] = High; // Turn whole column on at once (for equal lighting times)
}

// Ticker function is used to generate a periodic function call
static Ticker flipper;

static AnalogIn ain_x(A6); // connect joistics' x axis to A6 pin of mbed
static AnalogIn ain_y(A5); // connect joistics' y axis to A5 pin of mbed

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum
{
  MaximumSpeed = 20,
  LowerMarginInStall = 48,
  UpperMarginInStall = 52
};

int main()
{
  uint8_t pattern = 0;
  uint8_t analogInputX = 0;

  flipper.attach_us(&display, 1000);
  setPattern(pattern);

  while(1)
  {
    analogInputX = (uint8_t)(ain_x.read()*100.0f + 0.5);

    if(LowerMarginInStall > analogInputX)
    {
      if(++pattern >= numPatterns)
      {
        pattern = 0;
      }
      printf("pattern = %d\n", pattern);
      slidePattern(pattern, MAX(MaximumSpeed, analogInputX));
    }
    else if(UpperMarginInStall < analogInputX)
    {
      if(--pattern >= numPatterns)
      {
        pattern = numPatterns - 1;
      }
      printf("pattern = %d\n", pattern);
      slidePattern_reverse(pattern, MAX(MaximumSpeed, 100 - analogInputX));
    }
  }
}
