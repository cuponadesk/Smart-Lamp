#ifndef WEATHER_H
#define WEATHER_H

#include "OpenWeatherMapCurrent.h"
#include <Adafruit_GFX.h>


class Weather {
  protected:
    uint32_t _next = 0;
    OpenWeatherMapCurrentData *_data;
    
    virtual void setConditions(OpenWeatherMapCurrentData *data) = 0;
    virtual bool next() = 0;
    virtual GFXcanvas16* screenBuffer() = 0;
};

#endif