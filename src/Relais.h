#include <PCF8574.h>
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#ifndef RELAIS_H
#define RELAIS_H

class Relais
{
private:
    PCF8574 *PCF;
    Adafruit_MCP23017 *mcp;
    uint8_t pins[8] = {0, 1, 2, 3, 4, 5, 6, 7};

public:
    Relais();
    void begin();
    void open(int relais);
    void close(int relais);
};
#endif