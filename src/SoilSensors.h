#include <Mqtt.h>
#include <AdsReader.h>

#ifndef SOIL_SENSORS_H
#define SOIL_SENSORS_H

#define ADS1115_ADDRESS_1 (0x48) ///< 1001 000 (ADDR = GND)
#define ADS1115_ADDRESS_2 (0x49) ///< 1001 001 (ADDR = VDD)
#define ADS1115_ADDRESS_3 (0x4A) ///< 1001 010 (ADDR = SDA)
#define ADS1115_ADDRESS_4 (0x4B) ///< 1001 011 (ADDR = SCL)

class SoilSensors
{
private:
    AdsReader *adsr1;
    AdsReader *adsr2;
    Mqtt *mqtt;
    unsigned long lastMeasurement = 0;
    const unsigned long interval = 60000;

    struct Sensor
    {
        AdsReader *reader;
        char *name;
        int pinNumber;
    };
    const Sensor sensors[8] = {
        {adsr1, (char *)"Sensor1", 0},
        {adsr1, (char *)"Sensor2", 1},
        {adsr1, (char *)"Sensor3", 2},
        {adsr1, (char *)"Sensor4", 3},
        {adsr2, (char *)"Sensor5", 0},
        {adsr2, (char *)"Sensor6", 1},
        {adsr2, (char *)"Sensor7", 2},
        {adsr2, (char *)"Sensor8", 3},
    };

public:
    SoilSensors(Mqtt *mqttClient);
    void readData();
};
#endif