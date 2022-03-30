// #ifndef CLOUDS_H
// #define CLOUDS_H
// #define CLOUDS_DEBUG

// #include <stdint.h>
// #include <vector>
// #include "weather.h"
// #include "sky.h"

// #define MOVE_SPEED 4000
// #define FADE_IN 1
// #define FADE_OUT -1
// #define NO_FADE 0
// #define MOVE_1PX_AT_1MPH 30000
// #define TIME_BETWEEN_FRAMES 16

// const uint16_t cloudColors[5][3] = {{ 0xFFFF, 0xef5d, 0xd6ba},
//                                     { 0xd6ba, 0xbdf7, 0xad55},
//                                     { 0xad55, 0x9492, 0x7bcf},
//                                     { 0x7bcf, 0x62ec, 0x4228},
//                                     { 0x1042, 0x1042, 0x1042}};

// const uint8_t cloudPositions[64][2] = { {6,1}, {6,2}, {5,2}, {7,2}, {1,1}, {2,1}, {0,2}, {1,2}, 
//                                         {10,2}, {11,2}, {9,2}, {9,1}, {14,3}, {15,3}, {15,2}, {13,3},

//                                         {2,3}, {3,3}, {3,2}, {1,3}, {8,1}, {9,3}, {8,3}, {11,1},
//                                         {12,0}, {14,2}, {14,1}, {15,1}, {5,1}, {5,0}, {7,0}, {6,0},

//                                         {11,3}, {10,1}, {10,0}, {9,0}, {1,0}, {0,0}, {3,0}, {2,2},
//                                         {7,3}, {6,3}, {4,1}, {4,2}, {12,1}, {13,1}, {12,3}, {15,0},

//                                         {13,2}, {12,2}, {13,0}, {14,0}, {11,0}, {8,0}, {10,3}, {8,2},
//                                         {4,0}, {5,3}, {4,3}, {7,1}, {0,1}, {2,0}, {3,1}, {0,3}
//                                       };



// struct Cloud {
//   uint8_t x;
//   uint8_t y;
//   int8_t fade;
//   uint8_t alpha;
//   bool operator==(Cloud &rhs) const {
//   return rhs.x==x && rhs.y == y;
//   }
// };

// class Clouds : private Weather {
//   private:
//     std::vector<Cloud> _clouds;
//     uint8_t _cloudColorIndex;
//     GFXcanvas16 _canvas;
//     Sky *_sky; 
//     float _offset;
//     uint32_t _offsetTime;
//     uint32_t _nextCloudAction;

//     void buildClouds();
//     bool cloudExists(const Cloud &newCloud);
//     void moveClouds();
//     void setCloudColorIndex();

//   public:

//     Clouds();
//     void setConditions(OpenWeatherMapCurrentData *data) override;
//     bool next() override;
//     GFXcanvas16*  screenBuffer() override;
//     void setSky(Sky *sky);
    
// };
// #endif