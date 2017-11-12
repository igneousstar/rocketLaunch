/************************** sensorCalibrate ****************************/

/**
 * This is meant to account for the gyro drift
 */

void sensorCalibrate(){
  float drift = 0;

  myFile.println("/***** Gyro Calibration *****/");
  for(int i = 0; i < 30; i++){
    imu.readGyro();
    drift += imu.calcGyro(imu.gx);
  }
  drift /= 30;

  myFile.print("Xdrift: ");

  myFile.println(drift, 6);
  drift = 0;

  for(int i = 0; i < 30; i++){
    imu.readGyro();
    drift += imu.calcGyro(imu.gy);
  }

  drift /= 30;
  myFile.print("Ydrift");

  myFile.println(drift, 6);
  drift = 0;

  for(int i = 0; i < 30; i++){
    imu.readGyro();
    drift += imu.calcGyro(imu.gz);
  }

  drift /= 30;
  myFile.print("Zdrift");

  myFile.println(drift, 6);

  for(int i = 0; i < 30; i++){
      startAlt += bme280.calcAltitude(bme280.getPressure());
  }
  startAlt /= 30;

  Serial.println("Sensors Calibrated");
  
  myFile.print("Start altitude: ");
  myFile.println(startAlt);
  myFile.println("---------------");
  myFile.println();
  myFile.flush();
}

