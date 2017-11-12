

/************************************ checkForLaunch ***********************************/

void checkForLaunch(){

  #if DEBUG
  Serial.println("Waiting to launch");
  #endif
  
  float accelVector = 0;
  while(accelVector < 1.5){
    accelVector = 0;
    for(int i = 0; i < 5; i++){
      imu.readAccel();
      accelVector += sqrt(pow(imu.calcAccel(imu.ax) , 2) + pow(imu.calcAccel(imu.ay), 2) + pow(imu.calcAccel(imu.az), 2));
    }
    accelVector /= 5;
  }

  #if DEBUG
  Serial.println("Launched!");
  #endif
  
  launchTime = millis();
}
