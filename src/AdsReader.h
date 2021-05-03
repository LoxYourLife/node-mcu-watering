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
    Adafruit_ADS1115 ads;

public:
    AdsReader(uint8_t addr);
    SensorData readValue(int pin);
};

#endif