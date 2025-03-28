//https://openweathermap.org/weather-conditions

const weatherCodes = {
    // Group 2xx: Thunderstorm
    200: ["Thunderstorm with light rain", "11d"],
    201: ["Thunderstorm with rain", "11d"],
    202: ["Thunderstorm with heavy rain", "11d"],
    210: ["Light thunderstorm", "11d"],
    211: ["Thunderstorm", "11d"],
    212: ["Heavy thunderstorm", "11d"],
    221: ["Ragged thunderstorm", "11d"],
    230: ["Thunderstorm with light drizzle", "11d"],
    231: ["Thunderstorm with drizzle", "11d"],
    232: ["Thunderstorm with heavy drizzle", "11d"],
  
    // Group 3xx: Drizzle
    300: ["Light intensity drizzle", "09d"],
    301: ["Drizzle", "09d"],
    302: ["Heavy intensity drizzle", "09d"],
    310: ["Light intensity drizzle rain", "09d"],
    311: ["Drizzle rain", "09d"],
    312: ["Heavy intensity drizzle rain", "09d"],
    313: ["Shower rain and drizzle", "09d"],
    314: ["Heavy shower rain and drizzle", "09d"],
    321: ["Shower drizzle", "09d"],
  
    // Group 5xx: Rain
    500: ["Light rain", "10d"],
    501: ["Moderate rain", "10d"],
    502: ["Heavy intensity rain", "10d"],
    503: ["Very heavy rain", "10d"],
    504: ["Extreme rain", "10d"],
    511: ["Freezing rain", "13d"],
    520: ["Light intensity shower rain", "09d"],
    521: ["Shower rain", "09d"],
    522: ["Heavy intensity shower rain", "09d"],
    531: ["Ragged shower rain", "09d"],
  
    // Group 6xx: Snow
    600: ["Light snow", "13d"],
    601: ["Snow", "13d"],
    602: ["Heavy snow", "13d"],
    611: ["Sleet", "13d"],
    612: ["Light shower sleet", "13d"],
    613: ["Shower sleet", "13d"],
    615: ["Light rain and snow", "13d"],
    616: ["Rain and snow", "13d"],
    620: ["Light shower snow", "13d"],
    621: ["Shower snow", "13d"],
    622: ["Heavy shower snow", "13d"],
  
    // Group 7xx: Atmosphere
    701: ["Mist", "50d"],
    711: ["Smoke", "50d"],
    721: ["Haze", "50d"],
    731: ["Sand/dust whirls", "50d"],
    741: ["Fog", "50d"],
    751: ["Sand", "50d"],
    761: ["Dust", "50d"],
    762: ["Volcanic ash", "50d"],
    771: ["Squalls", "50d"],
    781: ["Tornado", "50d"],
  
    // Group 800: Clear
    800: ["Clear sky", "01d"],
  
    // Group 80x: Clouds
    801: ["Few clouds: 11-25%", "02d"],
    802: ["Scattered clouds: 25-50%", "03d"],
    803: ["Broken clouds: 51-84%", "04d"],
    804: ["Overcast clouds: 85-100%", "04d"]
  };