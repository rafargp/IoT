#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "RTClib.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"


const char *url = "http://rafargpiot.mybluemix.net/meusensor";
const char *ssid[3] = {"Rafaelrgp", "F106_CS10", "GE VISITANTE 2.4Ghz"};
const char *password[3] = {"rafael02", "Senai4.0", "gealunosenai"};
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

void setup()
{
  Serial.begin(115200);
  setupBMP(); delay(1000);
  setupDHT(); delay(1000);
  //setupWifi(); delay(1000);  
  setupHeartRate(); delay(1000);
  interruptStart(); delay(1000);  
}

void loop()
{
  readBMP();
  readPulseSensor();
  readDHT();
  discoveryDevicesI2C();

}
