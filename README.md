### Weather Station ###

![weather station gif](https://github.com/boonchu/ESPXX_weather_station/blob/master/Weather%20Station.gif)

* Features:
	- Current date and time with NTP sync
	- one week forcast local weather in your area
	- display the indoor temperature and humidity
	- display the outdoor temperature and humidity (part two with outdoor sensor)

* Note: find the original project idea from this link https://github.com/squix78/esp8266-weather-station

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
	- read schemeatic and put parts together with connecting wires
	- use USB cable to connect your PC
	- register yourself to retrieve the API key from https://www.wunderground.com/weather/api
	- checkout this code from github
	- run Arduino IDE
	- Open file 'WeatherStationDemoExtendedDST.ino'
	- change your WIFI ID and Password for first name that connect to internet
	- tab to settings.h file to adjust setting values (note: I use South East Asia region setting)
	- required setting changes: (local city name, localized langauge code, NTP servers, etc)
	- required setting for forcasting data: replace value in WUNDERGRROUND_API_KEY

* Schematic:

![alt text](https://github.com/boonchu/ESPXX_weather_station/blob/master/Weather%20Station%20Schematic.png)

DHT sensor  | ESP8266 12E
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
