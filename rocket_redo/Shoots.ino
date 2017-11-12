/********************************** checkShoots *********************************/

/**
 * This checks to see if the shoots need to be deployed
 * It also leaves the realy on for DROGUE_DELAY
 * before turning them back off
 */
 
void checkShoots(){
  
  if(rocketStage == 1){
    // deploy the drogue if 
    if     ((imu.calcAccel(imu.ax) < FREE_FALL_THRESH && imu.calcAccel(imu.ax) > -FREE_FALL_THRESH) && //We check to see if it is in FREE_FALL_THRESHold 
            (imu.calcAccel(imu.ay) < FREE_FALL_THRESH && imu.calcAccel(imu.ay) > -FREE_FALL_THRESH) && 
            (imu.calcAccel(imu.az) < FREE_FALL_THRESH && imu.calcAccel(imu.az) > -FREE_FALL_THRESH) &&
            (millis() - seconds > FREE_FALL_DELAY))  //We check the amount of time it was in free fall
       {
          digitalWrite(DROGUE_PIN, HIGH);
          rocketStage = 2;

          #if DEBUG
          Serial.println("Stage: 2");
          #endif
          
          seconds = millis();
      }
    else if(!(imu.calcAccel(imu.ax) < FREE_FALL_THRESH && imu.calcAccel(imu.ax) > -FREE_FALL_THRESH) && //We check to see if it is in FREE_FALL_THRESHold 
            !(imu.calcAccel(imu.ay) < FREE_FALL_THRESH && imu.calcAccel(imu.ay) > -FREE_FALL_THRESH) && 
            !(imu.calcAccel(imu.az) < FREE_FALL_THRESH && imu.calcAccel(imu.az) > -FREE_FALL_THRESH))
      {
          seconds = millis(); 
      }
  }

  if(rocketStage == 2){
    if((millis()-seconds) > DROGUE_DELAY){
      digitalWrite(DROGUE_PIN, LOW);
      rocketStage = 3;

      #if DEBUG
      Serial.println("Stage: 3");
      #endif
      
      seconds = millis();
    }
  }
  if(rocketStage == 3){
    if(bme280.calcAltitude(bme280.getPressure()) - startAlt < SHOOT_ALT){
        digitalWrite(SHOOT_PIN, HIGH);
        rocketStage = 4;

        #if DEBUG
        Serial.println("Stage: 4");
        #endif
        
        seconds = millis();
    }
  }
  if(rocketStage == 4){
    if(millis()-seconds > DROGUE_DELAY){
      digitalWrite(SHOOT_PIN, LOW);
      rocketStage = 5;

      #if DEBUG
      Serial.println("Stage: 5");
      #endif
      
      seconds = millis();
      speedCheck = bme280.calcAltitude(bme280.getPressure());
    }
  }
  if(rocketStage == 5){
    if(millis()-seconds > SPEED_CHECK){

      //When the rocket lands, we are going to close the file and stop the program. 
      if(((speedCheck - bme280.calcAltitude(bme280.getPressure()))/(SPEED_CHECK/1000)) < SPEED){
        rocketStage = 6;

        #if DEBUG
        Serial.println("Stage: 6");
        #endif
        
      }
      else{
        seconds = millis();
        speedCheck = bme280.calcAltitude(bme280.getPressure());
      }
    }
  }
  
  if(rocketStage == 6){
    myFile.flush();
    myFile.close();
    while(true){}
  }
}

