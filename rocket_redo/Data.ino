
/*************************** writeData ***************************/

/**
 * Writes the sensor data
 */
void writeData(){
  if(myFile){
        
        myFile.println((millis()-launchTime));
        myFile.print("Temp: ");
        myFile.print(bme280.getTemperature());
        myFile.println("C");

        myFile.print("Pressure: ");
        myFile.print(bme280.getPressure());
        myFile.println("Pa");

        myFile.print("Altitude: ");
        myFile.print(bme280.calcAltitude(bme280.getPressure()));
        myFile.println("m");

        myFile.print("Humidity: ");
        myFile.print(bme280.getHumidity());
        myFile.println("%");
        myFile.println();

        myFile.print("xGyro: ");
        myFile.println(imu.calcGyro(imu.gx), 6);
        myFile.print("yGyro: ");
        myFile.println(imu.calcGyro(imu.gy), 6);
        myFile.print("zGyro: ");
        myFile.println(imu.calcGyro(imu.gz), 6);
        myFile.println();

        myFile.print("xAccel: ");
        myFile.println(imu.calcAccel(imu.gx), 6);
        myFile.print("yAccel: ");
        myFile.println(imu.calcAccel(imu.gy), 6);
        myFile.print("zAccel: ");
        myFile.println(imu.calcAccel(imu.gz), 6);
        myFile.println();

        myFile.print("xMag: ");
        myFile.println(imu.calcMag(imu.mx), 6);
        myFile.print("yMag: ");
        myFile.println(imu.calcMag(imu.my), 6);
        myFile.print("zMag: ");
        myFile.println(imu.calcMag(imu.mz), 6);
        myFile.println();

        //Save the file 
        myFile.flush();
      }
}
