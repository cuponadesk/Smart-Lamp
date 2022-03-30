#include "ClockGFX.h"

TimeGFX::TimeGFX() {
   _color = 0x4040;
  setLayout(HORIZONTAL);
  ntpClient = new NTPClient(udp, "pool.ntp.org");
  ntpClient->begin();
  // // Force an update before setting the internal clock
  // Serial.printf("Forcing time update %d\n",ntpClient->forceUpdate());
  // setTime(ntpClient->getEpochTime());
}

TimeGFX::TimeGFX(uint16_t textColor, bool layout = HORIZONTAL) {
  _color = textColor;
  setLayout(layout);
  ntpClient = new NTPClient(udp, "pool.ntp.org");
  ntpClient->begin();
  // Force an update before setting the internal clock
  Serial.printf("Forcing time update %d\n",ntpClient->forceUpdate());
  setTime(ntpClient->getEpochTime());
}

void TimeGFX::setColor(uint16_t c) {
  _canvas->setTextColor(c);
}

void TimeGFX::setTimezoneRules(TimeChangeRule std, TimeChangeRule day) {
  tz.setRules(std, day);
}

time_t TimeGFX::getTime() {
  // Serial.print("Getting time - ");
  ntpClient->update();
  // Serial.println(tz.toLocal(ntpClient->getEpochTime()));
  return tz.toLocal(ntpClient->getEpochTime());
}

void TimeGFX::setLayout(bool l) {
  _layout = l;
  if(_canvas)
    delete _canvas;
  if(l) {
    _canvas = new GFXcanvas16(7, 11);
    _canvasWidth = 7;
    _canvasHeight = 11;
  }
  else {
    _canvas = new GFXcanvas16(17,5);
    _canvasWidth = 17;
    _canvasHeight = 5;
  }
  _canvas->setTextWrap(false);
  _canvas->setFont(&TomThumb);
  _canvas->setTextColor(_color);
}

uint16_t * TimeGFX::getCanvas() {
  Serial.println("Getting buffer");
  buildCanvas();
  return _canvas->getBuffer();
}

void TimeGFX::buildCanvas() {
  time_t t = getTime();
  Serial.println("Building canvas");
  char digitBuf[4] = "";
  _canvas->fillScreen(0);
  if(_layout) {
    if(hourFormat12(t)<10) {
      _canvas->setCursor(4, 5);
      sprintf(digitBuf, "%.1d", hourFormat12(t));
      Serial.printf("Hours : %.1d ", hourFormat12(t));
      _canvas->print(hour(t));
    }
    else {
      _canvas->setCursor(0, 5);
      sprintf(digitBuf, "%.2d", hour(t));
      Serial.printf("Hours : %.2d ", hour(t));
      _canvas->print(digitBuf);
    }
    _canvas->setCursor(0, 11);
    sprintf(digitBuf, "%.2d", minute(t));
    Serial.printf(" Minutes : %0.2d\n", minute(t));
    _canvas->print(minute(t));      
  }
  else {
    _textWidth=0;
    Serial.println("Drawing horizontal time");
    if(hourFormat12(t)<10) {
      _canvas->setCursor(4, 5);
      sprintf(digitBuf, "%.1d", hourFormat12(t));
      _canvas->print(digitBuf);
      _textWidth=13;
    }
    else {
      _canvas->setCursor(0, 5);
      sprintf(digitBuf, "%.2d", hourFormat12(t));
      // Serial.printf("Hours : %.2d ", hour(getTime()));
      _canvas->print(digitBuf);
      _textWidth=17;
    }
    _canvas->setCursor(8, 5);
    sprintf(digitBuf, ":%.2d", minute(t));
    // Serial.printf("Minutes : %.2d", minute(getTime()));
    _canvas->print(digitBuf);       
  }
}