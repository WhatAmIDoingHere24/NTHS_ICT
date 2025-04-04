#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h> 
#include <ArduinoJson.h>
#include <Timer.h>
#include <MPU6050.h>
#include <I2Cdev.h>


MPU6050 mpu;
Timer time;
bool deviceConnected = false;
JsonDocument txValue;

#define SERVICE_UUID = NULL //theres a UUID for each esp32 from the FCC we jsut put that data here and copy it below
//defines the output format of the mpu data
#define OUTPUT_READABLE_ACCELGYRO

//begin the bluetooth low energy device
BLE.begin();

//set device BLE device values for transmission
BLE.setAdvertisedServiceUuid(SERVICE_UUID);
BLE.setAdvertisedService(SERVICE_UUID);
BLE.setLocalName("NTHS Paddle");
BLE.setDeviceName("NTHS Paddle ESP32");


While(!bleDevice.connected()){
  Serial.println("Looking for connection...");
  //begin advertising the BLE device
  BLE.advertise();
  if(bleDevice.connected()){
    //stop advertising the BLE device
    BLE.stopAdvertise()
    Serial.println("the signal strength of the connection is: " {BLE.rssi()});
    deviceConnected = true;
    break;
  }
}








bool connectedTimer() {
  if(deviceConnected) {
      timer.start();
      if(time.read() == 3000) {
        if(deviceConnected) {
          return true;
          time.stop();
        } else {
          time.stop();
          return false;
        }
      }
  }
}

//create and retrieve current offset values
int accelX = mpu.getXAccelOffset();
int accelY = mpu.getYAccelOffset();
int accelZ = mpu.getZAccelOffset();
int gyroX = mpu.getXAccelOffset();
int gyroY = mpu.getYAccelOffset();
int gyroZ = mpu.getZAccelOffset();

//create the JSON format
JsonDocument mpuData;

mpuData["accelration_x"] = accelX;
mpuData["accelration_y"] = accelY;
mpuData["accelration_z"] = accelZ;
mpuData["gyro_x"] = gyroX;
mpuData["gyro_y"] = gyroY;
mpuData["gyro_z"] = gyroZ;

//serializeJson(mpuData, Serial);




void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  if(I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE){
    Wire.begin();
  } elif (I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE) {
    Fastwire::setup(400, true);
  }

  Serial.println("starting MPU");

  mpu.initialize();
  Serial.println("running test.....");
  if(mpu.testConnection() == false){
    Serial.println("testing failed");
  } else {
    Serial.println("MPU6050; 200")
  }

  Serial.println("about to Zero, Hold device in desired pos for 5 seconds to accuratlly zero");
  Delay(3000);
  mpu.setXAccelOffset(0); 
  mpu.setYAccelOffset(0); 
  mpu.setZAccelOffset(0);
  Serial.println("accelration is zero'd");
  mpu.setXGyroOffset(0);  
  mpu.setYGyroOffset(0); 
  mpu.setZGyroOffset(0);  
  Serial.println("Gyroscope is zero'd");
  Serial.println("Device is now zeroed to current pos");
  Serial.println("Setting current values");
  
  



void loop() {
  // put your main code here, to run repeatedly:
  //get all the current values form the MPU
  accelX = mpu.getXAccelOffset();
  accelY = mpu.getYAccelOffset();
  accelZ = mpu.getZAccelOffset();
  gyroX = mpu.getXGyroOffset();
  gyroY = mpu.getYGyroOffset();
  gyroZ = mpu.getZGyroOffset();
  
  //print all current values
  Serial.println(accelX + accelY + accelZ + gyroX + gyroY + gyroZ);
  
  if(connectedTimer()) {//checks that the device has been connected for 3 seconds
    txValue = mpuData["gyro_x"]["gyro_y"]["gyro_z"]["accelration_x"]["accelration_y"]["accelration_z"]; //txValue will transmit all the current values of mpuData
    //data to send
    bleCharacteristic(SERVICE_UUID, txValue);
    
  }






}
