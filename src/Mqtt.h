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

    char *sensorTopic = (char *)"soilSensors_test";
    char *relaisTopic = (char *)"wateringRelais/#";
    void callback(char *topicChar, byte *payload, unsigned int length);

public:
    void relais(Relais *relaisClass);
    void begin();
    void connect();
    void loop();
    void sendPercentage(char *name, double value);
    void sendVoltage(char *name, double value);
};

#endif