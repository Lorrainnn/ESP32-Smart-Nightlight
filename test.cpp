#include <ArduinoJson.h>
#include <WiFi.h>
#include <HTTPClient.h>


// AWS server info
const char kHostname[] = "18.220.203.2";
const int kPort = 5000;
const char kPath[] = "/";

// Helper function to format time from UNIX timestamp
String formatTime(int unixTime) {
  time_t rawtime = unixTime;
  struct tm *timeinfo = localtime(&rawtime);
  char buffer[10];
  strftime(buffer, sizeof(buffer), "%I:%M %p", timeinfo);  // Format as HH:MM AM/PM
  return String(buffer);
}
void sendWeatherData(const JsonDocument& doc) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Construct server URL
    String serverUrl = String("http://") + kHostname + ":" + kPort + kPath;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Extract and prepare data
    StaticJsonDocument<512> dataToSend;
    dataToSend["location"]["name"] = doc["name"];
    dataToSend["location"]["coordinates"]["lon"] = doc["coord"]["lon"];
    dataToSend["location"]["coordinates"]["lat"] = doc["coord"]["lat"];

    dataToSend["weather"]["main"] = doc["weather"][0]["main"];
    dataToSend["weather"]["description"] = doc["weather"][0]["description"];

    dataToSend["temperature"]["current"] = doc["main"]["temp"];
    dataToSend["temperature"]["feels_like"] = doc["main"]["feels_like"];
    dataToSend["temperature"]["humidity"] = doc["main"]["humidity"];
    dataToSend["temperature"]["pressure"] = doc["main"]["pressure"];

    dataToSend["clouds"] = doc["clouds"]["all"];

    dataToSend["wind"]["speed"] = doc["wind"]["speed"];
    dataToSend["wind"]["direction"] = doc["wind"]["deg"];

    dataToSend["sun"]["sunrise"] = doc["sys"]["sunrise"];
    dataToSend["sun"]["sunset"] = doc["sys"]["sunset"];

    // Create a readable reminder string
    String reminder = "Weather in ";
    reminder += doc["name"].as<String>() + ": ";
    reminder += doc["weather"][0]["description"].as<String>() + ". ";
    reminder += "Temperature is " + String(doc["main"]["temp"].as<float>() - 273.15, 1) + "°C";
    reminder += ", feels like " + String(doc["main"]["feels_like"].as<float>() - 273.15, 1) + "°C. ";
    reminder += "Humidity is " + String(doc["main"]["humidity"].as<int>()) + "%, ";
    reminder += "with a wind speed of " + String(doc["wind"]["speed"].as<float>()) + " m/s. ";
    reminder += "Sunrise at " + formatTime(doc["sys"]["sunrise"].as<int>()) + ", ";
    reminder += "and sunset at " + formatTime(doc["sys"]["sunset"].as<int>()) + ".";

    // Add the reminder to the payload
    dataToSend["reminder"] = reminder;

    // Serialize JSON to string
    String payload;
    serializeJson(dataToSend, payload);

    // Send HTTP POST request
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully!");
      Serial.println("Response: " + http.getString());
    } else {
      Serial.print("Error sending data. HTTP response code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}


