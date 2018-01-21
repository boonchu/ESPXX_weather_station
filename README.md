### Weather Station ###

* Features:
	- one week forcast local weather in your area
	- display the actual temperature and humidy in your working area

* Note: find the original project idea from this link https://github.com/squix78/esp8266-weather-station

* Note: When you want to get basic understanding about SSD1306 OLED display device, this link will help https://github.com/squix78/esp8266-oled-ssd1306

I extract only actual example code from 'squix78/esp8266-weather-station' to run weather station testing.

* Parts:
	- ESP8266 12E
	- Arudino IDE software
	- DHT11 or DHT22 integrated temperature and humidity sensors
	- Graphical OLED SSD1306 128 by 64 pixels

* Preparing steps:
	- read schemeatic and put parts together with connecting wires
	- use USB cable to connect your PC
	- checkout this code from github
	- run Arduino IDE
	- Open file 'WeatherStationDemoExtendedDST.ino'
	- change your WIFI ID and Password for first name that connect to internet
	- tab to settings.h file to adjust setting values (note: I use South East Asia region setting)
	- required setting changes: (local city name, localized langauge code, NTP servers, etc)

* Schematic:

![alt text](https://github.com/boonchu/ESPXX_weather_station/blob/master/Weather%20Station%20Schematic.png)

DHT sensor  | ESP8266 12E
------------- | -------------
pin 1 | pin D6
vcc   | 3v3 pin
GND   | GND pin

SSD1306 OLED | ESP8266 12E
------------- | -------------
vcc | 3v3 pin
GND | GND
SCL | D5
SDA | D3
