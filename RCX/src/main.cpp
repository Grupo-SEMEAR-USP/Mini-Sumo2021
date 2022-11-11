#include <Arduino.h>

// Define LED
// #define LED

// Define motorR
#define pwmR 19 // pins to be defined
#define motorR1 17
#define motorR2 18

// Define motorL
#define pwmL 26 // pins to be defined
#define motorL1 25
#define motorL2 4

// Define microStart
#define microStart 32

// Define line sensor
// #define lineR
// #define lineL

// Define distance sensor
// #define distR
// #define distM
// #define distL

// right engine control
void motorR(int pwm)
{
    /*
    motorR1 == 0 and motorR2 == 0; idle (parado)
    motorR1 == 0 and motorR2 == 1; go forward (vai pra frente)
    motorR1 == 1 and motorR2 == 0; back up (dá ré)
    motorR1 == 1 and motorR2 == 1; stalled (motor travado)
    */

    if (pwm == 0)
    {
        digitalWrite(motorR1, HIGH);
        digitalWrite(motorR2, HIGH);
    }
    else if (pwm > 0)
    {
        digitalWrite(pwmR, HIGH);
        digitalWrite(motorR1, HIGH);
        digitalWrite(motorR2, LOW);
    }
    else
    {
        digitalWrite(pwmR, HIGH);
        digitalWrite(motorR1, LOW);
        digitalWrite(motorR2, HIGH);
    }
}

// left engine control --> based on the diagram below
void motorL(int pwm)
{
    /*
    motorL1 == 0 and motorL2 == 0; idle (parado)
    motorL1 == 0 and motorL2 == 1; go forward (vai pra frente)
    motorL1 == 1 and motorL2 == 0; back up (dá ré)
    motorL1 == 1 and motorL2 == 1; stalled (motor travado)
    */

    if (pwm == 0)
    {
        digitalWrite(motorL1, HIGH);
        digitalWrite(motorL2, HIGH);
    }
    else if (pwm > 0)
    {
        digitalWrite(pwmL, HIGH);
        digitalWrite(motorL1, HIGH);
        digitalWrite(motorL2, LOW);
    }
    else
    {
        digitalWrite(pwmL, HIGH);
        digitalWrite(motorL1, LOW);
        digitalWrite(motorL2, HIGH);
    }
}

// left and right line Sensors
void line_sensor(int *left, int *right){
    //Checking if the reading is white 
    *left = analogRead(lineL) <= HIGH ? 1 : 0;
    *right = analogRead(lineR) <= HIGH ? 1 : 0;
}

// simple moves
void move(int pwm){
    motorR(pwm);
    motorL(pwm);
}

void setup()
{
    Serial.begin(115200);
    /*         PINOUT CONFIG           */
    /*         OUTPUT         */
    // pinMode(LED, OUTPUT);     // led

    // PINS FOR motorR
    pinMode(pwmR, OUTPUT);    // right motor power
    pinMode(motorR1, OUTPUT); // right motor dir.
    pinMode(motorR2, OUTPUT); // right motor dir.

    // PINS FOR motorL
    pinMode(pwmL, OUTPUT);    // left motor power
    pinMode(motorL1, OUTPUT); // left motor dir.
    pinMode(motorL2, OUTPUT); // left motor dir.

    /*         INPUT         */
    // PINS FOR microStart
    pinMode(microStart, INPUT); // microStart  

    // PINS FOR LINE SENSOR
    // pinMode(lineL, INPUT);
    // pinMode(lineR, INPUT);

    // DISTANCE SENSOR
    // pinMode(distR, INPUT);
    // pinMode(distL, INPUT);

    /*         INITIAL CONDITIONS           */
    // digitalWrite(LED, LOW);

    while(digitalRead(microStart) == 0)
    {
        motorR(0);
        motorL(0);
    }
}

void loop()
{
    while(digitalRead(microStart) == 1){
        move(255);
    }

    move(0);
}
