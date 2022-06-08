#ifndef FILLING_LEVEL_H
#define FILLING_LEVEL_H
#include <Arduino.h>
#include <Mqtt.h>

class FillingLevel
{
private:
    const uint8_t TRIGGER = D5;
    const uint8_t ECHO = D6;

    unsigned long lastMeasurement = 0;
    const unsigned long interval = 15000;
    const int minDistanceToWater = 3;
    const int maxDistance = 42 - minDistanceToWater;

    Mqtt *mqtt;

public:
    FillingLevel(Mqtt *mqttClient);
    void begin();
    void read();
};

#endif
