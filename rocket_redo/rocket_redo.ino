/****************** Settings for pins ect ********************/ 

/**
 * Will serial print out the rocket
 * stages when connected to a computer
 */
#define DEBUG false

/**
 * Amount of time in free fall before the drogue is deployed
 */
#define FREE_FALL_DELAY 100

/** 
 *  The tolerance for the accelerometer in detecting freeFall
 */
#define FREE_FALL_THRESH 0.2

/**
 * The amount of time to light the charge for the droube parishoot in milliseconds
 */
#define DROGUE_DELAY 5000

/**
 * The pin for igniting the drogue's charge
 */
#define DROGUE_PIN 4

/**
 * the pin for the shoot
 */
#define SHOOT_PIN 5
 
/**
 * The pin that needs to be pulLED to start the calibration and launch 
 */
#define LAUNCH_PIN 8

/**
 * time waited until calibration starts and the rocket is primed for launch
 */
#define DELAY_TILL_CAL 5000

/**
 * The SD clock pin
 */
#define CS_PIN 6

/**
 *  Deploy point for the second shoot in meters
 */
#define SHOOT_ALT 10

/**
 * LED indicator
 */
#define LED 9

/**
 * time inbetween checking for the rocket to land
 */

#define SPEED_CHECK 2000

/**
 * The speed that we are looking for to check for the rocket to land
 */

#define SPEED 2


/********************** Libraries *********************/
#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>
#include <SD.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include "Seeed_BME280.h"

/************** Altimeter object **************/

BME280 bme280;

/************** IMU Start UP ******************/
//////////////////////////
// LSM9DS1 Library Init //
//////////////////////////
// Use the LSM9DS1 class to create an object. [imu] can be
// named anything, we'll refer to that throught the sketch.
LSM9DS1 imu;

///////////////////////
// Example I2C Setup //
///////////////////////
// SDO_XM and SDO_G are both pulLED high, so our addresses are:
#define LSM9DS1_M 0x1E // Would be 0x1C if SDO_M is LOW
#define LSM9DS1_AG  0x6B // Would be 0x6A if SDO_AG is LOW

/**
 * Timer between stages
 */
unsigned long seconds = 0;

/**
 * Time since launch 
 */
long launchTime;

/**
 * the stage of the rocket
 */

int rocketStage = 1;

/**
 * The starting Altitude 
 */
float startAlt = 0;

/**
 * 
 */
float speedCheck;

/**
 * the File we are writing to
 */
File myFile;

/************************* SET UP ********************************/

void setup() 
{
  sensorStarUp();

  #if DEBUG
  Serial.println("waiting to pull the pin");
  #endif
  
  //wait for the launch pin to be pulLED
  while(digitalRead(LAUNCH_PIN) == HIGH){}
  
  digitalWrite(LED, LOW);
  delay(DELAY_TILL_CAL);
  sensorCalibrate();
  checkForLaunch();
  seconds = millis();

}

void loop()
{
  readSensors();
  writeData();
  checkShoots();
}
