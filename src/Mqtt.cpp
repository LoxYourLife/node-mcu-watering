#include <Mqtt.h>

IPAddress MQTT_BROKER(10, 10, 1, 4);
const uint16_t MQTT_PORT = 1883;
const char *MQTT_USER = "loxberry";
const char *MQTT_PASS = "password";
unsigned long previousMillis = 0;
unsigned long interval = 2000;

void Mqtt::relais(Relais *relaisClass)
{
    relaisController = relaisClass;
}

void Mqtt::begin()
{
    wifiClient = new WiFiClient();
    std::function<void(char *, uint8_t *, unsigned int)> callbackFn = std::bind(&Mqtt::callback, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    client = new PubSubClient(MQTT_BROKER, MQTT_PORT, callbackFn, *wifiClient);
    connect();
}
void Mqtt::connect()
{
    if (!client->connected())
    {
        Serial.print("Connecting to Mqtt Broker ... ");
        while (!client->connected())
        {
            if (client->connect(clientName, MQTT_USER, MQTT_PASS))
            {
                Serial.println("Connection established");
                delay(100);
                client->subscribe(relaisTopic);
                client->setKeepAlive(30);
                client->setSocketTimeout(40);
                return;
            }
            else
            {
                Serial.print("failed with state ");
                Serial.println(client->state());
                delay(2000);
            }
        }
    }
}

void Mqtt::loop()
{
    client->loop();
}

void Mqtt::sendPercentage(char *name, double percent)
{
    char topic[200];
    char value[10];
    sprintf(topic, "%s/%s/percent", sensorTopic, name);
    sprintf(value, "%3.2f", round(percent));
    client->publish(topic, value);
}

void Mqtt::sendVoltage(char *name, double voltage)
{
    char topic[200];
    char value[10];
    sprintf(topic, "%s/%s/voltage", sensorTopic, name);
    sprintf(value, "%4.2f", round(voltage));
    client->publish(topic, value);
}
void Mqtt::sendFillingLevel(double distance, double percent)
{
    char distanceValue[10];
    sprintf(distanceValue, "%4.2f", distance);
    char percentValue[10];
    sprintf(percentValue, "%2.2f", percent);
    client->publish(fillingLevelDistanceTopic, distanceValue);
    client->publish(fillingLevelpercentTopic, percentValue);
}

void Mqtt::callback(char *topicChar, byte *payload, unsigned int length)
{
    String topic = topicChar;
    String message = "";
    for (unsigned int i = 0; i < length; i++)
    {
        message = message + (char)payload[i];
    }

    int relaisNumber = topic.substring(15).toInt();

    Serial.print("Received Message on Topic \"");
    Serial.print(topic);
    Serial.print("\" on Relais ");
    Serial.print(relaisNumber);
    Serial.print(" with message: ");
    Serial.println(message);

    if (message == "on")
    {
        relaisController->open(relaisNumber);
    }
    else
    {
        relaisController->close(relaisNumber);
    }
}