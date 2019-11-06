#include "RTClib.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "MPU9250.h"

//Global Variables
RTC_DS3231 rtc;
MPU9250 mpu;

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

  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    while (1)
      ;
  }

  if (rtc.lostPower())
  {
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  int contador = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    if (contador == 2)
    {
      contador = 0;
    }

    Serial.print("Connecting to WiFi ");
    Serial.println(ssid[contador]);
    WiFi.begin(ssid[contador], password[contador]);
    delay(1000);
  }
}

void loop()
{

  GetTemperature();
  GetTime();
  delay(3000);
}
DateTime GetTime()
{
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  return now;
}
float GetTemperature()
{
  float temperature = rtc.getTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");
  return temperature;
}
int postData(String url, String parameters)
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wi-Fi is not connected!");
    return;
  }
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded; charset=UTF-8");
  int httpResponseCode = http.POST(parameters);

  if (httpResponseCode > 0)
  {
    String response = http.getString();
    Serial.println(httpResponseCode);
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return httpResponseCode;
}
void discoveryDevicesI2C()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
  delay(1000);
}
void getMPUData()
{
  static uint32_t prev_ms = millis();
  if ((millis() - prev_ms) > 16)
  {
    mpu.update();
    Serial.print("Roll: ");
    Serial.println(mpu.getRoll());

    Serial.print("Pitch: ");
    Serial.println(mpu.getPitch());

    Serial.print("Yaw: ");
    Serial.println(mpu.getYaw());
    prev_ms = millis();
  }
}
