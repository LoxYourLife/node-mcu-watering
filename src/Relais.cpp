#include <Relais.h>

Relais::Relais()
{
    PCF = new PCF8574(0x20);
}

void Relais::begin()
{
    Serial.print("Connecting to PCF8574 ... ");
    if (!PCF->begin(LOW))
    {
        Serial.print("Initialization Failure ");
    }

    if (!PCF->isConnected())
    {
        Serial.println("=> connection failed");
    }
    else
    {
        Serial.println("=> connected");
    }
}

void Relais::open(int relais)
{
    if (PCF->isConnected())
    {
        Serial.print("Openeing relais ");
        Serial.println(relais);
        int pin = relais - 1; // convert 1-8 to 0-7
        PCF->write(pin, HIGH);
    }
    else
    {
        Serial.print("Connot open relais ");
        Serial.print(relais);
        Serial.println(" because PCF is not connected");
    }
}

void Relais::close(int relais)
{
    if (PCF->isConnected())
    {
        Serial.print("Closing relais ");
        Serial.println(relais);
        int pin = relais - 1; // convert 1-8 to 0-7
        PCF->write(pin, LOW);
    }
    else
    {
        Serial.print("Connot open relais ");
        Serial.print(relais);
        Serial.println(" because PCF is not connected");
    }
}