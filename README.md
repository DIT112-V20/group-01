# Group-01 ![Arduino CI](https://github.com/DIT112-V20/group-01/workflows/Arduino%20CI/badge.svg) ![Java CI with Gradle](https://github.com/DIT112-V20/group-01/workflows/Java%20CI%20with%20Gradle/badge.svg)

[1. Project Overview](https://github.com/DIT112-V20/group-01#project-overview)
* [What is the idea of our project?](https://github.com/DIT112-V20/group-01#what-is-the-idea-of-our-project)
* [Why will we make it?](https://github.com/DIT112-V20/group-01#why-will-we-make-it)
* [How are we going to make it?](https://github.com/DIT112-V20/group-01#how-are-we-going-to-make-it)

[2. Features](https://github.com/DIT112-V20/group-01#features)
* [Obstacle Avoidance](https://github.com/DIT112-V20/group-01#obstacle-avoidance)
* [Manual Control](https://github.com/DIT112-V20/group-01#manual-control)
* [Autonomous Driving](https://github.com/DIT112-V20/group-01#autonomous-driving)
* [Display Covered Distance ](https://github.com/DIT112-V20/group-01#display-covered-distance)

[3. Resources](https://github.com/DIT112-V20/group-01#resources)
* [Software](https://github.com/DIT112-V20/group-01#software)
* [Hardware](https://github.com/DIT112-V20/group-01#hardware)

[4. Installation](https://github.com/DIT112-V20/group-01#installation)
* [Import the code](https://github.com/DIT112-V20/group-01#import-the-code)
* [Setup the car](https://github.com/DIT112-V20/group-01#setup-the-car)
* [Setup the app](https://github.com/DIT112-V20/group-01#setup-the-app)
* [Establish Connection](https://github.com/DIT112-V20/group-01#establish-connection)

[5. User Manual](https://github.com/DIT112-V20/group-01#user-manual)

[6. Product Demo](https://github.com/DIT112-V20/group-01#product-demo)

[7. Team](https://github.com/DIT112-V20/group-01#team)
# **Project Overview**
## What is the idea of our project?
Our main idea of the project is a car with capabilities of autonomously driving and detecting obstacles around.
Additionally the car can be manually controlled by users. The project also relates to development of an Android application that allows the users to control and interact with the car.

## Why will we make it?
Our aim with the project is to simulate a real world driving experience, and introduce users to some aspects of self-driving cars.

## How are we going to make it?
We're working on two platforms, an Arduino car and a mobile application.
For the Arduino car, we are going to create an Arduino sketch that holds the car's functions, and for the mobile application we are using Android Studio to create a simple UI.
The communication between the car and the application will be easily done through Google Firebase. Using a Real-time Database, if any changes occur to one of the platforms, the other will be notified of these changes using API's provided by the database. 

# Features
## Obstacle Avoidance
This insures the car does not hit any obstacles when it's in Autonomous Driving mode. Using the LIDAR sensor, the car will detect objects from a good distance, giving it enough time to decrease speed until it fully-stops to avoid hitting them.
## Manual Control
Using the mobile application, the user will be able to manually control the speed and the direction of the car.
In the manual control screen, there are four direction buttons (Forward, backward, right, left), when the user presses one of them the car starts moving in that direction and stops when the button is released. And there's a speed SeekBar that allows the user to increase/decease the speed of the car.
## Autonomous Driving
Using the mobile application, the user will have the choice to activate the Autonomous Driving mode.
When activating the autonomous driving mode, the car starts moving forward until it detects obstalces on its way, so it changes direction and keeps moving until the user deactivates the autonomous driving.
## Display Covered Distance 
In Autonomous Driving mode, once the car stops, the application will display to the users the distance driven by the car. 

# Resources
## Software 
**Arduino IDE:** used to implement the logic to the car's functions.

**Android Studio:** used to develop the application as an interface between the user and and the car.
## Hardware
* Android phone
* Smart car
* 1x Micro LiDAR sensor
* 2x Odometers
* Microcontroller

# Installation
## Import the code
Download the [package](https://github.com/DIT112-V20/group-01/archive/master.zip) from our Github page.
## Setup the car
* Download [Arduino IDE](https://www.arduino.cc/en/main/software)
* Install the following libraries: [SmartCar shield library](https://www.arduinolibraries.info/libraries/smartcar-shield), [Firebase library](https://www.arduinolibraries.info/libraries/firebase-esp32-client), [Distance sensor library](https://www.arduinolibraries.info/libraries/vl53-l0-x), [Wifi library](https://github.com/espressif/arduino-esp32/blob/master/libraries/WiFi/src/WiFi.h)
* Compile the [Arduino sketch](https://github.com/DIT112-V20/group-01/blob/master/manualCon/manualCon.ino) Using Arduino IDE, and replace the hashes in WIFI_SSID and WIFI_PASSWORD with your own credentials.

![key1](https://user-images.githubusercontent.com/43995000/83351009-c5346080-a340-11ea-8102-4a2b5a5a86ec.png)

## Setup the app
* Download [Android Studio IDE](https://developer.android.com/studio)
* Upload the application on your device using [Andriod Studio](https://developer.android.com/training/basics/firstapp/running-app)
## Establish Connection
* Follow this [guide](https://medium.com/coinmonks/arduino-to-android-real-time-communication-for-iot-with-firebase-60df579f962) to connect the car and the app to a Firebase database.
* Replce the hashes for FIREBASE_HOST and FIREBASE_AUTH in the [Arduino sketch](https://github.com/DIT112-V20/group-01/blob/master/manualCon/manualCon.ino) with your own credentials.

![key2](https://user-images.githubusercontent.com/43995000/83351041-02005780-a341-11ea-8631-0435a4d40dc0.png)




<img align="right"  src="https://user-images.githubusercontent.com/43995000/83341714-c9339480-a2e6-11ea-8bdc-9fa18e625489.gif">

# User Manual


1. Open the CarController application.

2. You're now in the home screen, You have two options to operate, manual and auto.

3. Tap on manual if you wish to control the car manually, you have now 4 buttons to control the direction of the car and a speed SeekBar to adjust the speed of the car.

4. Tap on auto and you're now in the autonomous driving screen, if you wish to start the autonomous driving mode press the "off" button to change the state from off to on and the car will start the run, click on the same button when you want the car to stop.

5. The distance driven by the car will now be displyed on the screen.

# Product Demo
Watch it here : [https://youtu.be/2E3qfQQXuCo](https://youtu.be/2E3qfQQXuCo)

# Team
* Karam Khatib guskarkh@student.gu.se
* Kareem Abdeldayem gusabdka@student.gu.se
* Luai Obaid gusalklu@student.gu.se
* Mohammad Nablo gusnabmo@student.gu.se
* Rodan Uca gusucaro@student.gu.se
