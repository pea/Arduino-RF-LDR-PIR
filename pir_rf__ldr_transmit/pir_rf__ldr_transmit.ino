#include <RCSwitch.h>

RCSwitch RFSwitch = RCSwitch();

int calibrationTime = 30; // Time to give for the PIR to calibrate
int ldrbreakpoint = 400; // Level of resistence of LDR to trigger on/off
int rfpulselength = 399; // Pulse length to use for RF transmitter

int pirPin = 2; // Digital pin connected to the PIR sensor
int ldrpin = A0; // Analogue pin connected to LDR
int rfpin = 10; // Digital pin connected to RF transmitter

void setup() {

  Serial.begin(9600);

  RFSwitch.enableTransmit(rfpin);
  RFSwitch.setPulseLength(rfpulselength);

  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);

  // Allow time for the PIR to calibrate

  Serial.print("Calibrating");
  Serial.print("\n");

  for(int i = 0; i < calibrationTime; i++){
    delay(1000);
  }
  delay(50);

  Serial.print("Calibrated");
  Serial.print("\n");

}

void loop() {
  
  int ldrreading = analogRead(ldrpin);
  
  // If PIR detects motion and the LDR has a low reading (low light) turn light on
  
  if(digitalRead(pirPin) == HIGH && ldrreading < ldrbreakpoint){
    Serial.print("Turning on");
    Serial.print("\n");
    RFSwitch.send("010001010100010101010101"); // Send binary code to turn on light
    delay(1000);
  }
  
  // If the LDR has a high reading (high light) turn light off 
  
  if(ldrreading > ldrbreakpoint){
    Serial.print("Turning off");
    Serial.print("\n");
    RFSwitch.send("010001010100010101010100"); // Send binary code to turn off light
    delay(1000);
  }
  
}

