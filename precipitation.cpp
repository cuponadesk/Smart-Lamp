#include "precipitation.h"

Precipitation::Precipitation() : _canvas(32,16) {
  std::srand ( unsigned ( analogRead(0) ) );
}

void Precipitation::setConditions(OpenWeatherMapCurrentData *data) {

  if(data->weatherId >= 200 && data->weatherId < 700) {

      _next = millis();
      _nextDropTime = _next - 1;

    if( data->weatherId & 0 ) {
      _precipIntensity = 1;
    }
    else if( data->weatherId & 1 ) {
      _precipIntensity = 2;
    }
    else if( data->weatherId & 2 ) {
      _precipIntensity = 3;
    }
    else {
      _precipIntensity = 2;
    }

    //Rain
    if( (data->weatherId >=200  && data->weatherId < 600)) {
      Serial.println("Drawing rain");
      _precipColorIndex = 0;
      _precipFallRate = DEFAULT_FALL_RATE;
    }
    //Snow
    else if ((data->weatherId >=600 && data->weatherId < 700)) {
      Serial.println("Drawing snow");
      _precipFallRate = 3 * DEFAULT_FALL_RATE;
      _precipColorIndex = 2;
    }
    //Sleet or freezing rain
    else if( data->weatherId == 611 || data->weatherId == 511|| data->weatherId == 512 || data->weatherId == 513) {
      Serial.println("Drawing freezing rain");
      _precipFallRate = 2 * DEFAULT_FALL_RATE;
      _precipColorIndex = 1;
    }
  }
  else {
    _precipIntensity = 0;
  }
}

bool Precipitation::next() {
  uint32_t ct = millis();
  //flag to keep track of whether updating canvas is required
  bool draw = false;

  //_next is used to limit FPS to one frame every 16ms
  if(_next  < ct) {
    //Move all drops on screen if necessary
    for(int i=0; i < _drops.size(); i++) {
      //calculate where the drop should be vertically
      int y = 4 + 13 * ( ct - _drops[i].startTime ) / _precipFallRate ;
      //check if the drop needs to be moved
      if(_drops[i].y != y) {
        //mark the drop as moved so it gets drawn
        _drops[i].moved = true;
        //move the drop
        _drops[i].y = y;
        //update draw flag so changes are drawn
        draw = true;
      }
      //flag drop as unmoved so it can be skipped during draw
      else _drops[i].moved = false;
    }
    //Remove drops no longer on screen
    if(_drops[0].y == 17) {
      //add column back to open slots
      _open.push_back( _drops[0].x - _drops[0].x & 1 );
      //remove drop
      _drops.pop_front();
      draw = true;
    }
    //Add new drops if needed
    if(_precipIntensity && _drops.size() < std::pow(2,_precipIntensity) && ct > _nextDropTime) {
      Droplet d = Droplet(_open[0] + rand()&1 , 4, ct);
      _drops.push_back(std::move(d));
      _open.pop_front();
      _nextDropTime = ct + _precipFallRate / std::pow(2,_precipIntensity) + (rand() & 1) * _precipFallRate / std::pow(2,_precipIntensity) / 2; 
      draw = true;
    }
    _next = ct + 16;
  }
  return draw;

}

GFXcanvas16* Precipitation::screenBuffer() {
  for(int i = 0; i < _drops.size(); i++) {
    if(_drops[i].moved) {
      _canvas.drawPixel(_drops[i].x, _drops[i].y - (_drops[i].y == 16) - 1 , 0);
      _canvas.drawPixel(_drops[i].x, _drops[i].y - (_drops[i].y == 16), precipColors[_precipColorIndex]);
    }    
  }
  return &_canvas;
}