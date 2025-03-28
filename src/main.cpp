#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>
#include "config.h"
#include "/Users/rzbyy/cs147/final non-s3/test.cpp"


#define PEOPLEPIN 36
#define LIGHTPIN 38
#define LIGHT_ON_DURATION 1000
//180000

Adafruit_NeoPixel rgb_display = Adafruit_NeoPixel(60, 21, NEO_GRB + NEO_KHZ800);

//Error color: amazon
int weatherAPIError[3] = {59, 122, 87};

//default color: african violet
int weatherAPINotFound[3] = {178, 132, 190};

// Global variables for light and motion sensors
int light = 0;
int people = 0;
int onLight = 0;   // Light on state
int lighting = 0;  // Currently lighting
float startTime = 0.0;  // Start time of lighting



// Function to set the light color
void setLightColor(int R, int G, int B) {
    for (int i = 0; i < 60; i++) {
        rgb_display.setPixelColor(i, rgb_display.Color(R, G, B));
    }
    rgb_display.show();
}


void taskOne(void *parameter) {
    while (1) {
        light = analogRead(LIGHTPIN);
        people = digitalRead(PEOPLEPIN);

        Serial.print("Light level: ");
        Serial.println(light);
        Serial.print("PIR state: ");
        Serial.println(people ? "Motion Detected" : "No Motion");

        if (light <= 2000 && people == HIGH && lighting == 0) {
            onLight = 1;  // Trigger light on
            startTime = millis();
        }
        vTaskDelay(500);
    }
    vTaskDelete(NULL);
}


void startLight() {
    HTTPClient http;
    int httpCode = -1;
    StaticJsonDocument<2048> doc; 
    String payload;

  
    String apiUrl = "https://api.openweathermap.org/data/2.5/weather?";
    apiUrl += "lat=" + String(LAT) + "&lon=" + String(LON);
    apiUrl += "&exclude=current,minutely,hourly,alerts";
    apiUrl += "&appid=" + String(API_KEY);

    Serial.println("Requesting URL: " + apiUrl); 

    http.begin(apiUrl); 
    httpCode = http.GET();

    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            payload = http.getString();
            deserializeJson(doc, payload);

            // Get tomorrow's weather ID from the daily forecast
            sendWeatherData(doc);

            int weatherId = doc["weather"][0]["id"]; // get weather code
            rgb_display.clear();

            // Determine the LED color based on weather ID groups
            if (weatherId >= 200 && weatherId < 300) {
                // Thunderstorm (2xx)
                setLightColor(115, 0, 230); // Electric indigo
                Serial.println("Thunderstorm detected! Color: Electric indigo");
            } else if (weatherId >= 300 && weatherId < 400) {
                // Drizzle (3xx)
                setLightColor(0, 255, 255); // Cyan
                Serial.println("Drizzle detected! Color: Cyan");
            } else if (weatherId >= 500 && weatherId < 600) {
                // Rain (5xx)
                setLightColor(0, 0, 255); // Blue
                Serial.println("Rain detected! Color: Blue");
            } else if (weatherId >= 600 && weatherId < 700) {
                // Snow (6xx)
                setLightColor(255, 255, 255); // White
                Serial.println("Snow detected! Color: White");
            } else if (weatherId >= 700 && weatherId < 800) {
                // Atmosphere (7xx)
                setLightColor(255, 0, 0); // Red
                Serial.println("Atmospheric conditions detected! Color: Red");
            } else if (weatherId == 800) {
                // Clear sky (800)
                setLightColor(255, 170, 0); // Orange
                Serial.println("Clear sky detected! Color: Orange");
            } else if (weatherId >= 801 && weatherId < 900) {
                // Clouds (801-804)
                setLightColor(255, 153, 255); // Lavender
                Serial.println("Cloudy conditions detected! Color: Lavender");
            } else {
                // Unknown or unhandled weather codes
                setLightColor(weatherAPIError[0],weatherAPIError[1],weatherAPIError[2]); 
                Serial.println("Unknown weather code! Color: ?");
                Serial.print(weatherId);
            }
        } else {
            // Handle HTTP response errors
            setLightColor(weatherAPIError[0],weatherAPIError[1],weatherAPIError[2]); 
            Serial.println("HTTP error occurred while fetching weather data.");
        }
    } else {
        // Handle network or API errors
        setLightColor(weatherAPIError[0],weatherAPIError[1],weatherAPIError[2]); 
        Serial.println("Network or API error occurred while fetching weather data.");
    }

    // Gradually increase brightness
    for (int i = 1; i <= 14; i++) {
        rgb_display.setBrightness(i * 5);
        rgb_display.show();
        delay(200);
    }
}



// Prepare light before fetching weather data
void startLightPrepare() {
    setLightColor(weatherAPINotFound[0], weatherAPINotFound[1], weatherAPINotFound[2]);
    rgb_display.setBrightness(10);
    rgb_display.show();
}



void setup() {
    Serial.begin(115200);

    // WiFi setup
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }


    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Lightstrip setup
    rgb_display.begin();
    rgb_display.show();

    pinMode(LIGHTPIN, INPUT);
    pinMode(PEOPLEPIN, INPUT);

    // Task setup
    xTaskCreatePinnedToCore(
        taskOne, "taskOne", 15000, NULL, 1, NULL, 1);
}



void loop() {
    if (lighting == 1) {
        float tempTime = millis();

        // If it's bright, turn off the light
        if (light == 0) {
            rgb_display.clear();
            rgb_display.show();
            lighting = 0;
            onLight = 0;
        }

        // Turn off after setting minutes
        if (tempTime - startTime > LIGHT_ON_DURATION) {
            rgb_display.clear();
            rgb_display.show();
            lighting = 0;
            onLight = 0;
        }
    } else {
        if (onLight == 1) {
            lighting = 1;
            onLight = 0;
            startLightPrepare();
            startLight();
        }
    }

    delay(500);
}