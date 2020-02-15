#include <HardwareSerial.h>

HardwareSerial RxSerial(1);

void setup(){
  Serial.begin(9600);
  RxSerial.begin(9600,SERIAL_8N1,27,26);
}

void loop(){
  String received = "";
  while(RxSerial.available()){
    received = char(RxSerial.read());
    Serial.print(received);
  }
}
