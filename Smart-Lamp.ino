#include <stdint.h>

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <gfxfont.h>
#include <DNSServer.h>
#include <WiFiUdp.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

#include "ClockGFX.h"
#include "weathergfx.h"
#include "ClockGFX.h"
#include "ESPTouch.h"

#define MATRIX_PIN 12
#define WIDTH 32
#define HEIGHT 16

#define ON_OFF_BUTTON_PIN T3
#define TOP_BUTTON_PIN T1
#define MIDDLE_BUTTON_PIN T0
#define BOTTOM_BUTTON_PIN T2

#define MODE_OFF 0
#define MODE_WEATHER 1
#define MODE_LAMP 2
#define NUM_LAMP_MODES 3

uint8_t lampMode = MODE_WEATHER;
uint8_t lampModeBeforeOffCommand = 1;
uint8_t brightness = 127;
uint16_t lampColor = 0xffff;
bool drawTime = true;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 1, 1, MATRIX_PIN,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_PROGRESSIVE +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB + NEO_KHZ800);

WiFiManager wifiManager;

WeatherGFX weather = WeatherGFX(WIDTH, HEIGHT);
TimeGFX tGFX;

// ESPTouch powerButton(ON_OFF_BUTTON_PIN);
// ESPTouch middleButton(MIDDLE_BUTTON_PIN);
// ESPTouch topButton(TOP_BUTTON_PIN);
// ESPTouch bottomButton(BOTTOM_BUTTON_PIN);


void setup() {
  Serial.begin(115200);
  
  wifiManager.autoConnect("Lamp");

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(127);
  matrix.setRemapFunction(&mPos);
  // tGFX.updateTime();
  
}

void loop() {

  if( lampMode == MODE_WEATHER) {
    matrix.drawRGBBitmap(0,0,weather.screenBuffer()->getBuffer(),32,16);
  }
  else if(lampMode == MODE_LAMP) {
    matrix.fillScreen(0xfded);
  }

  // if(drawTime) {
  //   if(tGFX.getLayout()) {
  //     matrix.drawRGBBitmap(16, 3, tGFX.getCanvas(), tGFX.canvasWidth(), tGFX.canvasHeight());
  //   }
  //   else {
  //     matrix.drawRGBBitmap((hourFormat12(tGFX.getTime())<10?8:7), 9, tGFX.getCanvas(), tGFX.canvasWidth(), tGFX.canvasHeight());
  //   }
  // }
  matrix.show();
}

// void handleButtons() {
//   int pButton = powerButton.read();
//   int tButton = topButton.read();
//   int mButton = middleButton.read();
//   int bButton = bottomButton.read();

//   switch(pButton) {
//     case LONG_PRESS:
//       lampPowerMode();
//     break;
//     case PRESS:
//       changeLampMode();

//   }
// }

// void lampPowerMode() {
//   if(!lampMode) {
//     lampMode = lampModeBeforeOffCommand;
//     matrix.setBrightness(brightness);
//   }
//   else {
//     lampModeBeforeOffCommand = lampMode;
//     lampMode = 0;
//     matrix.setBrightness(0);
//   }
// }

// void changeLampMode() {
//   lampMode++;
//   if(lampMode == NUM_LAMP_MODES) {
//     lampMode = 1;
//   }
// }




