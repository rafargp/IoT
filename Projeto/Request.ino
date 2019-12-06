int MAX_TRY = 3;
void setupWifi()
{
    Serial.println("Iniciando Wifi");
    int contador = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        if (contador == 3)
        {
            contador = 0;
            MAX_TRY--;
        }
        if(MAX_TRY == 0){
          Serial.println("Wifi Não Conectado!");
          return;
        }

        Serial.print("Connecting to WiFi ");
        Serial.println(ssid[contador]);
        WiFi.begin(ssid[contador], password[contador]);
        delay(2000);
        contador++;
    }
    Serial.println("Wifi Iniciado");
}
int postData(String url, String parameters)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Wi-Fi is not connected!");
        return -1;
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
