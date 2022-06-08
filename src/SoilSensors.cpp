#include <SoilSensors.h>

SoilSensors::SoilSensors(Mqtt *mqttClient)
{
    mqtt = mqttClient;
}

void SoilSensors::begin()
{
    adsr1->begin();
    adsr2->begin();
}

void SoilSensors::readData()
{
    unsigned long currentMillis = millis();

    if (currentMillis - lastMeasurement > interval || lastMeasurement == 0)
    {
        lastMeasurement = currentMillis;

        for (Sensor sensor : sensors)
        {
            Serial.print("Reading ");
            Serial.print(sensor.name);
            auto values = sensor.reader->readValue(sensor.pinNumber);
            Serial.print(": ");
            Serial.print(values.percent);
            Serial.print("% | ");
            Serial.print(values.voltage);
            Serial.println("mV");

            mqtt->sendPercentage(sensor.name, values.percent);
            mqtt->sendVoltage(sensor.name, values.voltage);

            delay(10);
        }
    }
}