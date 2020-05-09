//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal 

#include <Smartcar.h>

#include <FirebaseESP32.h>
#include <WiFi.h>             //wifi library
#define WIFI_SSID "OWNIT_24GHz_4E4C0D"             //replace SSID with your wifi username
#define WIFI_PASSWORD "4F75D9E491"          //replace PWD with your wifi password
//#define WIFI_LED D5                  //connect a led to any of the gpio pins of the board and replace pin_number with it eg. D4
FirebaseData firebasedata;
#define FIREBASE_HOST "https://testing2-ce90b.firebaseio.com/"                         //link of api
#define FIREBASE_AUTH "Z0Ea0vK4xmlByoYgI8mR1t2oCz1l7qqDCrvyKS0V"           //database secret



const float fSpeed = 0.5;  // a ground speed (m/sec) for going forward
const float bSpeed = -0.5; // a ground speed (m/sec)y for going backward
const int lDegrees = -75; // degrees to turn left
const int rDegrees = 75;  // degrees to turn right

BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
DifferentialControl control(leftMotor, rightMotor);
GY50 gyroscope(37);

const auto pulsesPerMeter = 600;

DirectionlessOdometer leftOdometer(
smartcarlib::pins::v2::leftOdometerPin, []() {
  leftOdometer.update();
}, pulsesPerMeter);
DirectionlessOdometer rightOdometer(
smartcarlib::pins::v2::rightOdometerPin, []() {
  rightOdometer.update();
}, pulsesPerMeter);

SmartCar car(control, gyroscope, leftOdometer, rightOdometer);

const int TRIGGER_PIN = 5; //D5
const int ECHO_PIN = 4; //D4
const unsigned int MAX_DISTANCE = 100;
SR04 front(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);






void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);                        //define pinmodes
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  //connect to wifi
  while (WiFi.status() != WL_CONNECTED) {           //wait till connected to WiFi
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);                    //Blink the light till connected to WiFi
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); //connect to Database

  delay(1000);
  car.enableCruiseControl();


}


void loop() {
  car.update();
  handleInput();
}

void handleInput() {
  if (Firebase.getString(firebasedata, "/manual/forward")) {

    String val = firebasedata.stringData();
    Serial.println(val);
    if (val == "on") {
      car.setSpeed(fSpeed);
      car.setAngle(0);
    } else if (val == "off") {
      car.setSpeed(0);
    }  

  }

    if (Firebase.getString(firebasedata, "/manual/backward")) {

    String val = firebasedata.stringData();
    Serial.println(val);
    if (val == "on") {
      car.setSpeed(fSpeed);
      car.setAngle(0);
    } else if (val == "off") {
      car.setSpeed(0);
    }  

  }

    if (Firebase.getString(firebasedata, "/manual/left")) {

    String val = firebasedata.stringData();
    Serial.println(val);
    if (val == "on") {
      car.setSpeed(fSpeed);
      car.setAngle(0);
    } else if (val == "off") {
      car.setSpeed(0);
    }  

  }

    if (Firebase.getString(firebasedata, "/manual/right")) {

    String val = firebasedata.stringData();
    Serial.println(val);
    if (val == "on") {
      car.setSpeed(fSpeed);
      car.setAngle(0);
    } else if (val == "off") {
      car.setSpeed(0);
    }  

  }
