#include <Servo.h>

Servo servo; // Create a servo object

const int servoPin = 9; // Pin number where the servo signal wire is connected
const int ledPin = 12; // Pin number where the LED is connected



// These constants won't change. They're used to give names to the pins used:
const int analogInPin1 = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1;  // Analog input pin that the potentiometer is attached to
// const int analogOutPin = 9;  // Analog output pin that the LED is attached to

int sensorValue1 = 0;  // value read from the pot
int sensorValue2 = 0;  // value read from the pot
// int outputValue = 0;  // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  servo.attach(servoPin); // Attach the servo to the specified pin
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
  servo.write(112);
  digitalWrite(ledPin, LOW); 
  delay(100);// Turn the LED on (HIGH voltage)
}

void loop() {
  // read the analog in value:
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);
  
  Serial.print("sensor1 = ");Serial.print(sensorValue1);Serial.print(" sensor2 = ");Serial.print(sensorValue2);Serial.println("");
  
  if (sensorValue1 > 315){
    servo.write(70);delay(1000);Serial.println("----------------------");
    digitalWrite(ledPin, HIGH); delay(200);// Turn the LED on (HIGH voltage)
    digitalWrite(ledPin, LOW); delay(4000);// Turn the LED on (HIGH voltage)

  }

  else if (sensorValue2 > 100){
    servo.write(150);delay(1000);Serial.println("----------------------");
    digitalWrite(ledPin, HIGH); delay(200);// Turn the LED on (HIGH voltage)
    digitalWrite(ledPin, LOW); delay(4000);// Turn the LED on (HIGH voltage)

  }
  else {
    servo.write(112);delay(250);
    digitalWrite(ledPin, LOW); // Turn the LED off (LOW voltage)
  }
  


  delay(2);
}
