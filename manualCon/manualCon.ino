//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <Smartcar.h>
#include <VL53L0X.h>
#include <FirebaseESP32.h>
#include <WiFi.h>             //wifi library


#define WIFI_SSID "##########################"             //replace SSID with your wifi username
#define WIFI_PASSWORD "#########################"

#define FIREBASE_HOST "###################################.firebaseio.com/"                         //link of api
#define FIREBASE_AUTH "###################################"           //database secret



const float maxSpeed = 5;
float fSpeed = 2.5;  // a ground speed (m/sec) for going forward
float bSpeed = -2.5; // a ground speed (m/sec)y for going backward
const float auto_fwd_speed = 1;
const float auto_avoidObs_speed = 0.75;
const int lDegrees = -75; // degrees to turn left
const int rDegrees = 75;  // degrees to turn right

FirebaseData firebasedata;
FirebaseData firebasedata1;
FirebaseData firebasedata2;
FirebaseData firebasedata3;
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
VL53L0X sensor;






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

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous();
  car.enableCruiseControl();

}


void loop() {
  car.update();
  handleInput();
}

void handleInput() {
  Serial.print(sensor.readRangeContinuousMillimeters());
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }

  Serial.println();

  int all_offVal = 0;
  // Serial.println(all_offVal);







  if ( Firebase.getString(firebasedata2, "/auto/mode")) {
    String autoVal = firebasedata2.stringData();



    float covered_dis = car.getDistance();
    Firebase.setFloat(firebasedata3, "/auto/covered_dis", covered_dis);


    if (autoVal == "on") {

      if (sensor.readRangeContinuousMillimeters() <= 500 && sensor.readRangeContinuousMillimeters() != 0) {

        car.setSpeed(auto_avoidObs_speed);
        car.setAngle(90);
        delay(1000);

      } else {
        car.setSpeed(auto_fwd_speed);
        car.setAngle(0);
      }
    } else if (autoVal == "off") {

      all_offVal = all_offVal + 1;


      if (Firebase.getFloat(firebasedata1, "/manual/speed")) {
        float speedVal = firebasedata1.floatData();
        fSpeed = speedVal;
        bSpeed = (-1) * speedVal;
      }

      if ( Firebase.getString(firebasedata, "/manual/forward")) {

        String fwdVal = firebasedata.stringData();

        if (fwdVal == "on") {

          car.setSpeed(fSpeed);
          car.setAngle(0);

        } else if (fwdVal == "off") {
          all_offVal = all_offVal + 1;
        }

      }
      if ( Firebase.getString(firebasedata, "/manual/backward") ) {
        String bwdVal = firebasedata.stringData();
        // Serial.println("bwd " + bwdVal + all_offVal);
        if (bwdVal == "on") {
          car.setSpeed(bSpeed);
          car.setAngle(0);

        } else if (bwdVal == "off") {
          all_offVal = all_offVal + 1;
        }
      }

      if (Firebase.getString(firebasedata, "/manual/right") ) {
        String rightVal = firebasedata.stringData();
        // Serial.println("right " + rightVal + all_offVal);
        if (rightVal == "on") {
          car.setSpeed(fSpeed);
          car.setAngle(rDegrees);
        } else if (rightVal == "off") {
          all_offVal = all_offVal + 1;
        }
      }

      if (Firebase.getString(firebasedata, "/manual/left")) {
        String leftVal = firebasedata.stringData();
        //Serial.println("left " + leftVal + all_offVal);
        if (leftVal == "on") {
          car.setSpeed(fSpeed);
          car.setAngle(lDegrees);
        }
        else if (leftVal == "off") {
          all_offVal = all_offVal + 1;
        }
      }
    }
  }

  Serial.println( all_offVal);
  if (all_offVal == 5) {
    car.setSpeed(0);
    car.setAngle(0);
  }
}
