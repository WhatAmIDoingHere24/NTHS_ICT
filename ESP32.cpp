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
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;
int txValue = 0;

#define SERVICE_UUID = NULL //theres a UUID for each esp32 from the FCC we jsut put that data here and copy it below
#define CHARACTERISTIC_UUID_TX = NULL
//defines the output format of the mpu data
#define OUTPUT_READABLE_ACCELGYRO

//creates a few 16 bit sighned intergers for each axis
int16_t ax, ay, az;
int16_t gx, gy, gz;


class MyServerCallBacks: public BLEServerCallbacks {
  
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer){
    deviceConnected = false;
  }

};

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
  Serial.println("running checks.....");
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
  mpu.setXGyroOffset(0);  
  mpu.setYGyroOffset(0); 
  mpu.setZGyroOffset(0);  

  Serial.println("Device is now zeroed to current pos");
  Serial.println("Setting current values");




  //create bluetooth device
  BLEDevice::init("dope paddle");

  //create bluetooth server
  BLEServer *pServer = BLEServer::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  //actually create the signal
  BLEService *pService = pServer->createService(SERVICE_UUID);

  //create a bluetooth chararicteristic
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX,BLECharacteristic::PROPERTY_NOTIFY);

  //send bluetooth notification out
  pCharacteristic->addDescriptor(new BLE2902());

  pService->start();

  pServer->getAdvertising()->start();
  
  Serial.println("waiting for connection....");
}



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
    //convert txValue into bytes
    //char txString[8];
    //dtostrf(txValue, 1, 2, txString);

    //sets txValue to the charecteristic of the device (the data to send)
    pCharacteristic->setValue(txValue);//txString

    //actually send data
    pCharacteristic->notify();
    Serial.println("IT WORKED: " + String(txValue));
    
  }






}

