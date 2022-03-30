#include "lightning.h"

Lightning::Lightning(): _canvas(32,16) {

}

void Lightning::setConditions(OpenWeatherMapCurrentData *data) {
  _data = data;
  if(_data->weatherId >= 200 && _data->weatherId < 300) {
    _next = millis()-1;
  }
  else {
    _next = 0;
  }
}

bool Lightning::next(){
  
  if( millis() > _next && _next ) {
    lightning.point = rand() %26 +3;
    _next = millis() + random(5000,10000);
    _lastFrame = 0;
    lightning.depth = 1;
    _canvas.fillScreen(0);
  }
  return lightning.depth;
}

GFXcanvas16* Lightning::screenBuffer(){

  if( (!next() && !lightning.depth) || (millis() < 40 +  _lastFrame)) return &_canvas;

  _lastFrame = millis();

  Serial.printf("Lightning frame %d\n", millis());

  
  
  if(lightning.depth < 16) {
    for(int i = 0; i < lightning.depth; i++) {
      _canvas.drawPixel( lightning.points[i].x + lightning.point, 
                          lightning.points[i].y + 5, 
                          boltColors[0] );
    }
    lightning.depth+=rand()%3+1;
  }
  else if( lightning.depth > 15 && lightning.depth <= 17 ) {
    for(int i = 0; i < 16; i++) {
      _canvas.drawPixel( lightning.points[i].x + lightning.point,
                          lightning.points[i].y + 4,
                          boltColors[1] );
    }
    lightning.depth++;//=rand()%3+1;
  }
  else if( lightning.depth >= 18 && lightning.depth < 20)  {
    for(int i = 0; i < 16; i++) {
      _canvas.drawPixel( lightning.points[i].x + lightning.point,
                          lightning.points[i].y+4, 
                          boltColors[2] );
    }
    lightning.depth++;//=rand()%3+1;
  }
  else if(lightning.depth==20){
     for(int i = 0; i < 16; i++) {
      //  Serial.printf("X:%d Y:%d ",lightning.points[i].x + lightning.point, lightning.points[i].y+4);
     }
    _canvas.fillScreen(0);
    lightning.depth=0;
  }
  return &_canvas;
}

