#include <Relais.h>

Relais::Relais()
{
    mcp = new Adafruit_MCP23017();
}

void Relais::begin()
{
    mcp->begin();
    for (uint8_t pin : pins)
    {
        mcp->pinMode(pin, OUTPUT);
        mcp->digitalWrite(pin, HIGH);
        mcp->pullUp(pin, HIGH);
    }
}

void Relais::open(int relais)
{
    Serial.print("Openeing relais ");
    Serial.println(relais);
    int pin = relais - 1; // convert 1-8 to 0-7
    mcp->digitalWrite(pin, LOW);
}

void Relais::close(int relais)
{
    Serial.print("Closing relais ");
    Serial.println(relais);
    int pin = relais - 1; // convert 1-8 to 0-7
    mcp->digitalWrite(pin, HIGH);
}
