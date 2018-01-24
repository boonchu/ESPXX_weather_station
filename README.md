### Weather Station (SSD1306 OLED display) ###

![weather station gif](https://github.com/boonchu/ESPXX_weather_station/blob/master/Weather%20Station.gif)

* Features:
	- Current date and time with NTP sync
	- one week forcast local weather in your area
	- display the indoor temperature and humidity
	- display the outdoor temperature and humidity (part two with outdoor sensor)

* Note: find the original project idea from this link
	- https://github.com/squix78/esp8266-weather-station
	- https://blog.squix.org/2015/12/esp8266-weather-station-measuring-2.html

* Note: When you want to get basic understanding about SSD1306 OLED display device, this link will help https://github.com/squix78/esp8266-oled-ssd1306

I extract only actual example code from 'squix78/esp8266-weather-station' to run weather station testing.

* Parts:
	- ESP8266 12E
	- DHT11 or DHT22 integrated temperature and humidity sensors
	- Graphical OLED SSD1306 128 by 64 pixels

* Softwares:
	- Arudino IDE software
	- Fritzing software

* Preparing steps:
	- reads schemeatic and put parts together with connecting wires
	- uses USB cable to connect your PC
	- registers yourself to retrieve the API key from https://www.wunderground.com/weather/api
	- use git checkout the code from github
	- run Arduino IDE
	- Open file 'WeatherStationDemoExtendedDST.ino'
	- change your WIFI ID and Password for first time that connect to internet 
	- tab to settings.h file to adjust setting values (note: I use South East Asia region setting)
	- require settings for forcasting data: replace value in WUNDERGRROUND_API_KEY
	- require settings change: (local city name, localized langauge code, NTP servers, etc)
	- loads code from arduino IDE to ESP unit
```
139   // Manual Wifi
140   // WiFi.begin(SSID, PASSWORD);
```
```
119 // use thingspeak to register your key
120 const String WUNDERGRROUND_API_KEY = "register your key here";
121 // update your location⋅
122 const String WUNDERGRROUND_LANGUAGE = "EN";
123 const String WUNDERGROUND_COUNTRY = "TH";
124 const String WUNDERGROUND_CITY = "Bangkok";
```

* Schematic:

![alt text](https://github.com/boonchu/ESPXX_weather_station/blob/master/Weather%20Station%20Schematic.png)

##### !attention! #####
```
Consult pin layouts from manufacturers. Table below is *ONLY* sample pin that use for my unit.
I have not responsible for any mistake.
```

DHT11 sensor  | ESP8266 12E
------------- | -------------
pin 1 data | pin D6 - GPIO
pin 2 vcc  | pin 3v3
pin 3 GND  | pin GND

SSD1306 OLED | ESP8266 12E
------------- | -------------
vcc | 3v3 pin
GND | GND
SCL | D5
SDA | D3
