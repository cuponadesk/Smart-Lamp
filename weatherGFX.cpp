#include "weathergfx.h"

WeatherGFX::WeatherGFX(uint8_t w, uint8_t h) : _canvas(w,h), _width(w), _height(h) {
  _data = new OpenWeatherMapCurrentData();
  wxRefreshTicker.attach(WEATHER_API_UPDATE_INTERVAL,&callAPI);
  callAPI();
}

WeatherGFX::~WeatherGFX(){
    wxRefreshTicker.detach(); 
    delete _data;
}

void WeatherGFX::refreshWeatherData() {
  if(!_updateWeatherFromApi) return;

  _updateWeatherFromApi = false;
  Serial.println("refreshWeatherData");
  OpenWeatherMapCurrent client;
  client.setLanguage("en");
  client.setMetric(false);
  Serial.println("Updating weather _data");
  client.updateCurrent(_data, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID);

  _data->clouds = 9;
  _data->observationTime = _data->sunrise + 100;
  // _data->weatherId = 203;

  
  Serial.println("------------------------------------");

  // "lon": 8.54, float lon;
  Serial.printf("lon: %f\n", _data->lon);
  // "lat": 47.37 float lat;
  Serial.printf("lat: %f\n", _data->lat);
  // "id": 521, weatherId weatherId;
  Serial.printf("weatherId: %d\n", _data->weatherId);
  // "main": "Rain", String main;
  Serial.printf("main: %s\n", _data->main.c_str());
  // "description": "shower rain", String description;
  Serial.printf("description: %s\n", _data->description.c_str());
  // "icon": "09d" String icon; String iconMeteoCon;
  Serial.printf("icon: %s\n", _data->icon.c_str());
  Serial.printf("iconMeteoCon: %s\n", _data->iconMeteoCon.c_str());
  // "temp": 290.56, float temp;
  Serial.printf("temp: %f\n", _data->temp);
  // "pressure": 1013, uint16_t pressure;
  Serial.printf("pressure: %d\n", _data->pressure);
  // "humidity": 87, uint8_t humidity;
  Serial.printf("humidity: %d\n", _data->humidity);
  // "temp_min": 289.15, float tempMin;
  Serial.printf("tempMin: %f\n", _data->tempMin);
  // "temp_max": 292.15 float tempMax;
  Serial.printf("tempMax: %f\n", _data->tempMax);
  // "wind": {"speed": 1.5}, float windSpeed;
  Serial.printf("windSpeed: %f\n", _data->windSpeed);
  // "wind": {"deg": 1.5}, float windDeg;
  Serial.printf("windDeg: %f\n", _data->windDeg);
  // "clouds": {"all": 90}, uint8_t clouds;
  Serial.printf("clouds: %d\n", _data->clouds);
  // "dt": 1527015000, uint64_t observationTime;
  time_t time = _data->observationTime;
  Serial.printf("observationTime: %d, full date: %s", _data->observationTime, ctime(&time));
  // "country": "CH", String country;
  Serial.printf("country: %s\n", _data->country.c_str());
  // "sunrise": 1526960448, uint32_t sunrise;
  time = _data->sunrise;
  Serial.printf("sunrise: %d, full date: %s", _data->sunrise, ctime(&time));
  // "sunset": 1527015901 uint32_t sunset;
  time = _data->sunset;
  Serial.printf("sunset: %d, full date: %s", _data->sunset, ctime(&time));

  // "name": "Zurich", String cityName;
  Serial.printf("cityName: %s\n", _data->cityName.c_str());
  Serial.println();
  Serial.println("---------------------------------------------------/\n");


  updateComponents();

}

void WeatherGFX::updateComponents() {
  Serial.println("Updating components");

  // _sky.setConditions(_data);
  // _lightning.setConditions(_data);
  _clouds.setConditions(_data);
  // _precipitation.setConditions(_data);

}

GFXcanvas16* WeatherGFX::screenBuffer() {

  refreshWeatherData();
  _canvas.fillScreen(_sky.getSkyColor());

  // Serial.println("Overlaying precip");
  // overlay(_precipitation.screenBuffer(), &_canvas, 0, 0);
  // Serial.println("Overlaying lightning");
  // overlay(_lightning.screenBuffer(), &_canvas, 0, 0);
  // Serial.println("Overlaying clouds");
  overlay(_clouds.screenBuffer(), &_canvas, 0, 0);
  return &_canvas;
}

