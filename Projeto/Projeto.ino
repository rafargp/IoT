#include "RTClib.h"
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

#ifndef ESP8266
  while (!Serial)
#endif

    Serial.begin(9600);

  delay(3000);
}

void loop()
{
}