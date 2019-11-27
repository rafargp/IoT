int fadePin = 12; // pin to do fancy classy fading blink at each beat
int fadeRate = 0; // used to fade LED on with PWM on fadePin
int pulseSensorPin = 34;

volatile int BPM;               // used to hold the pulse rate
volatile int Signal;            // holds the incoming raw data
volatile int IBI = 600;         // holds the time between beats, must be seeded!
volatile boolean Pulse = false; // true when pulse wave is high, false when it's low
volatile boolean QS = false;    // becomes true when Arduoino finds a beat.
int lastBpm = 0;
int buttonPin = 14;

void setupHeartRate()
{
  pinMode(buttonPin, INPUT);
  pinMode(fadePin, OUTPUT); 
}

void read()
{

  if (digitalRead(buttonPin) == HIGH)
  {
    if (QS == true)
    {                                 // Quantified Self flag is true when arduino finds a heartbeat
      fadeRate = 255;                 // Set 'fadeRate' Variable to 255 to fade LED with pulse
      sendDataToProcessing('S', Signal); // send Processing the raw Pulse Sensor data
      sendDataToProcessing('B', BPM); // send heart rate with a 'B' prefix
      sendDataToProcessing('Q', IBI); // send time between beats with a 'Q' prefix
      QS = false;                     // reset the Quantified Self flag for next time
    }
  }
  yield();
}

/*
void ledFadeToBeat(){
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
  }
*/

void sendDataToProcessing(char symbol, int data)
{
  Serial.print(symbol);
  Serial.print(";");
  Serial.println(data); // the data to send culminating in a carriage return
}
