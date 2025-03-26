# ESP32-Based Algae Wastewater Treatment Monitoring System

## Overview
This repository contains an ESP32-based monitoring system for an algae-based wastewater treatment system. It employs multiple sensors to monitor pH, turbidity, temperature, humidity, and water level while automating LED lighting and a water pump to optimize algae growth and pollutant removal.

## Features
- **Real-time Monitoring**: Tracks temperature, humidity, pH, turbidity, and water level.
- **Automatic Pump Control**: Activates the water pump based on pH and turbidity levels.
- **Adaptive LED System**: Adjusts lighting for algae photosynthesis.
- **WiFi Connectivity**: Enables remote monitoring via a web dashboard.
- **LCD Display**: Provides real-time local visualization of data.

## Components Used
- **ESP32** - Main microcontroller for data processing and connectivity.
- **DHT11 Sensor** - Measures temperature and humidity.
- **pH Sensor** - Monitors water acidity levels.
- **Turbidity Sensor** - Measures water clarity.
- **Water Level Sensor** - Detects the presence of water.
- **Relay Module** - Controls the water pump.
- **LED Lights** - Provides necessary light for algae photosynthesis.
- **LiquidCrystal_I2C Display** - Displays real-time readings locally.

## Setup Instructions
### Clone the Repository
```bash
git clone https://github.com/LabibProjects/ESP32-PhycoCycle.git
cd ESP32-PhycoCycle
```

### Install Required Libraries in Arduino IDE:
- `WiFi`
- `Adafruit_Sensor`
- `DHT`
- `LiquidCrystal_I2C`

### Hardware Setup
- Connect the devices according to the circuit diagram.
- Update `ssid` and `password` in the code with your WiFi credentials.
- Upload the code to ESP32 and open the Serial Monitor to view logs.
- Open the web dashboard by entering the ESP32’s IP address in a browser.

## Usage
- The system continuously monitors water parameters and activates the pump as needed.
- Data is displayed both on the LCD and the web dashboard.
- The LED system adjusts based on temperature conditions.

## Repository Structure
```
ESP32-PhycoCycle/
│── src/                
│   └── main_PBRESP32.ino 
│── README.md         
│── PBR_Flowchart.svg   
```

## Future Improvements
- **Cloud-Based Logging**: Integrate Firebase or Thingspeak for remote data logging.
- **CO₂ Injection**: Enhance algae growth by incorporating CO₂ control.
- **Mobile App**: Develop an app for real-time monitoring and control.



