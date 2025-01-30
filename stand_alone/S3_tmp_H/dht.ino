
#include "DHT.h"

#define DHTPIN 3
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

float tmpOffset = 0;
float humOffset = 0;

char tmpStr[8];
char humStr[8];

void setup_dht() {
  dht.begin();
}

char* dht_getTmp() {
  // Read temperature in Celsius (the default)
  dtostrf((tmpOffset + dht.readTemperature()), 6, 2, tmpStr);
  return tmpStr;
}

char* dht_getHum() {
  dtostrf((humOffset + dht.readHumidity()), 6, 2, humStr);
  return humStr;
}

void dht_setTmpOffset(const String newTOS) {
  tmpOffset = newTOS.toFloat();
}

void dht_setHumOffset(const String newHOS) {
  humOffset = newHOS.toFloat();
}
