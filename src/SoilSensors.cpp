#include <SoilSensors.h>

SoilSensors::SoilSensors(Mqtt *mqttClient)
{
    mqtt = mqttClient;
    adsr1 = new AdsReader(ADS1115_ADDRESS_1);
    adsr2 = new AdsReader(ADS1115_ADDRESS_2);
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