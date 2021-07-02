#include <webots/robot.h>
#include <stdio.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <time.h>

#include "utils.h"

#define TIME_STEP 13
#define DIST 100
#define LINE 250

// right engine control
void motorR(int pwm){
    WbDeviceTag right;
    right = wb_robot_get_device("motorR");

    wb_motor_set_position (right, INFINITY);
    wb_motor_set_velocity (right, pwm);
}

// left engine control
void motorL(int pwm){
    WbDeviceTag left;
    left = wb_robot_get_device("motorL");

    wb_motor_set_position (left, INFINITY);
    wb_motor_set_velocity (left, pwm);
}

void delay(int time, int atual){
    while (wb_robot_step(TIME_STEP) != -1) {
      if (wb_robot_get_time() > time + atual){
        break;
       }
  }
}

// left, mid and right distance sensors
void dist_sensor(int *left, int *mid, int *right){
    WbDeviceTag distL, distR, distM;

    distL = wb_robot_get_device("distL");
    distR = wb_robot_get_device("distR");
    distM = wb_robot_get_device("distM");

    wb_distance_sensor_enable(distL, TIME_STEP);
    wb_distance_sensor_enable(distR, TIME_STEP);
    wb_distance_sensor_enable(distM, TIME_STEP);

    *left = wb_distance_sensor_get_value(distL) <= LINE ? 1 : 0;
    *right = wb_distance_sensor_get_value(distR) <= LINE ? 1 : 0;
    *mid = wb_distance_sensor_get_value(distM) <= LINE ? 1 : 0;
}

// left and right line Sensors
void line_sensor(int *left, int *right){
    WbDeviceTag lineL, lineR;

    lineL = wb_robot_get_device("lineL");
    lineR = wb_robot_get_device("lineR");

    wb_distance_sensor_enable(lineL, TIME_STEP);
    wb_distance_sensor_enable(lineR, TIME_STEP);
    
    *left = wb_distance_sensor_get_value(lineL) <= LINE ? 1 : 0;
    *right = wb_distance_sensor_get_value(lineR) <= LINE ? 1 : 0;
}

// simple moves
void move(int pwm){
    motorR(pwm);
    motorL(pwm);
}

// rotation based on wheel axis
void rot_wheel(int pwm, int sense){

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
void arc_curve(int pwm, int sense, float angle){

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
void return_battle(int pwm, int sense, double time){

  move(-pwm);
  delay(time/100, wb_robot_get_time());
  rot_wheel(-pwm, sense);
  delay(time, wb_robot_get_time());
}

// attack enemy
void follow_enemy(int pwm, double dist, double time){
  int distL, distM, distR;
  double current_time, initial_time;

  dist_sensor(&distL, &distM, &distR);
  initial_time = wb_robot_get_time();
  current_time = initial_time;

  //while (current_time - initial_time <= time){
    current_time = wb_robot_get_time();

    if (distL == 1 &&  distM == 0 && distR == 0){
        motorL(0);
        motorR(pwm);
    }
    else if (distL == 0 &&  distM == 0 && distR == 1){
        motorL(pwm);
        motorR(0);
    }
    else if (distL == 1 &&  distM == 1 && distR == 0){
        motorL((int) pwm / 2);
        motorR(pwm);
    }
    else if (distL == 0 &&  distM == 1 && distR == 1){
        motorL(pwm);
        motorR((int) pwm / 2);
    }
    else if ((distL ==  0 &&  distM == 1 && distR == 0) || (distL == 1 &&  distM == 1 && distR == 1)){
        motorL(pwm);
        motorR(pwm);
    }
    else{
        move(pwm);
        return;
    }

  //}
}

//Arrumar dist