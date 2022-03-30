#ifndef CLOUD_GFX
#define CLOUD_GFX

#include <stdint.h>
#include <vector>
#include <Adafruit_GFX.h>
#include "OpenWeatherMapCurrent.h"

const uint16_t cloudColors[5][3] = {{ 0x41e8, 0x28c5, 0x1042},
                                    { 0x41e8, 0x28c5, 0x1042},
                                    { 0x41e8, 0x28c5, 0x1042},
                                    { 0x41e8, 0x28c5, 0x1042},
                                    { 0x1042, 0x1042, 0x1042}};




struct Cloud {
  Cloud(uint8_t xPos, uint8_t yPos, uint8_t cp) : x(xPos), y(yPos), cloudPattern(cp) {};
  uint8_t cloudPattern;
  uint8_t x, y;

};

const Point cloudStartPositions[25] = { Point(18,3), Point(0,3), Point(24,1), Point(7,2), Point(15,1),
                                   Point(31,1), Point(29,3), Point(11,2), Point(13,4), Point(20,1),
                                    Point(25,4), Point(0,1), Point(8,5), Point(23,4), Point(18,2),
                                     Point(16,4), Point(4,1), Point(23,2), Point(11,4), Point(12,1),
                                      Point(4,4), Point(31,3), Point(28,4), Point(8,1), Point(23,1)};
const uint8_t cloudStartPattern[25] = { 1, 1, 3, 3, 4,
                                   2, 5, 2, 6, 5,
                                    4, 1, 6, 6, 2,
                                     4, 3, 6, 7, 3,
                                      1, 7, 7, 4, 7};

const std::vector<std::vector<Point>> cloudPatterns = 
{ 
  { Point(0,0), Point(2,-1), Point(3,-1), Point(1,0), Point(2,0), Point(3,0), Point(-1,1), Point(0,1), Point(1,1), Point(2,1), Point(3,1), Point(4,1) },
  { Point(0,0), Point(-1,0), Point(-1,0), Point(0,1) },
  { Point(-1,-1), Point(0,0), Point(1,0), Point(2,0), Point(-1,1), Point(1,0), Point(1,1), Point(1,2) },
  { Point(0,-1), Point(1,-1), Point(-1,0), Point(0,0), Point(1,0), Point(2,0), Point(0,1), Point(1,2) },
  { Point(0,-1), Point(1,0), Point(0,0), Point(1,0), Point(0,1), Point(1,1), Point(2,1) },
  { Point(-1,-1), Point(0,-1), Point(1,-1), Point(2,-1), Point(-1,0), Point(0,0), Point(1,0), Point(2,0) },
  { Point(-1,-1), Point(0,-1), Point(-1,0), Point(0,0) }
};



class Clouds {
  private:
    std::vector<Cloud> _clouds{}; //Vector for holing all the clouds.
    GFXcanvas16 _canvas;  //Canvas the clouds are drawn on
    uint16_t _cloudColorIndex;
    uint8_t _width, _height; //width and height to make the canvas.
    OpenWeatherMapCurrentData *_data;
    uint32_t _nextCloudMove, _next;
    uint8_t _offset = 0;



    /*!
    @brief  Creates a new cloud in a open position
    */
    // Cloud newCloud() {
    //   // Cloud seedCloud;
    //   // do {
    //   //   // int rY = rand() % 5 + 0;
    //   //   // int rX = (rand() % 16) * 2 + (rY&1);
    //   //   int rY = (rand() % 3) * 2 ;
    //   //   int rX = (rand() % 16) * 2 + (rY == 2? 1 : 0);
    //   //   seedCloud.y = rY;
    //   //   seedCloud.x = rX;
    //   //   Serial.printf("Rand Cloud at x: %d y:%d\n", seedCloud.x, seedCloud.y );
    //   // } while (cloudExists(seedCloud));
    //   // Serial.print("here\n");
    //   // return seedCloud;
    // }


    /*!
    @brief  See if a cloud exists at a position
    @param  newCloud, x, y Coordinates to check to see if it exists.
    */
    // boolean cloudExists(Cloud const newCloud) {
    //   Serial.println("Checking if cloud exists");
    //   return cloudExists(newCloud.x, newCloud.y);
    // }


    // boolean cloudExists(uint8_t x, uint8_t y) {
    //   Serial.println(_clouds.size());
    //   if(_clouds.size() > 0 ) {
    //     for (Cloud c : _clouds) {
    //       Serial.print(".");
    //       yield();
    //       if (c.x == x && c.y == y) {
    //         return true;
    //       }
    //     }
    //   }
    //   Serial.println("Returning false");
    //   return false;
    // }


  /*!
  @brief  Deletes old clouds and builds new cloud vector
  */
  void buildClouds() {
    // Serial.println("Building clouds");
    // while(_data->clouds * 48 / 100 < _clouds.size()) {
    //   Serial.println("Removing cloud");
    //   _clouds.pop_back();
    // }

    //  Serial.printf("Adding clouds. Cloud percentt: %d Desired clouds:%d\n", _data->clouds, _data->clouds * 64 / 100);
    // while(_data->clouds * 48 / 100 > _clouds.size()) {
    //   // Serial.println("Adding cloud");
    //   Serial.println("Adding cloud");
    //   _clouds.push_back(newCloud());
    //   // Serial.println("Cloud added");
    //   // Serial.printf("%d clouds\n", _clouds.size());
    //   // Serial.println("yielding");
    //   // yield();
    // }

  }

