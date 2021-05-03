#include <PCF8574.h>

#ifndef RELAIS_H
#define RELAIS_H

class Relais
{
private:
    PCF8574 *PCF;

public:
    Relais();
    void begin();
    void open(int relais);
    void close(int relais);
};
#endif