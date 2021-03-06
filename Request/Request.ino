//Libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include "RTClib.h"
#include "MPU9250.h"

//I2C Devices
#define MPU9250_ADDRESS 0x76 //Gyroscope
#define DS3231_ADDRESS 0x57  //Real Time Clock

//Global Variables
RTC_DS3231 rtc;
MPU9250 mpu;
DateTime nowDateTime;
char daysOfTheWeek[7][12] = {"Domingo", "Segunda", "Terça", "Quarta", "Quinta", "Sexta", "Sábado"};
const char *url = "http://rafargpiot.mybluemix.net/meusensor";
//const char *ssid = "Rafaelrgp";
// const char *password = "rafael02";
//const char *ssid = "F106_CS10";
//const char *password = "Senai4.0";
const char *ssid = "GE VISITANTE 2.4Ghz";
const char *password = "gealunosenai";

void setup()
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    delay(2000);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Connecting to WiFi..");
        delay(1000);
    }
    Serial.println("Connected to the WiFi network with local IP:" + WiFi.localIP().toString());

    // mpu.setup();
    delay(2000);
    // if (!rtc.begin())
    // {
    //     Serial.println("Couldn't find RTC");
    // }
    // else
    // {
    //     rtc.adjust(DateTime(__DATE__, __TIME__));
    // }
}
void loop()
{
    // discoveryDevicesI2C();
    // getMPUData();
    // getTime();
    for (int i = 0; i <= 100; i++)
    {
        String parameters = "";
        parameters += "pulso=" + String(i);
        parameters += "&temperatura=" + String(i);
        parameters += "&latitude=20";
        parameters += "&longitude=30";
        parameters += "&ip=" + WiFi.localIP().toString();
        postData(url, parameters);
        delay(100);
    }
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
int getPulse()
{
    int sensorValue = analogRead(18);
    Serial.println(sensorValue);
    return sensorValue;
}
void postData(String url, String parameters)
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
