#define TIME_STEP 13

#define DIST 100

int main(){
  wb_robot_init();

  while(wb_robot_step(TIME_STEP) != -1){

    int actual_time = wb_robot_get_time();

    int lineR = 0;
    int lineL = 0;
    int distR = 0;
    int distM = 0;
    int distL = 0;
    
    line_sensor(&lineR, &lineL);
    dist_sensor(&distR, &distM, &distL);

    printf("/n/n");
    printf("/n Distance Sensor (Right): %d /n", distR);
    printf("/n Distance Sensor (Middle): %d /n", distM);
    printf("/n Distance Sensor (Left): %d /n", distL);



    }
  wb_robot_cleanup();
  return 0;
}