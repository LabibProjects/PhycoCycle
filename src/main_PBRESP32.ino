#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define PH_SENSOR A0
#define TURBIDITY_SENSOR A1
#define WATER_LEVEL_SENSOR 5
#define LED_PIN 2
#define PUMP_PIN 15

const char* ssid = "Labib";
const char* password = "Bangladesh9090";
WiFiServer server(80);

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);
    dht.begin();
    pinMode(WATER_LEVEL_SENSOR, INPUT);
    pinMode(PH_SENSOR, INPUT);
    pinMode(TURBIDITY_SENSOR, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);
    lcd.begin();
    lcd.backlight();
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    server.begin();
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int phValue = analogRead(PH_SENSOR);
    int turbidity = analogRead(TURBIDITY_SENSOR);
    int waterLevel = digitalRead(WATER_LEVEL_SENSOR);

    Serial.print("Temperature: "); Serial.print(temperature); Serial.println("C");
    Serial.print("Humidity: "); Serial.print(humidity); Serial.println("%");
    Serial.print("pH Value: "); Serial.println(phValue);
    Serial.print("Turbidity: "); Serial.println(turbidity);
    Serial.print("Water Level: "); Serial.println(waterLevel ? "OK" : "LOW");

    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("pH: ");
    lcd.print(phValue);
    lcd.print(" Turb: ");
    lcd.print(turbidity);

    if (phValue < 300 || turbidity > 700) {
        digitalWrite(PUMP_PIN, HIGH);
        Serial.println("Pump Activated");
    } else {
        digitalWrite(PUMP_PIN, LOW);
        Serial.println("Pump Deactivated");
    }

    if (temperature > 30) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED Turned On");
    } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED Turned Off");
    }

    WiFiClient client = server.available();
    if (client) {
        Serial.println("Client connected");
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.print("<html><body>");
        client.print("<h2>ESP32 Monitoring</h2>");
        client.print("Temperature: "); client.print(temperature); client.print("C<br>");
        client.print("Humidity: "); client.print(humidity); client.print("%<br>");
        client.print("pH: "); client.print(phValue); client.print("<br>");
        client.print("Turbidity: "); client.print(turbidity); client.print("<br>");
        client.print("Water Level: "); client.print(waterLevel ? "OK" : "LOW"); client.print("<br>");
        client.print("</body></html>");
        client.stop();
        Serial.println("Client disconnected");
    }
    delay(2000);
}