  /*!
  @brief  Safely deletes clouds to prevent memory leak and empties cloud vector
  @param  d Vector to delete clouds from 
  */
  // std::vector<Cloud *> deleteClouds(std::vector<Cloud *> &d) {
  //   Serial.println("Clearing clouds");
  //   Serial.printf("Clouds to delete: %d\n", d.size());
  //   for_each(d.begin(), d.end(), DeleteVector<Cloud *>());
  //   // Clear the vector
  //   d.clear();
  //   return d;
  //   Serial.println("Clouds cleared");
  // }


  /*!
  @brief  Draws clouds on cloud canvas
  */
  void drawClouds() {
    _canvas.fillScreen(0);
    Serial.println("Drawing clouds");
    Serial.printf("Desired clouds: %d\n", desiredClouds());
    // Serial.printf("Clouds: %d Pixel Clouds: %d\n", _data->clouds, _clouds.size());
    for (int i = 0; i < desiredClouds(); i++) {
      // Serial.printf("x: %d - y: %d\n", _clouds[i]->x,_clouds[i]->y);
      // drawCloud(_clouds[i]);
      drawCloud(i);
    }
  }

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
      Serial.printf("X:%d Y:%d\n", cloudStartPositions[c].x + p.x + _offset, cloudStartPositions[c].y + p.y);
      _canvas.drawPixel(cloudStartPositions[c].x + p.x + _offset, cloudStartPositions[c].y + p.y, cloudColors[_cloudColorIndex][rand()%3]);
    }

    // const uint8_t &x = c.x;
    // const uint8_t &y = c.y;
    

    

    // uint8_t left = (!(c.x) ? 31 : c.x - 1); //Pixels left and right of the center. Handles wrap around.
    // uint8_t right = (c.x == 31 ? 31 : c.x + 1);
    // uint8_t up = c.y - 1;
    // uint8_t down = c.y + 1;

    // // Serial.printf("X: %d Y: %d Left: %d Right: %d Up: %d Down: %d\n", x, y, left, right, up, down);

    // //Main cloud body
    // _canvas.drawPixel(x, y, cloudColors[_cloudColorIndex][0+ rand()%2*2]);

    // //Blend cloud edges if they overlap with other cloud edges
    // // _canvas.drawPixel(left, y,addColors(_canvas.getPixel(left, y), cloudColors[_cloudColorIndex][2]));
    // // _canvas.drawPixel(right, y, addColors(_canvas.getPixel(right, y), cloudColors[_cloudColorIndex][2]));
    // // _canvas.drawPixel(x, up, addColors(_canvas.getPixel(x, up), cloudColors[_cloudColorIndex][2]));
    // // _canvas.drawPixel(x, down, addColors(_canvas.getPixel(x, down), cloudColors[_cloudColorIndex][2]));

    // // _canvas.drawPixel(left,   y,     cloudColors[_cloudColorIndex][2- rand()%2*2] );
    // _canvas.drawPixel(right,  y,     cloudColors[_cloudColorIndex][2- rand()%2*2] );
    // // _canvas.drawPixel(x,      up,    cloudColors[_cloudColorIndex][2- rand()%2*2] );
    // _canvas.drawPixel(x,      down,  cloudColors[_cloudColorIndex][2- rand()%2*2] );
    // _canvas.drawPixel(right, down, cloudColors[_cloudColorIndex][2- rand()%2*2] );

    // // { 
    // //   _canvas.drawPixel( left, up, addColors(
    // //   _canvas.getPixel(left, up), 0x2104 ));
    // //   _canvas.drawPixel( left, down, addColors(
    // //   _canvas.getPixel(right, up), 0x2104 )); _canvas.drawPixel(
    // //   right, up, addColors( _canvas.getPixel(left, down), 0x2104 ));
    // //   _canvas.drawPixel( right, down, addColors(
    // //   _canvas.getPixel(right, down), 0x2104 ));

    // //   _canvas.drawPixel(_clouds[i]->x+1, _clouds[i]->y, 0x52AA);
    // //   _canvas.drawPixel(_clouds[i]->x-1, _clouds[i]->y, 0x52AA);
    // //   _canvas.drawPixel(_clouds[i]->x, _clouds[i]->y+1, 0x52AA);
    // //   _canvas.drawPixel(_clouds[i]->x, _clouds[i]->y-1, 0x52AA);

    // //   _canvas.drawPixel(_clouds[i]->x+1, _clouds[i]->y+1, 0x31A6);
    // //   _canvas.drawPixel(_clouds[i]->x-1, _clouds[i]->y+1, 0x31A6);
    // //   _canvas.drawPixel(_clouds[i]->x-1, _clouds[i]->y-1, 0x31A6);
    // //   _canvas.drawPixel(_clouds[i]->x-1, _clouds[i]->y-1, 0x31A6);
    // // }
  }


  public:

  
  Clouds() :_canvas(32,6){
    _width = 32;
    _height = 6;
  }
  ~Clouds(){
    
  }





  void setConditions(OpenWeatherMapCurrentData *data){
    _data = data;
    // setCloudColorIndex();
    buildClouds();
    _next = millis();
    // Serial.printf("cloudColorIndex %d Cloud Percent: %d\n", _cloudColorIndex, _data->clouds);
    _nextCloudMove = _next;
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
      // for (int i = 0; i < _clouds.size(); i++) {
      //   _clouds[i].x++;
      //   if(_clouds[i].x>31) {
      //     _clouds[i].x=0;
      //   }
      // }
      _offset = (_offset == 31 ? 0 : _offset+1);
      _nextCloudMove = millis()+40000/_data->windSpeed;
      drawClouds();
    }
    
    return &_canvas;
  }


};

#endif