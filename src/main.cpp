#define PRODUCTIVE

#include <Mqtt.h>
#include <Wifi.h>
#include <SoilSensors.h>
#include <Relais.h>
#include <FillingLevel.h>

Wifi wifi;
Mqtt *mqtt = new Mqtt();
SoilSensors *soilSensors = new SoilSensors(mqtt);
Relais *relais = new Relais();
FillingLevel *fillingLevel = new FillingLevel(mqtt);

void setup(void)
{
  Serial.begin(115200);
  relais->begin();
  soilSensors->begin();
  fillingLevel->begin();

  delay(1000);

  Serial.println("Setup Start");

  wifi.connect();
  mqtt->relais(relais);
  mqtt->begin();
}

void loop(void)
{
  mqtt->connect();
  mqtt->loop();
  soilSensors->readData();
  fillingLevel->read();
}