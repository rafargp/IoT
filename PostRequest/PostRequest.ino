//Libraries
#include <WiFi.h>
#include <HTTPClient.h>

//Global Variables
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

    delay(2000);
}
void loop()
{
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