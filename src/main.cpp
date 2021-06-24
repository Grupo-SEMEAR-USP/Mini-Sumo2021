#include <Arduino.h>

// Define motorR
#define pwmR // pins to be defined
#define motorR1
#define motorR2

// Define motorL
#define pwmL // pins to be defined
#define motorL1
#define motorL2

// Functions
void motorR(int pwm);
void motorL(int pwm);

void setup()
{
}

void loop()
{
}

// rotation based on wheel axis --> based on the diagram below
void rot_wheel(int pwm, bool sense)
{
  /* 
  pwm > 0 and bool == 1; rotates clockwise (gira no sentido horário)
  pwm > 0 and bool == 0; reverse clockwise (gira de ré no sentido anti-horário)
  pwm < 0 and bool == 1; rotate counterclockwise (gira no sentido anti-horário)
  pwm < 0 and bool == 0; reverse counterclockwise (gira de ré no sentido anti-horário)
  */

  if (pwm > 0 && bool == 1)
  {
    motorR(0);
    motorL(pwm);
  }
  else if (pwm > 0 && bool == 0)
  {
    motorR(0);
    motorL(-pwm);
  }
  else if (pwm < 0 && bool == 1)
  {
    motorR(pwm);
    motorL(0);
  }
  else
  {
    motorR(-pwm);
    motorL(0);
  }
}

// rotation based on robot axis --> based on the diagram below
void rot_robot(int pwm, bool sense)
{
  /* 
  pwm > 0 and bool == 1; rotates clockwise (gira no sentido horário)
  pwm > 0 and bool == 0; reverse clockwise (gira de ré no sentido anti-horário)
  pwm < 0 and bool == 1; rotate counterclockwise (gira no sentido anti-horário)
  pwm < 0 and bool == 0; reverse counterclockwise (gira de ré no sentido anti-horário)
  */

  if (pwm > 0 && bool == 1)
  {
    motorR(-pwm);
    motorL(pwm);
  }
  else if (pwm > 0 && bool == 0)
  {
    motorR(pwm);
    motorL(-pwm);
  }
  else if (pwm < 0 && bool == 1)
  {
    motorR(pwm);
    motorL(-pwm);
  }
  else
  {
    motorR(-pwm);
    motorL(pwm);
  }
}

void move(int pwm)
{
  motorR(pwm); // call the function of the engines to make a decision
  motorL(pwm);
}

// right engine control --> based on the diagram below
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
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, LOW);
  }
  else if (pwm < 0)
  {
    analogWrite(pwmR, -pwm);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }
  else
  {
    analogWrite(pwmR, pwm);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
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
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, LOW);
  }
  else if (pwm < 0)
  {
    analogWrite(pwmL, -pwm);
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
  }
  else
  {
    analogWrite(pwmL, pwm);
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, HIGH);
  }
}