# Pertrifilm-Incubator Coding Project

This Arduino-based project is coded using C++ to build a portable Petrifilm incubator (a system to inspect e.coli water contamination) for water sample testing in underprivileged areas. It is designed for temperature control in an incubator. It uses various hardware components and libraries to maintain a stable temperature environment for specific applications. This pertrifilm incubator is currently being applied to use by onsite researchers. Below, you will find information on the hardware required, connections, warnings, and the libraries needed for this project.

## Hardware

You will need the following hardware components for this project:

1. 1 x DS18B20 Temperature Sensor
2. 1 x 12V Heater
3. 1 x MOSFET Module (MOS)
4. 1 x Buzzer
5. 1 x Arduino Mega 2560
6. 1 x 0.92 inch OLED Display
7. 1 x SD Card Module
8. Battery (Power Supply)

## Connections

Follow these steps to connect the hardware components to the Arduino Mega 2560:

1. Connect all 5V pins of the components to the Arduino's 5V pin.
2. Connect all GND (Ground) pins of the components to the Arduino's GND.
3. Connect the MOSFET module's IN pin to Arduino's D4.
4. Connect the buzzer to Arduino's D3.
5. Connect the middle pin of the DS18B20 temperature sensor to Arduino's D5.
6. Connect the OLED display's SCL pin to Arduino's SCL.
7. Connect the OLED display's SDA pin to Arduino's SDA.
8. Connect the SD card module's MISO pin to Arduino's 50.
9. Connect the SD card module's MOSI pin to Arduino's 51.
10. Connect the SD card module's SCK pin to Arduino's 52.
11. Connect the SD card module's CS pin to Arduino's 53.

## Warnings

Please take note of the following warnings:

1. Do not set the timer to be lower than or equal to 500ms.
2. Do not touch the heating pad while it is working.
3. Do not let the sensor touch the heater directly.

## Required Libraries

Make sure to install the following libraries in your Arduino IDE before uploading the code:

1. `Adafruit_SSD1306`: Library for OLED display.
2. `DallasTemperature`: Library for DS18B20 temperature sensor.
3. `MsTimer2`: Library for managing timers.

## Arduino Code

You can find the Arduino code for this project in the provided code file. Simply upload this code to your Arduino Mega 2560 to start using the incubator temperature control system.

## Usage

This incubator temperature control system continuously monitors the temperature using the DS18B20 sensor and displays it on the OLED display. It also controls the heater and buzzer based on predefined temperature thresholds. Temperature data is saved to an SD card for later analysis.

Feel free to modify the code and customize the temperature control settings to suit your specific incubation needs.

Enjoy your Arduino-based incubator temperature control project!
<img width="672" alt="Screen Shot 2023-09-04 at 11 41 46 AM" src="https://github.com/norahty/pertrifilm-incubator/assets/94091909/cf70ab83-a3a0-4955-8b07-dd16c02be123">

Here's a simple demo of how the system works:

temperature control demo:



https://github.com/norahty/pertrifilm-incubator/assets/94091909/2bb5951b-de06-4672-81f7-e4776b39d3b2



the entire incubator:



https://github.com/norahty/pertrifilm-incubator/assets/94091909/0f1d060a-ad9f-48bf-81df-5f7a59860c57


