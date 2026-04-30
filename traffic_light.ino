/*
  Project: Non-Blocking Traffic Light System with Pedestrian Control
  Author: Rohan Bhardwaj
  Description:
  Arduino-based traffic light controller using millis() for non-blocking timing.
  Implements a state machine (RED, YELLOW, GREEN) with pedestrian button override.
  Demonstrates real-time embedded logic without using delay().
*/

// Pin Definitions
const int redLed = 9;
const int yellowLed = 10;
const int greenLed = 11;
const int whiteLed = 12;
const int button = 2;

// Button States
int buttonState = HIGH;
int lastButtonState = HIGH;

// Pedestrian Control
bool pedestrianRequest = false;

// Timing Variables
unsigned long previousMillis = 0;
const unsigned long redTime = 3000;
const unsigned long yellowTime = 1000;
const unsigned long greenTime = 3000;
const unsigned long whiteTime = 5000;

// LED Modes
int trafficState = 0;



void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(whiteLed, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  
}

void loop() {
  buttonState = digitalRead(button);

  // Detect button press (edge detection)
  if (buttonState == LOW && lastButtonState == HIGH){
    pedestrianRequest = true;
    previousMillis = millis();
    digitalWrite(whiteLed, HIGH);
  }

  // Pedestrian Mode
  if (pedestrianRequest) {
     digitalWrite(redLed, LOW);
     digitalWrite(yellowLed, LOW);
     digitalWrite(greenLed, LOW);
     digitalWrite(whiteLed, HIGH); 
     if (millis() - previousMillis >= whiteTime) {
     digitalWrite(whiteLed, LOW);  
    pedestrianRequest = false; //resets the pedestrian
     previousMillis = millis();
    }
  }

  // Traffic Light Mode
  else
    {
       
    switch (trafficState){
      case 0:
           // RED ON
       digitalWrite(redLed, HIGH);
       digitalWrite(yellowLed, LOW);
       digitalWrite(greenLed, LOW);
        if (millis()- previousMillis>=redTime){
          trafficState=1;
         previousMillis=millis();
         digitalWrite(redLed, LOW);
    }
  break;
    
      case 1:
           // YELLOW ON
       digitalWrite(redLed, LOW);
       digitalWrite(yellowLed, HIGH);
       digitalWrite(greenLed, LOW);
        if (millis()-previousMillis>=yellowTime){
          trafficState=2;
         previousMillis=millis();
         digitalWrite(yellowLed, LOW);
  }
  break;

       case 2:
            // GREEN ON
        digitalWrite(redLed, LOW);
        digitalWrite(yellowLed, LOW);
        digitalWrite(greenLed, HIGH);
         if (millis()-previousMillis>=greenTime){
           trafficState=0;
          previousMillis=millis();
          digitalWrite(greenLed, LOW);
  }
  break;
}
  }
  
  
  lastButtonState = buttonState;
  
}
