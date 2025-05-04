# Incubator-arduino
## 🐣 Smart Egg Incubator using ESP32 + Blynk
This is an **IoT-enabled Smart Egg Incubator** system built with an ESP32 microcontroller, a DHT11 temperature and humidity sensor, a relay-controlled heating element, fan, buzzer, LCD display, and Blynk for real-time monitoring and control.
### 🔧 Features

* Real-time monitoring of temperature and humidity via **Blynk mobile app**
* Automatic control of heating element and fan based on temperature thresholds
* Visual alerts using **LCD display**
* Buzzer alert system for abnormal conditions
* Manual relay control from Blynk App
### Components Used

* ESP32 Development Board
* DHT11 Temperature & Humidity Sensor
* Relay Module (for heating element)
* Fan
* Buzzer
* I2C 16x2 LCD Display
* Blynk IoT Mobile App

### 🔌 Pin Configuration

| Component    | ESP32 Pin          |
| ------------ | ------------------ |
| DHT11 Sensor | GPIO 4             |
| Relay        | GPIO 26            |
| Fan          | GPIO 27            |
| Buzzer       | GPIO 25            |
| LCD (I2C)    | 0x27 (I2C Address) |

### 📱 Blynk Setup

* **Template ID**: `TMPL2hV6NYYnJ`
* **Template Name**: `Incubator`
* **Auth Token**: Replace `"UCtHxS5uELtKN7HkegxaMyc0V-KXFpZf4"` with your actual Blynk token
* Virtual Pins:

  * `V0`: Temperature
  * `V1`: Humidity
  * `V2`: Manual relay control

### 🛠 How It Works

* Every 5 seconds, the ESP32 reads temperature and humidity values from the DHT11 sensor.
* The data is displayed on the LCD and sent to the Blynk app.
* If the temperature:

  * Exceeds 38°C → Fan turns ON, heater OFF.
  * Falls below 36°C → Fan turns OFF, heater ON.
  * Is between 36–38°C → Alert buzzer beeps intermittently.
* The relay can also be controlled manually via Blynk (V2).



