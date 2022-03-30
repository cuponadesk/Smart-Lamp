// #ifndef PRECIPITATION_GFX
// #define PRECIPITATION_GFX

// #include <stdint.h>
// #include <Adafruit_GFX.h>
// #include <Ticker.h>
// #include <deque>
// #include "gfx.h"

// #define DELAY_MULTIPLIER 1000
// #define DELAY_MOVE 100
// #define Y_START 2

// enum PrecipitationType {SNOW, RAIN, SLEET};
// static const uint16_t precipColors[3] = {0xE75C, 0x019F, 0xAC5E};

// struct Droplet {
//   Droplet(uint8_t xPos, uint8_t yPos, uint8_t pType, uint32_t start) : x(xPos), y(yPos), type(pType), startTime(start){
//     lastMove = start;
//   };
//   uint8_t x, y;
//   uint8_t type;
//   uint32_t startTime;
//   uint32_t lastMove;
// };

// struct Lightning {
//   Lightning(uint8_t xStart) : x(xStart){};
//   uint8_t x;
// };

// class Precipitation
// {
//   public:
//   Precipitation(uint8_t width, uint8_t height) : _width(width), _height(height){
//     _canvas = new GFXcanvas16(width, height);    
//     // animateTicker.attach_ms(16,[this](){ this->update(); });
//   }

//   ~Precipitation() {
//     delete _canvas;
//     animateTicker.detach();
//   }

//   /*!
//   @brief  Set precipitation variables
//   @param  i   Intensity of precip 1-4
//           t   Type of precipitation (SNOW, RAIN, SLEET)
//   */
//   void setPrecip(uint8_t i, PrecipitationType t){
//     _intensity = i;
//     _pt = t;
//     _drops.clear();
//   }

//   void setPrecip(uint16_t wxCode) {
//     int i;
//     PrecipitationType t;
//     if(wxCode >= 200 && wxCode < 600) {
//       t=RAIN;
//       _intensity = 1+ wxCode % 100;
//     }
//     else if(wxCode >= 600 && wxCode <= 602 || wxCode >= 620 && wxCode <= 622){
//       t=SNOW;
//       _intensity = 1+ wxCode % 100;
//     }
//   }
//   /*!
//   @brief  Returns the canvas so it can be drawn
//   */
//   GFXcanvas16 * getCanvas() {
//     return _canvas;
//   }

//   void update(){
//     _updateFlag=true;
//   }

//   /*!
//   @brief  animate the falling of the Droplets
//   @param  
//   */
//   void animate() {
//     uint32_t ct = millis();
//     buildPrecip();    
//     for(int i = 0; i < _drops.size(); i++) {
//       if( _drops[i].lastMove + DELAY_MOVE > ct ) 
//       {
//         _drops[i].y++;
//         _drops[i].lastMove = ct;
//       }
//     }
//     if(_drops.size()) 
//     {
//       drawDrops();
//     }
//   }

//   void isPrecip(){
    
//   }

//   private:
//   //size of the canvas
//   uint8_t _width, _height;
//   std::deque<Droplet> _drops;
//   PrecipitationType _pt;
//   uint8_t _intensity;
//   GFXcanvas16 * _canvas;
//   Ticker animateTicker;
//   boolean _updateFlag = false;

//     /*!
//   @brief  Removes drops that are no longer visible and creates new ones 
//   */
//   void buildPrecip() {
//     //remove drops who arent on screen anymore
//     while(_drops[0].y > 31){
//       _drops.pop_front();
//     }
//     //add a drop if there are too few based on precip conditions
//     while( ( _drops.size() < _intensity*4 ) && (_drops.back().startTime < millis() + DELAY_MULTIPLIER /_intensity) ) {
//       int x = rand()%32;
//       while(dropAtXColumn(x)){x=rand()%32;}
//       _drops.push_back(Droplet( x, Y_START,RAIN, millis()));
//     }

//   }

//   /*!
//   @brief  Function to search the deque for a drop in x position
//   @param  x   Column we want to know if there is already a droplet in it
//   @return true if droplet is in column x otherwise false
//   */
//   bool dropAtXColumn(const int & x){
//     for(int i = 0; i < _drops.size(); ++i) {
//       if (_drops[i].x = x) {
//         return true;
//       }
//     }
//     return false;
//   }
//   /*!
//   @brief  Draws the droplets on the screen
//   */
//   void drawDrops(){
//     _canvas->fillScreen(0);
//     uint16_t dropColor = precipColors[_drops[0].type];
//     uint16_t tailColor = blendColors(dropColor,0,127);
//     for(Droplet &d: _drops) {
//       _canvas->drawPixel(d.x, d.y, dropColor);
//       _canvas->drawPixel(d.x, d.y-1, tailColor);
//     }
//   }

// };

// #endif