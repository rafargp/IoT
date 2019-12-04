#include "RTClib.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "MPU9250.h"

const char *url = "http://rafargpiot.mybluemix.net/meusensor";
const char *ssid[3] = {"Rafaelrgp", "F106_CS10", "GE VISITANTE 2.4Ghz"};
const char *password[3] = {"rafael02", "Senai4.0", "gealunosenai"};
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sabado"};

void setup()
{
  Serial.begin(115200);


  Serial.println("Iniciando Wifi");
  SetupWifi();
  Serial.println("Wifi Iniciado");

  delay(3000);
  
  Serial.println("Iniciando PulseSensor");
  setupHeartRate();
  interruptStart();
  Serial.println("PulseSensor Iniciado");
}

void loop()
{
  readPulseSensor();
}
