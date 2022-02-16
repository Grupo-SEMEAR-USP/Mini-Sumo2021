#include <Arduino.h>
#include "utils.h"

// Define LED
#define LED

// Define motorR
#define pwmR // pins to be defined
#define motorR1
#define motorR2

// Define motorL
#define pwmL // pins to be defined
#define motorL1
#define motorL2

// Define line sensor
#define lineR
#define lineL

// Define distance sensor 
#define distR
#define distM
#define distL

void setup(){
  /*         PINOUT CONFIG           */
  /*         OUTPUT         */
  pinMode(LED, OUTPUT);     // led
 
  // PINS FOR motorR
  pinMode(pwmR, OUTPUT);    // right motor power
  pinMode(motorR1, OUTPUT); // right motor dir.
  pinMode(motorR2, OUTPUT); // right motor dir.
 
  /*         INPUT         */
  // PINS FOR motorL
  pinMode(pwmL, OUTPUT);     // left motor power
  pinMode(motorL1, OUTPUT);  // left motor dir.
  pinMode(motorL2, OUTPUT);  // left motor dir.
  
  // PINS FOR LINE SENSOR
  pinMode(lineL, INPUT); 
  pinMode(lineR, INPUT); 
 
  // distance sensor
  pinMode(distR, INPUT); 
  pinMode(distL, INPUT); 
 
  /*         INITIAL CONDIDIONS           */
  digitalWrite(LED, LOW); 
  motorR(0); 
  motorL(0); 
}

void loop(){

}