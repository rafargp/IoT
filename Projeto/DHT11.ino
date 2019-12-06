#include "DHT.h"

#define DHTPIN 13

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  Serial.println("Iniciando DHT");
  dht.begin();
  Serial.println("DHT Iniciado");
}
float getDHTTemperature(){
  return dht.readTemperature();
}
float getDHTHumidity(){
  return dht.readHumidity();
}
float getHeatIndex(){
  return dht.computeHeatIndex(getDHTTemperature(), getDHTHumidity(), false);
}
float getHeatIndex(float t, float h){
  return dht.computeHeatIndex(t, h, false);
}

void readDHT() {
  delay(2000);

  float h = getDHTHumidity();
  float t = getDHTTemperature();
    
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hic = getHeatIndex(t,h);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
}
