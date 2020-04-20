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



const int fSpeed   = 70;  // 70% of the full speed forward
const int bSpeed   = -70; // 70% of the full speed backward
const int lDegrees = -75; // degrees to turn left
const int rDegrees = 75;  // degrees to turn right

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);

const int TRIGGER_PIN = 5; //D5
const int ECHO_PIN = 4; //D4
const unsigned int MAX_DISTANCE = 100;
SR04 front(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

SimpleCar car(control);




void setup() {

  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(LED_BUILTIN, OUTPUT);


}


void loop() {



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


  delay(20);
}
