#ifndef GFX_HELPER
#define GFX_HELPER

#include <Adafruit_GFX.h>

static uint16_t addColors(const uint16_t fg, const uint16_t bg) {
  // Split foreground into components
  unsigned fg_r = fg >> 11;
  unsigned fg_g = (fg >> 5) & ((1u << 6) - 1);
  unsigned fg_b = fg & ((1u << 5) - 1);

  // Split background into components
  unsigned bg_r = bg >> 11;
  unsigned bg_g = (bg >> 5) & ((1u << 6) - 1);
  unsigned bg_b = bg & ((1u << 5) - 1);

  unsigned out_r = (fg_r + bg_r > 255 ? 255 : fg_r + bg_r);
  unsigned out_g = (fg_g + bg_g > 255 ? 255 : fg_g + bg_g);
  unsigned out_b = (fg_b + bg_b > 255 ? 255 : fg_b + bg_b);

  // Serial.printf("FG red: %d  green: %d  blue: %d\n", fg_r, fg_g, fg_b);
  // Serial.printf("BG red: %d  green: %d  blue: %d\n", bg_r, bg_g, bg_b);
  // Serial.printf("OUT red: %d  green: %d  blue: %d\n", out_r, out_g, out_b);
  return (uint16_t)((out_r << 11) | (out_g << 5) | out_b);
}


static uint16_t blendColors(uint16_t fg, uint16_t bg, uint8_t alpha) {

  // Serial.println("Blending colors 2");
  // yield();
  // Split foreground into components
  unsigned fg_r = fg >> 11;
  unsigned fg_g = (fg >> 5) & ((1u << 6) - 1);
  unsigned fg_b = fg & ((1u << 5) - 1);

  // Split background into components
  unsigned bg_r = bg >> 11;
  unsigned bg_g = (bg >> 5) & ((1u << 6) - 1);
  unsigned bg_b = bg & ((1u << 5) - 1);

  // Alpha blend components
  unsigned out_r = (fg_r * alpha + bg_r * (255 - alpha)) / 255;
  unsigned out_g = (fg_g * alpha + bg_g * (255 - alpha)) / 255;
  unsigned out_b = (fg_b * alpha + bg_b * (255 - alpha)) / 255;

  // Pack result
  return (uint16_t)((out_r << 11) | (out_g << 5) | out_b);
}

static void fillEveryOtherPixel(GFXcanvas16 *_c, uint16_t color) {
  _c->fillScreen(0);
  // Serial.printf("%d %d", _c->width(), _c->height());
  for (int x = 0; x < _c->width(); x++) {
    for (int y = 0; y < _c->height(); y++) {
      if ((!(x & 1) && (y & 1)) || ((x & 1) && !(y & 1))) {
        _c->drawPixel(x, y, color);
      }
    }
  }
}

static void overlay(GFXcanvas16 *_top, GFXcanvas16 *_bottom, int8_t leftStart, int8_t topStart)
{
  // Serial.printf("Overlaying....Width: %d  Height: %d\n", _top->width(), _top->height());
  for(int x = 0; x < _top->width() ; x++) {
    for(int y = 0; y < _top->height(); y++) {
      if( _top->getPixel(x,y) ) {//pixel IS NOT 0,0,0 AKA 0x0000
        // Serial.printf("Getting pixel  X:%d  Y:%d", x,y);
        uint16_t topColor = _top->getPixel(x,y);
        // Serial.println("Drawing pixel");
        _bottom->drawPixel(x,y, topColor);

      }
    }
  }
}

static uint16_t Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}

static uint16_t mPos(uint16_t x, uint16_t y) {
  if ((x & 1)) { //is the column number odd ?
  //Pixel 256 is actually coords(0,8) [y/8)*256] gives the correct begining tile
    return (y/8)*256+(x*8)+7-(y&7); 
  } 
  return (y/8)*256+(x*8)+(y&7);
}

#endif