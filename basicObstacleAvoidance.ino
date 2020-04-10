#include <Smartcar.h>

        BrushedMotor leftMotor(smartcarlib::pins::v2::leftMotorPins);
        BrushedMotor rightMotor(smartcarlib::pins::v2::rightMotorPins);
        DifferentialControl control(leftMotor, rightMotor);
        SimpleCar car(control);

        const int TRIGGER_PIN = 6; //D6
        const int ECHO_PIN = 7; //D7
        const unsigned int MAX_DISTANCE = 100;
        SR04 front(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


        void setup() {

            Serial.begin(9600);
        }

        void loop() {
                
            int distance = front.getDistance();

            if(distance != 0 && distance <= 15) {
                car.setSpeed(0);
            } else {
                car.setSpeed(50);
                car.setAngle(0);
                }
            }
        }
