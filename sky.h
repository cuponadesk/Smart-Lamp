#ifndef SKY_H
#define SKY_H

#include "OpenWeatherMapCurrent.h"
#include <Adafruit_GFX.h>
#include "weather.h"

const uint16_t skyColors[7] = {0x0, 0x1084, 0x1a9, 0x0087, 0xe5, 0x18a6, 0x1084};

class Sky : private Weather {

  private:
    uint8_t _skyColor = 0;
    GFXcanvas16 _canvas;
    bool next() override;


  public:
    Sky();
    void setConditions(OpenWeatherMapCurrentData *data) override;
    GFXcanvas16* screenBuffer() override;
    uint16_t getSkyColor();

};

#endif