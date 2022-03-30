#ifndef Lightning_H
#define Lightning_H

#include <stdint.h>
#include <Adafruit_GFX.h>
#include "OpenWeatherMapCurrent.h"
#include "Point.h"
#include "Weather.h"

const uint16_t boltColors[3] = { 14816, 31712, 48608 };

struct Bolt {
  uint8_t point;
  uint8_t depth;
  Point points[16] = { Point(0,0),
                       Point(0,1),
                       Point(-1,2),
                       Point(-2,3), 
                       Point(0,3), 
                       Point(-3,4), 
                       Point(0,4), 
                       Point(1,5),
                       Point(0,6), 
                       Point(2,6),
                       Point(-1,7),
                       Point(3,7),
                       Point(-1,8),
                       Point(0,9),
                       Point(1,10),
                       Point(1,11)};
};

class Lightning : private Weather {
  private:   
    Bolt lightning;
    GFXcanvas16 _canvas;
    uint32_t _lastFrame;

  public:
    Lightning();
    void setConditions(OpenWeatherMapCurrentData *data) override;
    bool next() override;
    GFXcanvas16* screenBuffer() override;
    
};

#endif