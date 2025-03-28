#include <Arduino.h>
#include <lvgl.h>
#include <esp32_smartdisplay.h>
#include "ui.h" // Include the header generated by SquareLine Studio

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>  // Add this line - you may need to install ArduinoJson library

#define SDA_PIN 21
#define SCL_PIN 22
#define RST_PIN 23
#define IRQ_PIN 19

const char* ssid = "huawei";
const char* password = "s12345678";
const char* esp8266IP = "http://192.168.8.198/win"; // ESP8266 IP address
const char* openWeatherMapAPI = "http://api.openweathermap.org/data/2.5/weather?q=Al%20Qatif,sa&units=metric&APPID=c51346e22d798a475b744ae5a939d0f6";

auto lv_last_tick = millis();

// Function to get the switch state
bool getSwitchState() {
    return lv_obj_has_state(ui_Switch1, LV_STATE_CHECKED);
}

// Function to send HTTP request
void toggleLED() {
    HTTPClient http;

    // Get switch state
    bool switchState = getSwitchState();
    
    // Create the full URL (T=1 for ON, T=0 for OFF)
    String url = String(esp8266IP) + "&T=" + (switchState ? "1" : "0");
    
    http.begin(url);
    int httpCode = http.GET();

    if (httpCode > 0) {
        Serial.println("LED toggled");
    } else {
        Serial.println("Error toggling LED");
    }

    http.end();
}

// Event callback when the switch state changes
void switch_event_cb(lv_event_t * e) {
    Serial.println("Switch state changed!");
    toggleLED();
}

// Add this function to fetch temperature
void updateTemperature() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(openWeatherMapAPI);
        
        int httpCode = http.GET();
        if (httpCode > 0) {
            String payload = http.getString();
            
            DynamicJsonDocument doc(1024);
            DeserializationError error = deserializeJson(doc, payload);
            
            if (!error) {
                float temp = doc["main"]["temp"].as<float>();
                String displayTemp = String(temp, 1) + "°C";  // Show one decimal place
                lv_label_set_text(ui_Label3, displayTemp.c_str());
                Serial.println("Temperature updated: " + displayTemp);
            } else {
                Serial.println("JSON parsing failed");
                Serial.println("Error: " + String(error.c_str()));
                Serial.println("Received payload: " + payload);
            }
        } else {
            Serial.println("HTTP GET failed with code: " + String(httpCode));
        }
        http.end();
    }
}

void setup() {
    Serial.begin(115200);
    smartdisplay_init();
    ui_init();

    // Connect to WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!");


    // Set the IP address text in Label2
    lv_label_set_text(ui_Label2, esp8266IP);

    // Attach event callback to switch
    lv_obj_add_event_cb(ui_Switch1, switch_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    
   


    // Initial temperature update with delay to ensure stable connection
    delay(1000);
    updateTemperature();
}

void loop() {
    static unsigned long lastUpdate = 0;
    auto const now = millis();
    
    // Update LVGL
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    lv_timer_handler();

    // Update temperature every 10 minutes instead of 5
    if (now - lastUpdate >= 600000) {  // 10 minutes = 600000 milliseconds
        updateTemperature();
        lastUpdate = now;
    }
}
