#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <Relais.h>

#ifndef MQTT_H
#define MQTT_H

class Mqtt
{

private:
    WiFiClient *wifiClient;
    PubSubClient *client;
    Relais *relaisController;

    const char *clientName = (char *)"Soil_Sensor";
    const char *sensorTopic = (char *)"soilSensors";
    const char *relaisTopic = (char *)"wateringRelais/#";
    const char *fillingLevelDistanceTopic = (char *)"TankFillingLevel/distance";
    const char *fillingLevelpercentTopic = (char *)"TankFillingLevel/percent";

    void callback(char *topicChar, byte *payload, unsigned int length);

public:
    void relais(Relais *relaisClass);
    void begin();
    void connect();
    void loop();
    void sendPercentage(char *name, double value);
    void sendVoltage(char *name, double value);
    void sendFillingLevel(double distance, double percent);
};

#endif

