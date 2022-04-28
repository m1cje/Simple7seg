# Simple7seg

## A Library for displaying output on a 7 segment display module driven by the MAX7219 chip

![alt text](https://github.com/m1cje/Simple7seg/blob/main/docs/MAX7219.jpg?raw=true)

This is a simple library for driving one of the MAX7219 based 7 segment display modules.  These modules are driven with a SPI interface.  The library is designed to provide quick and easy support for a simple display output.  For more sophisticated requirements there are many other lbraries available.

* Small footprint
* Simple to implement
* No library dependancies
* Single display per instance
* Works with any available pins

See example.cpp for typical usage

### Using the Library

### Connecting the display module
There are three control pins required.  Data In (din) and Clock (clk) default to pins D7 for din and D5 for clk.  These two pins can be shared with other spi devices.<br>
The third pin is Chip Select (cs) which needs to be unique for each spi device connected.  Typically on the ESP8266 use pin D6 or D8.  You can connect multiple displays so long as each uses a seperate cs pin.<br>
Besides the control pins you will need to provide the module with power.  If possible use a 5v supply although the display should run on 3.3v if that's all you have available.
You may find it helpful to connect a small electrolytic capacitor across the supply pins on the back of the module, especially if you are rapidly switching output levels.<br>
If the default pins are already in use on your project then the library should work with any of the other available gpio pins.
The module should work with the 3.3v levels on the gpio pins directly connected.  If you have a lot of voltage drop on the control lines then you may need to use a level shifter to lift the voltages up to ttl levels.<br>

#### include <Simple7seg.h>
The include command needs to be at the top of your source code along with any other library includes you are using.<br>

#### Simple7seg display;
This command is required to create an instance of the Simple7seg driver.  It should be included near the top of your source code before the setup() and loop() functions.<br>

### Function Reference
#### simple7seg display(CHIPSSELECT)
This will create an instance of the driver using the pin specified by CHIPSELECT and the default of D7 for din and D5 for clk.<br>
```
  simple7seg display(byte cs);
```
#### simple7seg display(CHIPSSELECT,DIN,CLK)
This will create an instance of the driver overiding the default pins and using the pins specified.<br>
```
  simple7seg display(byte cs, byte din, byte clk);
```
##### Parameters
  _byte cs_ - The pin number used for chip select<br>
  _byte din_ - The pin number used for data in.<br>
  _byte clk_ - The pin number used for clock.<br>
##### Returns
  Nothing.<br>

#### displayChar(pos, msg)
This function will display a single character at a given position.  Accepted characters are the 10 numeric digits, hyphen, space, eEhHlLpP.  Any other character will display as a blank. The characters .,: will all display a blank with the decimal point lit.<br>
```
  displayChar(byte pos, char msg);
```
##### Parameters
  _byte pos_ - The position where on the display module to display the character.  Position 8 is on the left and position 1 is on the right.<br>
  _char msg_ - The character to display, see above for permitted characters.<br>
##### Returns
  Nothing.<br>

#### displayMessage(msg)
This function will display a character array at a given position.  Accepted characters are as for the displaychar() function.<br>
```
  displayMessage(char *msg);
```
##### Parameters
  _char *msg_ - A pointer to an array of eight characters to be displayed. The characters will be displayed in the order they appear in the source array.<br>
##### Returns
  Nothing.<br>

#### setDP(state)
This function will turn on or off the decimal point state.  It does not display anything itself but apples to all future character writes. Note that is you turn it on before calling the displaymessage() function then all characters will show the decimal point.<br>
```
  setDP(bool state);
```
##### Parameters
  _bool state_ - true or 1 will turn on the dp, false or 0 will turn it off.<br>
##### Returns
  Nothing.<br>

#### setIntensity(level)
This function sets the output intensity to a level from 0 to 15.  The function operates independantly of the character write function.<br>
```
  setIntensity(byte level);
```
##### Parameters
  _byte level_ - A number between 0 and 15 with 15 being the brightest.<br>
##### Returns
  Nothing.<br>

