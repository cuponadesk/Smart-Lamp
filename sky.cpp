#include "sky.h"

Sky::Sky() : _canvas(32,16){
}

void Sky::setConditions(OpenWeatherMapCurrentData *data) {
  _data = data;

  Serial.println("Setting sky data.");

  if(_data->observationTime > _data->sunrise && _data->observationTime < _data->sunset){
    if(_data->weatherId >= 200 &&  _data->weatherId < 700) {
      _skyColor = 1;
    }
    else if(_data->weatherId == 800) {
      _skyColor = 2;
    } 
    else if(_data->weatherId == 801) {
      _skyColor = 3;
    }
    else if(_data->weatherId == 802) {
      _skyColor = 4;
    }
    else if(_data->weatherId == 803) {
      _skyColor = 5;
    }
    else if(_data->weatherId == 804) {
      _skyColor = 6;
    }
  }
  else {
    _skyColor = 0;
  }
  _next = true;
  Serial.printf("Done setting sky data. Skycolor %hx\n", skyColors[_skyColor]);

}

bool Sky::next(){
  return _next;
}

GFXcanvas16* Sky::screenBuffer() {
  if(next()) {
    Serial.println("Drawing sky");
    _next = false;
    _canvas.fillScreen(0xF000);
  }
  return &_canvas;
}

uint16_t Sky::getSkyColor() {
  return skyColors[_skyColor];
}