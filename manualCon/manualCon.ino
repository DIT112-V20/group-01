//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <Smartcar.h>
#include "BluetoothSerial.h"
//THIS IS JUST A TEST DELETE LATER.



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
String message = "";
char incomingChar;



const int fSpeed   = 0.5;  // 70% of the full speed forward
const int bSpeed   = -0.5; // 70% of the full speed backward
const int lDegrees = -75; // degrees to turn left
const int rDegrees = 75;  // degrees to turn right


BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);
GY50 gyroscope(37);

const auto pulsesPerMeter = 600;

DirectionlessOdometer leftOdometer(
    smartcarlib::pins::v2::leftOdometerPin, []() { leftOdometer.update(); }, pulsesPerMeter);
DirectionlessOdometer rightOdometer(
    smartcarlib::pins::v2::rightOdometerPin, []() { rightOdometer.update(); }, pulsesPerMeter);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);


const int TRIGGER_PIN = 5; //D5
const int ECHO_PIN = 4; //D4
const unsigned int MAX_DISTANCE = 100;
SR04 front(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);



void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
 car.enableCruiseControl();


}


void loop() {
car.update();
  handleInput();
}

void handleInput(){
  if (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n') {
      message += char(incomingChar);
    }
    else {
      message = "";
    }
    Serial.write(incomingChar);
  }



  if (message == "forward") { // rotate counter-clockwise going forward
    car.setSpeed(fSpeed);

  }
  if (front.getDistance() != 0 && front.getDistance() <= 15) {
    car.setSpeed(0);
  }

  if (message == "left") { // rotate counter-clockwise going forward
    car.setSpeed(fSpeed);
    car.setAngle(lDegrees);
  }
  if (message == "right") { // turn clock-wise
    car.setSpeed(fSpeed);
    car.setAngle(rDegrees);
  }
    }
  if (message == "backwards") { // go back
    car.setSpeed(bSpeed);
    car.setAngle(0);
  }

  if(message=="incSpeed" ){
    car.setSpeed(car.getSpeed()+0.2);
  }

  if(message=="decSpeed" && car.getSpeed()>=0){
    car.setSpeed(car.getSpeed()-0.2);
  }

  else if (message == "stop" || (front.getDistance() != 0 && front.getDistance() <= 15)) {
    car.setSpeed(0);
    car.setAngle(0);
  }
  


  delay(20);
}
