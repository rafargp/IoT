int fadeRate = 0; // used to fade LED on with PWM on fadePin
int pulseSensorPin = 25;
int ledPin = 33;

volatile int BPM;               // used to hold the pulse rate
volatile int Signal;            // holds the incoming raw data
volatile int IBI = 600;         // holds the time between beats, must be seeded!
volatile boolean Pulse = false; // true when pulse wave is high, false when it's low
volatile boolean QS = false;    // becomes true when Arduoino finds a beat.
int lastBpm = 0;

void setupHeartRate()
{
  Serial.println("Iniciando PulseSensor");
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT); 
  Serial.println("PulseSensor Iniciado");
}

void readPulseSensor()
{
    if (QS == true)
    {                                 // Quantified Self flag is true when arduino finds a heartbeat
      fadeRate = 255;                 // Set 'fadeRate' Variable to 255 to fade LED with pulse
      sendDataToProcessing('S', Signal); // send Processing the raw Pulse Sensor data
      sendDataToProcessing('B', BPM); // send heart rate with a 'B' prefix
      sendDataToProcessing('Q', IBI); // send time between beats with a 'Q' prefix
      QS = false;                     // reset the Quantified Self flag for next time
  }
  yield();
}

void sendDataToProcessing(char symbol, int data)
{
  Serial.print(symbol);
  Serial.print(";");
  Serial.println(data); // the data to send culminating in a carriage return
}
