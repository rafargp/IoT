#include <Wire.h>
#include "RTClib.h"
#include <WiFi.h>
#include <HTTPClient.h>


const char *url = "http://rafargpiot.mybluemix.net/meusensor";
const char *ssid[3] = {"Rafaelrgp", "F106_CS10", "GE VISITANTE 2.4Ghz"};
const char *password[3] = {"rafael02", "Senai4.0", "gealunosenai"};
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

void setup()
{
  Serial.begin(115200);
  
  setupDHT(); delay(500);
  //setupWifi(); delay(500);  
  setupHeartRate(); delay(500);
  interruptStart(); delay(500);
}

void loop()
{
  readPulseSensor();
  readDHT();
}
