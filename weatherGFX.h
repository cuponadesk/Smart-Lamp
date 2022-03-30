#ifndef WEATHERGFX_H
#define WEATHERGFX_H

#include <Adafruit_GFX.h>
#include <JsonListener.h>
#include <time.h>
#include "OpenWeatherMapCurrent.h"
#include <Ticker.h>
#include <deque>
#include <utility>
#include <algorithm>
#include <cstdlib>

#include "secret.h"
#include "gfx.h"

#include "lightning.h"
#include "CloudGFX.h"
#include "precipitation.h"
#include "sky.h"

#define CELSIUS TRUE
#define FARHENHEIT FALSE
#define WEATHER_API_UPDATE_INTERVAL 300
#define OPEN_WEATHER_MAP_LOCATION_ID "Sharonville,OH,US"

//Needed for calling API using timer

static bool _updateWeatherFromApi;

static void callAPI(){
  _updateWeatherFromApi = true;
}

////////////////////////////////////

class WeatherGFX {

  public:
    WeatherGFX(uint8_t w, uint8_t h);
    ~WeatherGFX();

    //Update weather data from API
    void refreshWeatherData();
    //Update weather types with new data
    void updateComponents();
    //Call project types screenBuffer method, overlay them and return them
    //to be drawn
    GFXcanvas16* screenBuffer();

  private:
    //Primitive types
    uint8_t _width, _height;

    //Library types
    Ticker wxRefreshTicker; 
    OpenWeatherMapCurrentData *_data;
    GFXcanvas16 _canvas;

    //Project types
    Sky _sky;
    Clouds _clouds;
    Lightning _lightning;
    Precipitation _precipitation;

};

#endif
