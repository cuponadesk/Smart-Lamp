// #include "clouds.h"
// #include "gfx.h"
// #include <cmath>

// Clouds::Clouds(): _canvas(32,16) {}

// void Clouds::setSky(Sky *sky) {
//   _sky = sky;
//   _offset = 0;
// }

// void Clouds::setConditions(OpenWeatherMapCurrentData *data){
//   _data = data;
//   setCloudColorIndex();
//   // buildClouds();
//   _next = millis();
//   Serial.printf("cloudColorIndex %d Cloud Percent: %d\n", _cloudColorIndex, _data->clouds);
//   _nextCloudAction = _next;
// }

// void Clouds::setCloudColorIndex(){
//   _data->clouds = 50;

//   switch(_data->weatherId) {

//     case(800) :
//     case(801) :
//       _cloudColorIndex = 0;
//     break;
  
//     case( 802) :
//       _cloudColorIndex = 1;
//     break;

//     case(803) :
//       _cloudColorIndex = 2;
//     break;

//     case(804) :
//       _cloudColorIndex = 3;
//     break;

//     default :
//       _cloudColorIndex = 3;
//   }
//   if( (_data->observationTime < _data->sunrise && _data->observationTime < _data->sunset) || (_data->observationTime > _data->sunrise && _data->observationTime > _data->sunset)) {
//     _cloudColorIndex = 3;
//   }
//   Serial.printf("Observation time: %d Sunrise: %d Sunset %d\n", _data->observationTime, _data->sunrise, _data->sunset);
//   Serial.printf("Sky Color: %d\n", _sky->getSkyColor());
// }

// void Clouds::buildClouds(){

//   for (int i = (_data->clouds) / 2 - 2 ; i > 0; --i) {
//     Serial.println("Doing new cloud");
//     Cloud newCloud;
//     do {
//         int rY = rand() % 4 + 1;
//         int rX = (rand() % 16) * 2 + (rY&1);
//         newCloud.y = rY;
//         newCloud.x = rX;
//         newCloud.fade = 1;
//     } while (cloudExists(newCloud));
//     _clouds.push_back(std::move(newCloud));
//   }
//   Serial.println("Done building clouds"); 
// }

// bool Clouds::cloudExists(const Cloud &newCloud) {
//   for(int i = 0; i < _clouds.size(); i++) {
//     if(newCloud == _clouds[i]) return true;
//   }
//   return false;
// }

// bool Clouds::next(){
//   if( millis() < _next ) {
//     return false;
//   }    
//   if( (_clouds.size() < (64 * _data->clouds) / 100 ) && _nextCloudAction < millis()) {
//     Cloud newCloud;
//     Serial.println("Adding cloud");
//     newCloud.x = cloudPositions[_clouds.size()][0];
//     newCloud.y = cloudPositions[_clouds.size()][1];
//     newCloud.fade = NO_FADE;
//     newCloud.alpha = 255;
//     _nextCloudAction = millis() + 250;
//     Serial.printf("Cloud clouded X: %d Y:%d\n", newCloud.x, newCloud.y);
//     _clouds.push_back(std::move(newCloud));
//   }
//   //more clouds than needed
//   else if( (_clouds.size() > (64 * _data->clouds) / 100) && _nextCloudAction < millis()) {
//     int i = _clouds.size() - 1;
//     Serial.println("Removing cloud");
//     while(_clouds[i--].fade != FADE_OUT) {
//       _clouds[_clouds.size()-1].fade = FADE_OUT;
//       break;
//     }
//     _nextCloudAction = millis() + 250;
//   }
//   // Serial.println("Next step 2");
//   // moveClouds();    
//   _next = millis() + TIME_BETWEEN_FRAMES;
//   // Serial.println("Returning true");
//   return true;
// }

// void Clouds::moveClouds(){

//   //if we've offset the full width, reset it to 0
//   if(_offset > 32) { _offset -= 32; }

//   _offset += static_cast<float>((millis() - _next) + TIME_BETWEEN_FRAMES) / static_cast<float>(MOVE_1PX_AT_1MPH / _data->windSpeed);

// };


// GFXcanvas16* Clouds::screenBuffer(){
//   // Serial.println(_clouds.size());

//   if(!next()) return &_canvas;

//   GFXcanvas16 t = GFXcanvas16(32,16);

//   t.fillScreen(_sky->getSkyColor());

//   double intPart;
//   double fractPart = modf(_offset, &intPart);

