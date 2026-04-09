#include <Arduino.h>
#include <ESP8266WiFi.h>

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    delay(100);
    Serial.println();
    Serial.println("=== ESP8285 MAC Address ===");
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.println("===========================");
}

void loop() {
    delay(5000);
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());
}
