/**The MIT License (MIT)

Copyright (c) 2016 by Daniel Eichhorn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

See more at http://blog.squix.ch
*/

/* Customizations by Neptune (NeptuneEng on Twitter, Neptune2 on Github)
 *  
 *  Added Wifi Splash screen and credit to Squix78
 *  Modified progress bar to a thicker and symmetrical shape
 *  Replaced TimeClient with built-in lwip sntp client (no need for external ntp client library)
 *  Added Daylight Saving Time Auto adjuster with DST rules using simpleDSTadjust library
 *  https://github.com/neptune2/simpleDSTadjust
 *  Added Setting examples for Boston, Zurich and Sydney
  *  Selectable NTP servers for each locale
  *  DST rules and timezone settings customizable for each locale
   *  See https://www.timeanddate.com/time/change/ for DST rules
  *  Added AM/PM or 24-hour option for each locale
 *  Changed to 7-segment Clock font from http://www.keshikan.net/fonts-e.html
 *  Added Forecast screen for days 4-6 (requires 1.1.3 or later version of esp8266_Weather_Station library)
 *  Added support for DHT22, DHT21 and DHT11 Indoor Temperature and Humidity Sensors
 *  Fixed bug preventing display.flipScreenVertically() from working
 *  Slight adjustment to overlay
 */
 
#include <simpleDSTadjust.h>
#include "DHT.h"


// Please read http://blog.squix.org/weatherstation-getting-code-adapting-it
// for setup instructions

#define HOSTNAME "IoT-device-"

// Setup interval for update
// *** warning ***
// I received this warning message from wunderground and 2 minutes interval exceeds the traffic limits. 
// I recommended to use > 2 minutes to avoid to lost your own account and system lock you out.
//
//
// Your wunderground API key (XXXXXXXX) exceeded its allotted usage today by making 503 calls
// in a day but the limit is 500. We used one of your raindrops instead of disabling the key for the 
// remainder of the day. You now have 3 remaining raindrops.
const int UPDATE_INTERVAL_SECS = 3*60; // Update every 3 minutes

// >>> Uncomment one of the following 2 lines to define which OLED display interface type you are using
//#define spiOLED
#define i2cOLED

#ifdef spiOLED
#include "SSD1306Spi.h"
#endif
#ifdef i2cOLED
#include "SSD1306Wire.h"
#endif
#include "OLEDDisplayUi.h"

#ifdef spiOLED
// Pin definitions for SPI OLED
#define OLED_CS     D8  // Chip select
#define OLED_DC     D2  // Data/Command
#define OLED_RESET  D0  // RESET  - If you get an error on this line, either change Tools->Board to the board you are using or change "D0" to the appropriate pin number for your board.
#endif

#ifdef i2cOLED
// Pin definitions for I2C OLED
// Initialize the OLED display using brzo_i2c
// D3 -> SDA (Data) -> GPIO 0
// D5 -> SCL (Clock) -> GPIO 14
const int I2C_DISPLAY_ADDRESS = 0x3C;
const int SDA_PIN = D3; 
const int SDC_PIN = D5;
#endif


#define DHTPIN D6 // Wemos D1R2 Mini
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
#if DHTTYPE == DHT22
  #define DHTTEXT "DHT22"
#elif DHTTYPE == DHT21
  #define DHTTEXT "DHT21"
#elif DHTTYPE == DHT11
  #define DHTTEXT "DHT11"
#endif
char FormattedTemperature[10];
char FormattedHumidity[10];

// -----------------------------------
// Example Locales (uncomment only 1)
#define Bangkok
//------------------------------------

#ifdef Bangkok
//DST rules for Indochina Time Zone
#define UTC_OFFSET +7
struct dstRule StartRule = {"ICT", Last, Sun, Jan, 1, 0}; // Indochina Time = UTC/GMT +7 hours
struct dstRule EndRule = {"ICT", Last, Sun, Jan, 1, 0};  // Indochina Time = UTC/GMT +7 hour

// Uncomment for 24 Hour style clock
#define STYLE_24HR

#define NTP_SERVERS "0.asia.pool.ntp.org", "1.asia.pool.ntp.org", "2.asia.pool.ntp.org"

// Wunderground Settings
const boolean IS_METRIC = true;
const String WUNDERGRROUND_API_KEY = "8be40cc9fbf7c8bf";
const String WUNDERGRROUND_LANGUAGE = "EN";
const String WUNDERGROUND_COUNTRY = "TH";
const String WUNDERGROUND_CITY = "Bangkok";
#endif

//Thingspeak Settings
// testing thingspeak reading out from API
// https://api.thingspeak.com/channels/409552/feeds.json?api_key=TLMQEP66VPYJNESE&results=2
// note if you intend to use this value, the device will retrieve my data.
const char* host = "api.thingspeak.com";
const String THINGSPEAK_OUTDOOR_CHANNEL_ID = "409552";
const String THINGSPEAK_API_OUTDOOR_READ_KEY = "TLMQEP66VPYJNESE";
const String THINGSPEAK_API_OUTDOOR_WRITE_KEY = "3RNS8P07KQZUOHHO";

const String THINGSPEAK_INDOOR_CHANNEL_ID = "411929";
const String THINGSPEAK_API_INDOOR_READ_KEY = "OOKJ9ZHGTQTPCE0R";
const String THINGSPEAK_API_INDOOR_WRITE_KEY = "W9AER3QHXSPQDKQP";

#ifdef spiOLED
  SSD1306Spi display(OLED_RESET, OLED_DC, OLED_CS);  // SPI OLED
#endif
#ifdef i2cOLED
  SSD1306Wire display(I2C_DISPLAY_ADDRESS, SDA_PIN, SDC_PIN); 
  // Brzo settings
  // #include "SSD1306Brzo.h"
  // SSD1306Brzo display(0x3c, D3, D5);
#endif


OLEDDisplayUi   ui( &display );

// Setup simpleDSTadjust Library rules
simpleDSTadjust dstAdjusted(StartRule, EndRule);

/***************************
 * End Settings
 **************************/
 
