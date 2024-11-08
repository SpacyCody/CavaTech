//Screen
#include "U8g2lib.h"
#include "SPI.h"

//Temperature and humidity sensor
#include "DHT.h"

//Temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

//Temperature and humidity sensor
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Temperature sensor
#define SENSOR_PORT 4

OneWire oneWire(SENSOR_PORT);
DallasTemperature sensors(&oneWire);

// Screen
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
}

void loop() {
  screen(dht.readTemperature(), dht.readHumidity());

  // printTime();
  // printTemps(dht.readTemperature(), getTempFromTempSensor());
  // printHuminity(dht.readHumidity());
  // delay(10000);
}

float getTempFromTempSensor(){
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

void printTemps(float dhtTemp, float temp){
  Serial.print("Temperatur: DHT: ");
  Serial.print(dhtTemp);
  Serial.print(" C, Temp: ");
  Serial.print(temp);
  Serial.println(" C");
}

void printHuminity(float humidity){
  Serial.print("Luftfuktighet: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void printTime(){
  Serial.print("Time:");
  int time = millis()/1000;
  Serial.println(time);
}

void screen(int dhtTemp, int humidity){
  std::string text = "" + std::to_string(dhtTemp) + " C, " + std::to_string(humidity) + "%";
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 24, text.c_str());
  u8g2.sendBuffer();
}