#include <HardwareSerial.h>

HardwareSerial TxSerial(1);

void setup(){
  Serial.begin(115200);
  TxSerial.begin(1600,SERIAL_8N1, 12,14);
}

void loop(){
  TxSerial.flush();
  TxSerial.println("Aqui: "+String(millis()));
  delay(1000);
}
