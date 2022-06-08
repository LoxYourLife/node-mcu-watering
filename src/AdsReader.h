#include <Adafruit_ADS1X15.h>
#include <SPI.h>

#ifndef ADSREADER_H
#define ADSREADER_H

class AdsReader
{
private:
    struct SensorData
    {
        double voltage;
        double percent;
    };
    Adafruit_ADS1115 *ads;
    uint8_t address;

public:
    AdsReader(uint8_t addr);
    void begin();
    SensorData readValue(int pin);
};

#endif