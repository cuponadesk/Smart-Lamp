#ifndef PRECIPITATION_H
#define PRECIPITATION_H

#include <stdint.h>
#include <deque>
#include <vector>
#include "OpenWeatherMapCurrent.h"
#include <Adafruit_GFX.h>
#include <stdlib.h>
#include "weather.h"

#define DEFAULT_FALL_RATE 1000;

const uint16_t precipColors[3] = { 0x2110, 0x480E, 0x1883}; //rain, sleet, snow

struct Droplet {

  Droplet(int c, int r, uint32_t st){x = c; y = r; startTime = st;};

  uint8_t x;
  uint8_t y;
  uint32_t startTime;
  bool moved = true;
};

class Precipitation : private Weather{

  private: 
    uint32_t _nextDropTime = 0;
    uint16_t _precipFallRate = 1000;
    uint16_t _precipIntensity = 0;
    uint8_t _precipColorIndex = 0;

    GFXcanvas16 _canvas;

    std::deque<Droplet> _drops;
    std::deque<uint8_t> _open = {0, 16, 8, 24, 4, 28, 10, 20, 2, 26, 14, 30, 6, 18, 22, 12};

  public:
    Precipitation();
    void setConditions(OpenWeatherMapCurrentData *data) override;
    bool next() override;
    GFXcanvas16* screenBuffer() override;

};


#endif