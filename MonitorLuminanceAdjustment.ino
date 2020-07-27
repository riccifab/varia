/*
  A sketch for adjusting the brighness of three screens on a behavioral rig
  Useful for setting the brighness to a certain lavel 
  and (more importantly) equalizing the brightness across the screens.
  
  Heavily based on Arduino's own AnalogInOutSerial.ino example
  
  Michael Krumin, June 2020

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Repeats three times

  The circuit (repeat three times for three monitors with different AO and AI channels:
  - potentiometer connected to analog pin 0 (1, 2).
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - Monitor backlight control/override conneted to PWM pin (marked with a '~' on the Arduino unit),
    ground to ground. 
    NOTE: different PWM outputs might have different frequencies - check board documentation

  
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPinLeft = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPinLeft = 9; // Analog output pin that the monitor backlight LED is attached to
const int analogInPinCenter = A1;  // Analog input pin that the potentiometer is attached to
const int analogOutPinCenter = 10; // Analog output pin that the monitor backlight LED is attached to
const int analogInPinRight = A2;  // Analog input pin that the potentiometer is attached to
const int analogOutPinRight = 11; // Analog output pin that the monitor backlight LED is attached to

int sensorValueLeft = 0;        // value read from the pot
int outputValueLeft = 0;        // value output to the PWM (analog out)
int sensorValueCenter = 0;        // value read from the pot
int outputValueCenter = 0;        // value output to the PWM (analog out)
int sensorValueRight = 0;        // value read from the pot
int outputValueRight = 0;        // value output to the PWM (analog out)

void setup() {
  // nothing to set up in this sketch
}

void loop() {
  // read the analog in values:
  sensorValueLeft = analogRead(analogInPinLeft);
  sensorValueCenter = analogRead(analogInPinCenter);
  sensorValueRight = analogRead(analogInPinRight);
  // map them to the range of the analog out:
  outputValueLeft = map(sensorValueLeft, 0, 1023, 0, 255);
  outputValueCenter = map(sensorValueCenter, 0, 1023, 0, 255);
  outputValueRight = map(sensorValueRight, 0, 1023, 0, 255);
  // change the analog out values:
  analogWrite(analogOutPinLeft, outputValueLeft);
  analogWrite(analogOutPinCenter, outputValueCenter);
  analogWrite(analogOutPinRight, outputValueRight);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
