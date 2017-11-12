/*********************** readSensors ****************************/

/**
 * Reads all the sensors
 */
void readSensors(){
        imu.readGyro();
        imu.readMag();
        imu.readAccel();
}
