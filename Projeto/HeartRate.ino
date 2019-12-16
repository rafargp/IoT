int pulseSensorPin =34;
int pulseLedPin =33;

volatile int BPM;               // used to hold the pulse rate
volatile int Signal;            // holds the incoming raw data
volatile int IBI = 600;         // holds the time between beats, must be seeded!
volatile boolean Pulse = false; // true when pulse wave is high, false when it's low
volatile boolean QS = false;    // becomes true when Arduoino finds a beat.
int lastBpm = 0;

void setupHeartRate()
{
  Serial.println("Iniciando PulseSensor");
  pinMode(pulseLedPin, OUTPUT); 
  Serial.println("PulseSensor Iniciado");
}
int getBPM(){
  if(QS) return BPM;
  return -1;
}
int getIBI(){
  if(QS) return IBI;
  return -1;
}
int getSignal(){
  return Signal;
}
void readPulseSensor()
{
    if (QS == true)
    {                                     
      sendDataToProcessing('S', Signal); 
      sendDataToProcessing('B', BPM); 
      sendDataToProcessing('Q', IBI); 
      QS = false;                     
  }
  yield();
}

void sendDataToProcessing(char symbol, int data)
{
  Serial.print(symbol);
  Serial.print(";");
  Serial.println(data);
}
