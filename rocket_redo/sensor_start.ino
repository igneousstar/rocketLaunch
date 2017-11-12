

void sensorStarUp(){
  
  //Make sure the DROGUE_PIN is set to low to avoid accidentally setting off the charge
  pinMode(DROGUE_PIN, OUTPUT);
  digitalWrite(DROGUE_PIN, LOW);

  //Make sure the SHOOT_PIN is set to low to avoid accidentally setting off the charge
  pinMode(SHOOT_PIN, OUTPUT);
  digitalWrite(SHOOT_PIN, LOW);
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  pinMode(LAUNCH_PIN, INPUT);

  Serial.begin(9600);
  
  delay(500);

  //Start the file
  if(!SD.begin(CS_PIN)){

    #if DEBUG
    Serial.println("INITIALIZATION FAILED");
    #endif
    
  }  
  delay(500);
  myFile = SD.open("test.txt",FILE_WRITE);
  
  if(myFile){
    digitalWrite(LED, HIGH);
  }
  delay(2000);
  
  
  // Before initializing the IMU, there are a few settings
  // we may need to adjust. Use the settings struct to set
  // the device's communication mode and addresses:
  imu.settings.device.commInterface = IMU_MODE_I2C;
  imu.settings.device.mAddress = LSM9DS1_M;
  imu.settings.device.agAddress = LSM9DS1_AG;
  // The above lines will only take effect AFTER calling
  // imu.begin(), which verifies communication with the IMU
  // and turns it on.

  //If the imu doesn't want to work, tell the user and don't move on
  if(!imu.begin()){
      digitalWrite(LED, LOW);
      if(myFile){
        myFile.println("NO IMU DATA AVAILABLE");
      }
    }

  if(!bme280.init()){
      digitalWrite(LED, LOW);
      if(myFile){
      myFile.println("NO BARAMETER, WE ARE GONNA CRASH AND DIE!!!!!!!!!!!!");
    }
  } 
}


