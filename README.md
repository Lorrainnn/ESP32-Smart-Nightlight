# 🌙 Smart Night Light with Weather Integration

## 📁 Suggested GitHub Repository Name

**`smart-nightlight-weather`**

> A concise and descriptive name following GitHub naming conventions.  
> Alternative names you could use:
> - `iot-nightlight`
> - `motion-weather-light`
> - `esp32-smart-light`
> - `nightlight-plus-weather`
> - `ambient-light-iot`

---

## 📖 Description

This project is an IoT-enabled night light system designed to enhance nighttime safety and energy efficiency, especially for individuals in shared living spaces or elderly family members. Instead of keeping lights always on or requiring manual switches, our system activates only when motion is detected under low-light conditions and also changes LED colors based on real-time weather data. Weather visualization is also available through a web interface powered by data stored in the cloud.

Built on the ESP32 platform, the system integrates a PIR motion sensor, a photoresistor, and a weather API to create an adaptive lighting experience that’s both practical and informative.

---

## 🛠️ Features

- ✅ Motion-activated lighting using a PIR sensor
- 🌡️ Real-time weather visualization via LED strip
- ☀️ Auto-disable in daylight using a photoresistor
- 📶 Weather data fetched via OpenWeather API over Wi-Fi
- 📊 Web-based visualization using AWS + JavaScript
- 🔒 Data logging with JSON format for historical weather

---

## 🧩 Hardware Used

| Component                             | Quantity |
|--------------------------------------|----------|
| LILYGO T-Display ESP32 Dev Board     | 1        |
| HC-SR501 PIR Motion Sensor           | 1        |
| WS2812B RGB LED Strip (3.3ft)        | 1        |
| Photoresistor                        | 1        |
| Breadboard + Jumper Wires + Resistor| Many     |
| USB-C Cable                          | 1        |

---

## 📽️ Demo Video

[Watch on YouTube](https://www.youtube.com/watch?v=oQc5v1kqj4Y)
![image](https://github.com/user-attachments/assets/b0873588-d642-4587-9bba-27f80f28e969)


---



## 🔮 Future Improvements

- Add a simple UI or mobile app for easier Wi-Fi configuration
- Simplify cloud setup and make data visualization more user-friendly

---


## Features
- Fetches real-time weather data using OpenWeatherMap API.
- Supports daily weather forecasts for specific locations.
- Adjusts LED colors based on weather conditions:
  - Thunderstorm: Electric indigo
  - Rain: Blue
  - Clear: Orange
  - Snow: White
  - Atmosphere: Red
  - Cloud: Lavender
  - Default: Rose
  
