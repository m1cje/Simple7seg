/**
 * Max7219 clock
 * Bit banged output based on original source from this url
 * http://www.whatimade.today/programming-an-8-digit-7-segment-display-the-easy-way-using-a-max7219/
 *
 * MAX7219 pins
 * Din - GPio13 - D7
 * CS  - GPio15 - D8
 * Clk - GPio14 - D5
 *
 * 26th April 2022, Version 1.0 - Initial build
 **/

#include <Arduino.h>
#include <simple7seg.h>

#define DIN D7 // GPIO 13 - Default din pin for ESP8266
#define CLK D5 // GPIO 14 - Default clk pin for ESP8266

enum // enumerate the MAX7219 registers
{
    MAX7219_REG_DECODE = 0x09,
    MAX7219_REG_INTENSITY = 0x0A,
    MAX7219_REG_SCANLIMIT = 0x0B,
    MAX7219_REG_SHUTDOWN = 0x0C,
    MAX7219_REG_DISPTEST = 0x0F
};

enum // enumerate the SHUTDOWN modes
{
    OFF = 0,
    ON = 1
};

simple7seg::simple7seg(byte cs)
{
    _init(cs, DIN, CLK);
}

simple7seg::simple7seg(byte cs, byte din, byte clk)
{
    _init(cs, din, clk);
}

void simple7seg::_init(byte cs, byte din, byte clk)
{
    _cs = cs;               // User defined
    _din = din;             // Defaults to D7
    _clk = clk;             // Defaults to D5
    _displayIntensity = 15; // Set max brightness
    _dpstate = OFF;         // Turn off decimal point

    pinMode(_cs, OUTPUT);    // chip-select, active low
    pinMode(_din, OUTPUT);   // serial data-ii
    pinMode(_clk, OUTPUT);   // serial clock
    digitalWrite(_cs, HIGH); // chip-select, active low
    _resetDisplay();         // reset the MAX2719 display
}

void simple7seg::_setRegister(byte reg, byte value)
{
    digitalWrite(_cs, LOW);
    digitalWrite(_cs, LOW);
    digitalWrite(_clk, LOW);
    shiftOut(_din, _clk, MSBFIRST, reg);
    shiftOut(_din, _clk, MSBFIRST, value);
    digitalWrite(_cs, HIGH);
}

void simple7seg::_resetDisplay(void)
{
    _setRegister(MAX7219_REG_SHUTDOWN, OFF);                // turn off display
    _setRegister(MAX7219_REG_DISPTEST, OFF);                // turn off test mode
    _setRegister(MAX7219_REG_INTENSITY, _displayIntensity); // display intensity
    _setRegister(MAX7219_REG_SCANLIMIT, 7);                 // scan limit display 8 digits
    _setRegister(MAX7219_REG_DECODE, 0b11111111);           // decode all digits
    _setRegister(MAX7219_REG_SHUTDOWN, ON);                 // Turn on display
}

// msg should be a single character
// pos = 1 on right thru 8 on left
void simple7seg::displayChar(byte pos, char msg)
{
    byte outc;
    switch (msg)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        outc = msg - '0';
        break;
    case '-':
        outc = 0x0a;
        break;
    case 'e':
    case 'E':
        outc = 0x0b;
        break;
    case 'h':
    case 'H':
        outc = 0x0c;
        break;
    case 'l':
    case 'L':
        outc = 0x0d;
        break;
    case 'o':
    case 'O':
        outc = '0';
        break;
    case 'p':
    case 'P':
        outc = 0x0e;
        break;
    case ' ':
        outc = 0x0f;
        break;
    case '.':
    case ',':
    case ':':
        outc = 0x8f;
        break;
    default:
        outc = 0x0f;
        break;
    }
    if (_dpstate)
        outc |= 0x80;
    _setRegister(pos, outc);
}

void simple7seg::displayMessage(char *msg) // msg should be 8 characters long
{
    for (auto i = 0; i < 8; i++)
        displayChar(i + 1, msg[7 - i]);
}

void simple7seg::setDP(bool dpstate)
{
    _dpstate = dpstate;
}

void simple7seg::setIntensity(byte level)
{
    if (level > 0x0f)
        level = 0x0f;
    _displayIntensity = level;
    _setRegister(MAX7219_REG_INTENSITY, _displayIntensity); // display intensity
}
