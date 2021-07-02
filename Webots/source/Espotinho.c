#include "utils.h"
#include <webots/robot.h>
#include <time.h>

#define TIME_STEP 13

#define DIST 100

int main(){
  wb_robot_init();

  int pwm = 15;
  int time = 1;

  int lineR = 0;
  int lineL = 0;
  int distR = 0;
  int distM = 0;
  int distL = 0;

  while(wb_robot_step(TIME_STEP) != -1){

    int actual_time = wb_robot_get_time();

    line_sensor(&lineR, &lineL);
    dist_sensor(&distR, &distM, &distL);

    while(lineR == 0 && lineL == 0){
      follow_enemy(pwm, 0, 0);
    }

    return_battle(pwm, 1, time);
    
    
  }
  wb_robot_cleanup();
  return 0;
}