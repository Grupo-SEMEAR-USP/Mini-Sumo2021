#ifndef utils_h
#define utils_h

#include <Arduino.h>

//Motor control
void motorR(int pwm);
void motorL(int pwm);

//Sensors
void dist_sensor(int *left, int *mid, int *right);
void line_sensor(int *left, int *right);

//Robot moves
void move(int pwm);
void rot_wheel(int pwm, bool sense);
void rot_robot(int pwm);
void arc_curve(int pwm, bool sense, float angle);

//Robot actions
void return_battle(int pwm, bool sense, double time);
void follow_enemy(int pwm, double dist, double time);

#endif