// Multiple Filters Example
// Show how to make multiple filter objects in a single sketch.

#include <FIR.h>

// Make two instances of the FIR filter. The first is a 13 element float
// and the second is a 10 point float. The 13 element filter is a 2 Hz low-pass
// for a 10 SPS signal and the 10 element is a moving average over one second.

  FIR<float, 13> fir_lp;
FIR<float, 10> fir_avg;

// Some data that is a 0.2 Hz sine wave with a 0.3 Hz sine wave noise on it.
float data[500];

void setup() {
  Serial.begin(9600); // Start a serial port
   // Use an online tool to get these such as http://t-filter.engineerjs.com
  // This filter rolls off after 2 Hz for a 10 Hz sampling rate.
  float coef_lp[13] = { 660, 470, -1980, -3830, 504, 10027, 15214,
                    10027, 504, -3830, -1980, 470, 660};

  // For a moving average we use all ones as coefficients.
  float coef_avg[10] = {1., 1., 1., 1., 1., 1., 1., 1., 1., 1.};

  // Set the coefficients
  fir_lp.setFilterCoeffs(coef_lp);
  fir_avg.setFilterCoeffs(coef_avg);

  // Set the gain
  Serial.print("Low Pass Filter Gain: ");
  Serial.println(fir_lp.getGain());
  Serial.print("Moving Average Filter Gain: ");
  Serial.println(fir_avg.getGain());
}

void loop() {
  long startTime = millis();
  int counter = 0;
  while(millis() - startTime <=  1000) {
      startTime = millis();
      data[0] = analogRead(32);
      counter++;
  }
  Serial.print(counter);
/*  
  for (int i=0; i < 500; i++) {    
    Serial.println(fir_lp.processReading(data[i]));
    //delay(1); // Simulate real-time 10 Hz data collection
  }
*/

  delay(3000);
}
