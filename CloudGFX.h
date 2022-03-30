#ifndef CLOUD_GFX
#define CLOUD_GFX

#include <stdint.h>
#include <vector>
#include <Adafruit_GFX.h>
#include "OpenWeatherMapCurrent.h"
#include "Point.h"

const uint16_t cloudColors[5][3] = {{ 0x8410, 0xc618, 0xFFFF},
                                    { 0x4208, 0x8410, 0xa514},
                                    { 0x4208, 0x8410, 0xa514},
                                    { 0x41e8, 0x28c5, 0x1042},
                                    { 0x1042, 0x1042, 0x1042}};

const Point cloudStartPositions[25] = { Point(18,3), Point(0,3), Point(24,1), Point(7,2), Point(15,1),
                                   Point(31,1), Point(29,3), Point(11,2), Point(13,4), Point(20,1),
                                    Point(25,4), Point(0,1), Point(8,5), Point(23,4), Point(18,2),
                                     Point(16,4), Point(4,1), Point(28,2), Point(11,4), Point(12,1),
                                      Point(4,4), Point(31,3), Point(28,4), Point(8,1), Point(23,1)};
const uint8_t cloudStartPattern[25] = { 1, 1, 3, 3, 4,
                                   2, 5, 2, 6, 5,
                                    4, 1, 6, 6, 2,
                                     4, 3, 6, 7, 3,
                                      4, 7, 7, 4, 7};

const std::vector<std::vector<Point>> cloudPatterns = 
{ 
  { Point(0,0), Point(2,-1), Point(3,-1), Point(1,0), Point(2,0), Point(3,0), Point(-1,1), Point(0,1), Point(1,1), Point(2,1), Point(3,1), Point(4,1) },
  { Point(0,0), Point(-1,0), Point(0,-1), Point(1,0) },
  { Point(1,-1), Point(0,0), Point(1,0), Point(2,0), Point(-1,1), Point(0,1), Point(1,1), Point(2,1) },
  { Point(0,-1), Point(1,-1), Point(-1,0), Point(0,0), Point(1,0), Point(2,0), Point(0,1), Point(1,1) },
  { Point(0,-1), Point(-1,0), Point(0,0), Point(1,0), Point(0,1), Point(1,1), Point(2,1) },
  { Point(-1,-1), Point(0,-1), Point(1,-1), Point(2,-1), Point(-1,0), Point(0,0), Point(1,0), Point(2,0) },
  { Point(-1,-1), Point(0,-1), Point(-1,0), Point(0,0) }
};



class Clouds {
  private:
    GFXcanvas16 _canvas;  //Canvas the clouds are drawn on
    uint16_t _cloudColorIndex;
    uint8_t _width, _height; //width and height to make the canvas.
    OpenWeatherMapCurrentData *_data;
    uint32_t _nextCloudMove;
    uint8_t _offset = 0;




  /*!
  @brief  Draws clouds on cloud canvas
  */
  void drawClouds() {
    _canvas.fillScreen(0);
    Serial.println("Drawing clouds");
    Serial.printf("Desired clouds: %d\n", desiredClouds());
    for (int i = 0; i < desiredClouds(); i++) {

      drawCloud(i);
    }
  }

  /*!
  @brief  Function returns number of clouds based on cloud coverage percentage
  @returns Number of clouds to draw
  */
  int desiredClouds() {
  if(_data->clouds>= 98) {
    return 25;
  }
  else if(_data->clouds>= 96) {
    return 24;
  }
  else if(_data->clouds>= 94) {
    return 23;
  }
  else if(_data->clouds>= 93) {
    return 22;
  }
  else if(_data->clouds>= 92) {
    return 21;
  }
  else if(_data->clouds>= 89) {
    return 20;
  }
  else if(_data->clouds>= 85) {
    return 19;
  }
  else if(_data->clouds>= 83) {
    return 18;
  }
  else if(_data->clouds>= 79) {
    return 17;
  }
  else if(_data->clouds>= 75) {
    return 16;
  }
  else if(_data->clouds>= 73) {
    return 15;
  }
  else if(_data->clouds>= 70) {
    return 14;
  }
  else if(_data->clouds>= 67) {
    return 13;
  }
  else if(_data->clouds>= 60) {
    return 12;
  }
  else if(_data->clouds>= 58) {
    return 11;
  }
  else if(_data->clouds>= 53) {
    return 10;
  }
  else if(_data->clouds>= 50) {
    return 9;
  }
  else if(_data->clouds>= 44) {
    return 8;
  }
  else if(_data->clouds>= 41) {
    return 7;
  }
  else if(_data->clouds>= 36) {
    return 6;
  }
  else if(_data->clouds>= 34) {
    return 5;
  }
  else if(_data->clouds>= 29) {
    return 4;
  }
  else if(_data->clouds>= 24) {
    return 3;
  }
  else if(_data->clouds>= 18) {
    return 2;
  }
  else if(_data->clouds>= 9) {
    return 1;
  }
  return 0;
}


  /*!
  @brief  Draws a single cloud on cloud canvas
  @param  C   Cloud to be drawn
  */
  void drawCloud(uint8_t c) { 

    for(auto p : cloudPatterns[cloudStartPattern[c]-1]) {
      Serial.printf("X:%d Y:%d\n", (cloudStartPositions[c].x + p.x + _offset) % 32, cloudStartPositions[c].y + p.y);
      _canvas.drawPixel((cloudStartPositions[c].x + p.x + _offset) % 32, cloudStartPositions[c].y + p.y, cloudColors[_cloudColorIndex][rand()%3]);
    }
  }


  public:

  
  Clouds() :_canvas(32,6){
    _width = 32;
    _height = 6;
  }

  void setConditions(OpenWeatherMapCurrentData *data){
    _data = data;
    _nextCloudMove = millis();
    if(_data->clouds <= 25) {
      _cloudColorIndex = 0;
    }
    else if(_data->clouds > 25 && _data->clouds <= 50) {
      _cloudColorIndex = 1;
    }
    else if(_data->clouds > 50 && _data->clouds <= 75) {
      _cloudColorIndex = 2;
    }
    else if(_data->clouds > 75 && _data->clouds <= 100) {
      _cloudColorIndex = 3;
    }

    if( (_data->observationTime < _data->sunrise && _data->observationTime < _data->sunset) || (_data->observationTime > _data->sunrise && _data->observationTime > _data->sunset)) {
      _cloudColorIndex = 4;
    }
    Serial.printf("Observation time: %d Sunrise: %d Sunset %d\n", _data->observationTime, _data->sunrise, _data->sunset);
  }

  GFXcanvas16 * screenBuffer() {

    if(millis()> _nextCloudMove && _data->windSpeed) {
      _offset = (_offset == 31 ? 0 : _offset+1);
      _nextCloudMove = millis()+40000/_data->windSpeed;
      drawClouds();
    }
    
    return &_canvas;
  }


};

#endif