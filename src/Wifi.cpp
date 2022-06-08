#include <Wifi.h>

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "password"

void Wifi::connect()
{
    if (WiFi.status() != WL_CONNECTED)
    {

        Serial.println();
        Serial.println();
        Serial.print("Verbinde mich mit Netz: ");
        Serial.println(WIFI_SSID);

        WiFi.hostname("ESP8266-Watering");
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
    else
    {
        Serial.println(WIFI_SSID);
        Serial.println(WiFi.status());
        Serial.println(WiFi.localIP());
        Serial.println("Seems like wifi is already connected :O");
    }
}