#ifndef CLOCK_GFX
#define CLOCK_GFX

#include <WiFiUDP.h>
#include <NTPClient.h>

#include <Timezone.h> // https://github.com/JChristensen/Timezone
#include <Adafruit_GFX.h>
#include "TomThumb.h"

#define HORIZONTAL 0
#define VERTICAL 1

// US Eastern Time Zone (New York, Detroit)
const TimeChangeRule EDT = {"EDT", Second, Sun, Mar,   2, -240}; // Daylight time = UTC - 4 hours
const TimeChangeRule EST = {"EST", First, Sun,  Nov,   2, -300}; // Standard time = UTC - 5 hours
// US Central Time Zone (Chicago, Dallas)
const TimeChangeRule CDT = {"CDT", Second, Sun, Mar,   2, -300}; // Daylight time = UTC - 4 hours
const TimeChangeRule CST = {"CST", First, Sun,  Nov,   2, -360}; // Standard time = UTC - 5 hours
// US Mountain Time Zone (Denver, Boise)
const TimeChangeRule MDT = {"MDT", Second, Sun, Mar,   2, -360}; // Daylight time = UTC - 4 hours
const TimeChangeRule MST = {"MST", First, Sun,  Nov,   2, -420}; // Standard time = UTC - 5 hours
// US Pacific Time Zone (Las Vegas, Seattle)
const TimeChangeRule PDT = {"PDT", Second, Sun, Mar,   2, -420}; // Daylight time = UTC - 4 hours
const TimeChangeRule PST = {"PST", First, Sun,  Nov,   2, -480}; // Standard time = UTC - 5 hours
// US Arizone Time Zone 
const TimeChangeRule ADT = {"ADT", Second, Sun, Mar,   2, -420}; // Daylight time = UTC - 4 hours
const TimeChangeRule AST = {"MST", First, Sun,  Nov,   2, -420}; // Standard time = UTC - 5 hours
// US Alaska Time Zone 
const TimeChangeRule AKDT = {"AKDT", Second, Sun, Mar,   2, -480}; // Daylight time = UTC - 4 hours
const TimeChangeRule AKST = {"AKST", First, Sun,  Nov,   2, -540}; // Standard time = UTC - 5 hours
//US Hawaii Time Zone
const TimeChangeRule HDT = {"HDT", Second, Sun, Mar,   2, -540}; // Daylight time = UTC - 4 hours
const TimeChangeRule HST = {"HST", First, Sun,  Nov,   2, -600}; // Standard time = UTC - 5 hours

class TimeGFX {

  private:

    NTPClient *ntpClient;
    WiFiUDP udp;

    Timezone tz = Timezone(EDT, EST);

    TimeChangeRule *tcr; // pointer to the time change rule, use to get TZ abbrev

    GFXcanvas16* _canvas;
    uint8_t _layout = HORIZONTAL; //Orientation for time layout 0 is one line, 1 is hour over minutes
    uint16_t _canvasWidth, _canvasHeight;
    uint8_t _textWidth;
    uint16_t _color = 0x4040;
    uint32_t _nextCanvasDraw = 0;

    void buildCanvas();

  public:
    TimeGFX();
    TimeGFX(uint16_t textColor, bool layout);
    
    void setColor(uint16_t c);
    void setTimezoneRules(TimeChangeRule std, TimeChangeRule day);
    time_t getTime();
    void setLayout(bool l);
    uint16_t * getCanvas();

    void setTextColor(uint16_t c) {
      _color = c;
    }

    void updateTime() {
      Serial.printf("Forcing time update %d\n",ntpClient->forceUpdate());
    }

    uint8_t getLayout() {
      return _layout;
    }

    uint16_t canvasWidth() const {
      return _canvasWidth;
    }
    uint16_t canvasHeight() const {
      return _canvasHeight;
    }

};

#endif