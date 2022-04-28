/**
 * Simple7seg.cpp
 *
 * 28 April 2022 - Version 1.0, initial build
 *
 **/

#include <Arduino.h>
#include <simple7seg.h>

#define CHIPSSELECT D8 // GPIO 15 - also boot select pin
simple7seg display(CHIPSSELECT);

void setup(void)
{
  display.setIntensity(15);
}

void loop(void)
{
  // Set message
  display.displayMessage((char *)" Hello  ");
  delay(5000);

  // Set intensity
  for (auto i = 0; i < 16; i++)
  {
    display.setIntensity(i);
    char mbuff[8] = {' '};
    mbuff[0] = i > 9 ? '1' : ' ';
    mbuff[1] = '0' + (i % 10);
    mbuff[6] = mbuff[0];
    mbuff[7] = mbuff[1];
    display.displayMessage(mbuff);
    delay(1000);
  }
  delay(5000);

  // Set dp positions are numbered from 8 on the left to 1 on the right
  for (auto i = 1; i < 9; i++)
  {
    display.setDP(true);
    display.displayChar(i, ' ');
    delay(500);
    display.setDP(false);
    display.displayChar(i, ' ');
    delay(500);
  }
}