//   // for(int i = 0; i < _clouds.size(); i++) {
//   //   if(_clouds[i].fade == FADE_IN) {
//   //     if(_clouds[i].alpha > 249) {
//   //       _clouds[i].alpha = 255;
//   //       _clouds[i].fade = NO_FADE;
//   //     }
//   //     else {
//   //       _clouds[i].alpha += 3;
//   //     }
//   //   }
//   //   else if(_clouds[i].fade == FADE_OUT) {
//   //     if(_clouds[i].alpha < 5) {
//   //       _clouds[i].alpha = 0;
//   //       _clouds[i].fade = NO_FADE;
//   //     }
//   //     else {
//   //       _clouds[i].alpha -= 3;
//   //     }
//   //   }
//   // }

//   // // for(int i = 0; i < _clouds.size(); i++) {
//   // //   if(_clouds[i].alpha == 0 && _clouds[i].fade == NO_FADE) {
//   // //     _clouds.erase(_clouds.begin()+i);
//   // //     i--;
//   // //   }
//   // // }

//   for(int i = 0; i < _clouds.size(); i++) {
//     t.drawPixel( _clouds[i].x*2 + intPart , 
//                  _clouds[i].y,
//                  blendColors( cloudColors[_cloudColorIndex][i*3/64],
//                               _sky->getSkyColor(),
//                               _clouds[i].alpha
//                             )
//                );
//     t.drawPixel( _clouds[i].x*2+1 + intPart , 
//                  _clouds[i].y,
//                  blendColors( cloudColors[_cloudColorIndex][i*3/64],
//                               _sky->getSkyColor(),
//                               _clouds[i].alpha
//                             )
//                );
//   }
//   for(int j = 0; j < 4; j++) {
//     uint16_t leftPx;
//     uint16_t rightPx;
//     for(int i = 0; i < 32; i++) {
//       // Serial.printf("Left pixel location: %d %d\n",i,j);
//       // Serial.printf("Right pixel location: %d %d\n", (i+1)%32, j);    
//       leftPx = t.getPixel(i,j);
//       rightPx = t.getPixel((i+1)%32, j);
//       // Serial.printf("Left pixel color: %d\n",leftPx);
//       // Serial.printf("Right pixel color: %d\n", rightPx);    
//       // Serial.printf("Fractpart %f\n", fractPart);
//       _canvas.drawPixel((i+1)%32, j , blendColors(leftPx, rightPx, fractPart*100*255/100));
//       // Serial.printf("Right pixel color: %d\n", rightPx);    
//     }
//     leftPx = t.getPixel(31,j);
//     rightPx = t.getPixel(0, j);
//     _canvas.drawPixel(0, j , blendColors(leftPx, rightPx, fractPart*100*255/100));
//   }


//   // Serial.printf("Clouds: %d Pixel Clouds: %d\n", _data->clouds, _clouds.size());
//   // uint8_t left, right, up, down;
//   // for(int i = 0; i < _clouds.size(); i++) {
//   //   // Serial.printf("x: %d - y: %d\n", _clouds[i]->x,_clouds[i]->y);
//   //   left = ( _clouds[i].x == 0 ? 31 : _clouds[i].x- 1); //Pixels left and right of the center. Handles wrap around.
//   //   right = ( _clouds[i].x == 31 ? 0 : _clouds[i].x+ 1);
//   //   up = _clouds[i].y - 1;
//   //   down = _clouds[i].y + 1;
//   //       //Blend cloud edges if they overlap with other cloud edges
//   //   if(_clouds[i].x & 1 || _cloudColorIndex > 1) {
//   //     _canvas.drawPixel(left, up, cloudColors[_cloudColorIndex][2]);
//   //     _canvas.drawPixel(right, down, cloudColors[_cloudColorIndex][2]);
//   //   }
//   //   else {
//   //     _canvas.drawPixel(right, up, cloudColors[_cloudColorIndex][2]);
//   //     _canvas.drawPixel(left, down, cloudColors[_cloudColorIndex][2]);
//   //   }
//   //   //Blend cloud edges if they overlap with other cloud edges
//   //   _canvas.drawPixel(left, _clouds[i].y, cloudColors[_cloudColorIndex][1]);
//   //   _canvas.drawPixel(right, _clouds[i].y, cloudColors[_cloudColorIndex][1]);
//   //   _canvas.drawPixel(_clouds[i].x, up, cloudColors[_cloudColorIndex][1]);
//   //   _canvas.drawPixel(_clouds[i].x, down, cloudColors[_cloudColorIndex][1]);
//   //   //Main cloud body
//   //   _canvas.drawPixel(_clouds[i].x, _clouds[i].y, cloudColors[_cloudColorIndex][0]);
//   // }

//   return &_canvas;
// }