#include <Mqtt.h>
#include <Wifi.h>
#include <SoilSensors.h>
#include <Relais.h>

Wifi wifi;
Mqtt *mqtt = new Mqtt();
SoilSensors *soilSensors = new SoilSensors(mqtt);
Relais *relais = new Relais();

void setup(void)
{
  Serial.begin(115200);

  delay(1000);

  wifi.connect();
  mqtt->relais(relais);
  mqtt->begin();
}

void loop(void)
{
  mqtt->connect();
  mqtt->loop();
  //soilSensors->readData();
  //mqtt->send();
}