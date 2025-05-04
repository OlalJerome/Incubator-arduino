#define BLYNK_TEMPLATE_ID "TMPL2hV6NYYnJ"
#define BLYNK_TEMPLATE_NAME "Incubator"
#define BLYNK_PRINT Serial
#include <WiFi.h> 
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

// Define pin numbers
#define DHT11PIN 4   // DHT11 Sensor Pin
#define RELAY_PIN 26   // Relay connected to GPIO 5
#define FAN_PIN 27    // Fan connected to GPIO 18 (Example)
#define BUZZER 25      // Buzzer for alerts

// Initialize DHT sensor
DHT11 dht(DHT11PIN); 

// Initialize the LCD (Change address if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Blynk Credentials
char auth[] = "UCtHxS5uELtKN7HkegxaMyc0V-KXFpZf4"; 
char ssid[] = "Xenophobia";        
char pass[] = "Peakgrass";    

BlynkTimer timer;

// Function to send data to Blynk
void sendSensorData() 
{
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\tHumidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    // Send data to Blynk Virtual Pins
    Blynk.virtualWrite(V0, temperature); // Send temperature to V0
    Blynk.virtualWrite(V1, humidity);    // Send humidity to V1

    // Control Relay Based on Temperature
    if (temperature > 36.5) {
        digitalWrite(RELAY_PIN, HIGH);  // Turn ON relay
        Serial.println("Relay ON (Cooling Activated)");
    } else {
        digitalWrite(RELAY_PIN, LOW);   // Turn OFF relay
        Serial.println("Relay OFF");
    }

    // Example: Control Fan and Heater
    if (temperature > 38.0) {
        digitalWrite(FAN_PIN, HIGH);    // Turn ON Fan
        digitalWrite(HEATER_PIN, LOW);  // Turn OFF Heater
    } else if (temperature < 36.0) {
        digitalWrite(FAN_PIN, LOW);     // Turn OFF Fan
        digitalWrite(HEATER_PIN, HIGH); // Turn ON Heater
    } else {
        digitalWrite(FAN_PIN, LOW); 
        digitalWrite(BUZZER, HIGH):
        delay(1000);
        digitalWrite(BUZZER, LOW):
        delay(1000);
    }
}

// Blynk function to control relay from the app
BLYNK_WRITE(V2) {  
    int relayState = param.asInt(); 
    digitalWrite(RELAY_PIN, relayState);
    Serial.print("Relay Controlled from App: ");
    Serial.println(relayState);
}

void setup() {
    Serial.begin(115200);
    
    // Initialize LCD
    lcd.begin();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Incubator Ready");
    delay(2000);
    // Update LCD Display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print(" %");  
  
    // Set Pin Modes
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Default OFF
    digitalWrite(FAN_PIN, LOW);
        // Connect to WiFi and Blynk
    Blynk.begin(auth, ssid, pass);

    // Setup a timer to send sensor data every 5 seconds
    timer.setInterval(5000L, sendSensorData);
}

void loop() {
    Blynk.run(); // Run Blynk
    timer.run(); // Run Timer
}
