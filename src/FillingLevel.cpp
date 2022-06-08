#include <FillingLevel.h>

FillingLevel::FillingLevel(Mqtt *mqttClient)
{
    mqtt = mqttClient;
}

void FillingLevel::begin()
{
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);
    digitalWrite(TRIGGER, LOW);
}

void FillingLevel::read()
{
#ifndef PRODUCTIVE
    unsigned long currentMillis = millis();

    if (currentMillis - lastMeasurement > interval || lastMeasurement == 0)
    {
        lastMeasurement = currentMillis;

        Serial.print("Füllstandsmessung: ");
        digitalWrite(TRIGGER, HIGH);
        delay(10);
        digitalWrite(TRIGGER, LOW);
        long dauer = pulseIn(D6, HIGH);
        double rawDistance = ((dauer / 2) * 0.03432);
        double distance = maxDistance - (rawDistance - minDistanceToWater);
        double percent = (maxDistance - distance) * 100 / maxDistance;
        if (distance <= maxDistance && distance >= 0)
        {
            mqtt->sendFillingLevel(distance, percent);
        }
        else
        {
            mqtt->sendFillingLevel(-1, 0);
        }
        Serial.print(rawDistance);
        Serial.print(" cm ");
        Serial.print(distance);
        Serial.print(" cm ");
        Serial.print(percent);
        Serial.println("%");
    }
#endif
}