#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "RTClib.h"
#include "MPU9250.h"

MPU9250 mpu;
RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};

const char *ssid = "F106_CS10";
const char *password = "Senai4.0";
// const char *ssid = "GE VISITANTE 2.4Ghz";
// const char *password = "gealunosenai";
// const char *ssid = "Rafaelrgp";
// const char *password = "rafael02";
DateTime nowDateTime;

void setup()
{
    Serial.begin(115200);
    delay(4000);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
    Serial.println(WiFi.localIP());

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1)
            ;
    }
    rtc.adjust(DateTime(__DATE__, __TIME__));
}
void loop()
{
    getMPUData();
    getTime();
    //postData("http://rafargpiot.mybluemix.net/meusensor","Pulso="+String(getPulse())+"&temperatura="+String(getTemperature())+"&latitude=20&longitude=30&ip="+WiFi.localIP().toString());
}
void getMPUData()
{
    static uint32_t prev_ms = millis();
    if ((millis() - prev_ms) > 16)
    {
        mpu.update();
        //mpu.print();

        Serial.println("");
        Serial.print("Roll: ");
        Serial.println(mpu.getRoll());

        Serial.print("Pitch: ");
        Serial.println(mpu.getPitch());

        Serial.print("Yaw: ");
        Serial.println(mpu.getYaw());
        prev_ms = millis();
    }
}
int getPulse()
{
    int sensorValue = analogRead(34);
    Serial.println(sensorValue);
    return sensorValue;
}
void postData(String url, String parameters)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Error in WiFi connection");
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
}
float getTemperature()
{
    return rtc.getTemperature();
}
void getTime()
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
}
