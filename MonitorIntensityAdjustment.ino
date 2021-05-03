/*
  A sketch for adjusting the intensity of three screens
  Useful for setting the intensity to a certain lavel 
  and (more importantly) equalizing it across the three screens.
  
  Michael Krumin, May 2021
  - Reads an analog input pin (the value can be controlled by a potentiometer)
  - Calculates the On/Off durations
  - Runs through a single cycle of On/Off on all three screens
  
  The circuit (repeat three times for three monitors with different AO and AI channels:
  - Potentiometer connected to analog pin 0 (1, 2).
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - Monitor backlight control/override connected to a digital output pin, ground to ground. 
    NOTE: not using PWM output to be able to control the frequency
  
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPinLeft = A0;  // Analog input pin that the potentiometer is attached to
const int digitalOutPinLeft = 13; // Digital output pin that the monitor backlight LED is attached to
const int analogInPinCenter = A1;  // Analog input pin that the potentiometer is attached to
const int digitalOutPinCenter = 12; // Digital output pin that the monitor backlight LED is attached to
const int analogInPinRight = A2;  // Analog input pin that the potentiometer is attached to
const int digitalOutPinRight = 11; // Digital output pin that the monitor backlight LED is attached to

int freq = 200;                 // Target frequency of PWM 
int sensorValueLeft = 0;        // value read from the pot
long durLeft = 0;        // duration of left monitor ON
int sensorValueCenter = 0;        // value read from the pot
long durCenter = 0;        // duration of center monitor ON
int sensorValueRight = 0;        // value read from the pot
long durRight = 0;        // duration of right monitor ON

long cycleDuration = 0;
int firstPin = 0;
int secondPin = 0;
int thirdPin = 0;
long durFirst = 0;
long durSecond = 0;
long durThird = 0;
long waitFirst = 0;
long waitSecond = 0;
long waitThird = 0;
long waitEnd = 0;

void setup() {
  // setting up digital channels to output and set them to LOW
  pinMode(digitalOutPinLeft, OUTPUT); 
  pinMode(digitalOutPinCenter, OUTPUT); 
  pinMode(digitalOutPinRight, OUTPUT);
  digitalWrite(digitalOutPinLeft, LOW); 
  digitalWrite(digitalOutPinCenter, LOW); 
  digitalWrite(digitalOutPinRight, LOW); 
}

void loop() {
  // read the analog in values:
  sensorValueLeft = analogRead(analogInPinLeft);
  sensorValueCenter = analogRead(analogInPinCenter);
  sensorValueRight = analogRead(analogInPinRight);
  // map the values to durations:
  cycleDuration = round(1e6/freq); // microseconds
  durLeft = map(sensorValueLeft, 0, 1023, 0, cycleDuration);
  durCenter = map(sensorValueCenter, 0, 1023, 0, cycleDuration);
  durRight = map(sensorValueRight, 0, 1023, 0, cycleDuration);
  // complicated way to figure out which pins to switch off when
  if (durLeft < durCenter){
    if (durLeft < durRight){
      firstPin = digitalOutPinLeft;
      durFirst = durLeft;
      if (durRight < durCenter){
        secondPin = digitalOutPinRight;
        durSecond = durRight;
        thirdPin = digitalOutPinCenter;
        durThird = durCenter;
      }
      else{
        secondPin = digitalOutPinCenter;
        durSecond = durCenter;
        thirdPin = digitalOutPinRight;
        durThird = durRight;
      }
    }
    else{
      firstPin = digitalOutPinRight;
      durFirst = durRight;
      secondPin = digitalOutPinLeft;
      durSecond = durLeft;
      thirdPin = digitalOutPinCenter;
      durThird = durCenter;
    }
  }
  else{
    if (durCenter < durRight){
      firstPin = digitalOutPinCenter;
      durFirst = durCenter;
      if (durRight < durLeft){
        secondPin = digitalOutPinRight;
        durSecond = durRight;
        thirdPin = digitalOutPinLeft;
        durThird = durLeft;
      }
      else{
        secondPin = digitalOutPinLeft;
        durSecond = durLeft;
        thirdPin = digitalOutPinRight;
        durThird = durRight;
      }
    }
    else{
      firstPin = digitalOutPinRight;
      durFirst = durRight;
      secondPin = digitalOutPinCenter;
      durSecond = durCenter;
      thirdPin = digitalOutPinLeft;
      durThird = durLeft;
    }
  }

  // calculating waiting times (currently assuming operations take no time)
  // (for higher frequencies need to take the digital operation and calculation durations into account)
  waitFirst = durFirst;
  waitSecond = durSecond - durFirst;
  waitThird = durThird - durSecond;
  waitEnd = cycleDuration - durThird;
  
  // Flip the outputs up, wait required time and flip them down:
  digitalWrite(firstPin, HIGH);
  digitalWrite(secondPin, HIGH);
  digitalWrite(thirdPin, HIGH);
  delayMicroseconds(waitFirst);
  digitalWrite(firstPin, LOW);
  delayMicroseconds(waitSecond);
  digitalWrite(secondPin, LOW);
  delayMicroseconds(waitThird);
  digitalWrite(thirdPin, LOW);
  
  // wait before the next loop
  delayMicroseconds(waitEnd);
}
