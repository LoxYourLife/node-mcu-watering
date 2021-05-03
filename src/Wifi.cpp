#include <Wifi.h>

#define WIFI_SSID "Tor zur Welt"
#define WIFI_PASSWORD "nopote#5?22417"

void Wifi::connect()
{
    if (WiFi.status() != WL_CONNECTED)
    {

        Serial.println();
        Serial.println();
        Serial.print("Verbinde mich mit Netz: ");
        Serial.println(WIFI_SSID);

        WiFi.hostname("Soil-Sensors");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("");
        Serial.println("WiFi Verbindung aufgebaut");
        Serial.print("Eigene IP des ESP-Modul: ");
        Serial.println(WiFi.localIP());
    }
}