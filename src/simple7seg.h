#pragma once

class simple7seg
{
public:
    simple7seg(byte cs);
    simple7seg(byte cs, byte din, byte clk);
    void displayChar(byte pos, char msg);
    void displayMessage(char *msg);
    void setDP(bool dpstate);
    void setIntensity(byte level);

private:
    void _init(byte cs, byte din, byte clk);
    void _setRegister(byte reg, byte value);
    void _resetDisplay(void);

    byte _cs;
    byte _din;
    byte _clk;
    byte _displayIntensity;
    bool _dpstate;
};
