/**All functions are based on the diagram below**/

#include "utils.h"
#include <Arduino.h>

#define maxLine 740

// right engine control
void motorR(int pwm){
  /* 
  motorR1 == 0 and motorR2 == 0; idle (parado)
  motorR1 == 0 and motorR2 == 1; go forward (vai pra frente)
  motorR1 == 1 and motorR2 == 0; back up (dá ré)
  motorR1 == 1 and motorR2 == 1; stalled (motor travado)
  */

  if (pwm == 0){
    digitalWrite(motorR1, LOW);
    digitalWrite(motorR2, LOW);
  }
  else if (pwm < 0){
    analogWrite(pwmR, -pwm);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
  }
  else{
    analogWrite(pwmR, pwm);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
  }
}

// left engine control --> based on the diagram below
void motorL(int pwm){
  /* 
  motorL1 == 0 and motorL2 == 0; idle (parado)
  motorL1 == 0 and motorL2 == 1; go forward (vai pra frente)
  motorL1 == 1 and motorL2 == 0; back up (dá ré)
  motorL1 == 1 and motorL2 == 1; stalled (motor travado)
  */

  if (pwm == 0){
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, LOW);
  }
  else if (pwm < 0){
    analogWrite(pwmL, -pwm);
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2, LOW);
  }
  else{
    analogWrite(pwmL, pwm);
    digitalWrite(motorL1, LOW);
    digitalWrite(motorL2, HIGH);
  }
}

// left, mid and right distance sensors
void dist_sensor(int *left, int *mid, int *right){
  *left = digitalRead(distL);
  *mid = digitalRead(distM);
  *right = digitalRead(distR);
}

// left and right line Sensors
void line_sensor(int *left, int *right){
  //Checking if the reading is white 
  *left = analogRead(lineL) <= maxLine ? 1 : 0;
  *right = analogRead(lineR) <= maxLine ? 1 : 0;
}

// simple moves
void move(int pwm){
  motorR(pwm);
  motorL(pwm);
}

// rotation based on wheel axis
void rot_wheel(int pwm, bool sense){
  /* 
  pwm > 0 and bool == 1; rotates clockwise (gira no sentido horário)
  pwm > 0 and bool == 0; reverse clockwise (gira de ré no sentido anti-horário)
  pwm < 0 and bool == 1; rotate counterclockwise (gira no sentido anti-horário)
  pwm < 0 and bool == 0; reverse counterclockwise (gira de ré no sentido anti-horário)
  */

  if (pwm > 0 && sense == 1){
    motorR(0);
    motorL(pwm);
  }
  else if (pwm > 0 && sense == 0){
    motorR(0);
    motorL(-pwm);
  }
  else if (pwm < 0 && sense == 1){
    motorR(pwm);
    motorL(0);
  }
  else{
    motorR(-pwm);
    motorL(0);
  }
}

// rotation based on robot axis
void rot_robot(int pwm){
  /* 
  pwm > 0; rotates clockwise (gira no sentido horário)
  pwm < 0; rotate counterclockwise (gira no sentido anti-horário)
  */

  if (pwm > 0){
    motorR(-pwm);
    motorL(pwm);
  }
  else{
    motorR(-pwm);
    motorL(pwm);
  }
}

// angular curve
void arc_curve(int pwm, bool sense, float angle){
  /*
  pwm > 0 and sense == 1; clockwise forward curve (curva no sentido horário para frente)
  pwm > 0 and sense == 0; clockwise back curve (curva no sentido horário para trás)
  pwm < 0 and sense == 1; counterclockwise forward curve (curva no sentido anti-horário para frente)
  pwm < 0 and sense == 0; counterclockwise back curve (curva no sentido anti-horário para trás)
  */

  if (sense == 1){
    motorL(pwm);
    motorR((int) pwm * angle);
  }
  else{
    motorL((int) pwm * angle);
    motorR(pwm);
  }
}

// remove robot from the white line
void return_battle(int pwm, bool sense, double time){
  move(-pwm);
  delay(time/100);
  rot_wheel(-pwm, sense);
  delay(time);
}

// attack enemy
void follow_enemy(int pwm, double dist, double time){
  int distL, distM, distR;
  double current_time, initial_time;

  dist_sensor(distL, distM, distR);
  initial_time = millis();
  current_time = initial_time;

  while (current_time - initial_time <= time){
    //Update current_time
    current_time = millis();

    /*Verify location of follow_enemy*/
    //Only left sensor is hight
    if (distL == 1 &&  distM == 0 && distR == 0){
      motorL(0);
      motorR(pwm);
    }
    //Only right sensor is hight
    else if (distL == 0 &&  distM == 0 && distR == 1){
      motorL(pwm);
      motorR(0);
    }
    //Only left and mid sensor is hight
    else if (distL == 1 &&  distM == 1 && distR == 0){
      motorL((int) pwm / 2);
      motorR(pwm);
    }
    //Only right and mid sensor is hight
    else if (distL == 0 &&  distM == 1 && distR == 1){
      motorL(pwm);
      motorR((int) pwm / 2);
    }
    //Only mid sensor is hight or All sensor is hight
    else if (distL ==  &&  distM == 1 && distR == 0 || distL == 1 &&  distM == 1 && distR == 1){
      motorL(pwm);
      motorR(pwm);
    }
    //None sensor is hight
    else{
      return;
    }

  }
}
