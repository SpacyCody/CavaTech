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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  sensors.begin();
}

void loop() {
  printTime();
  printTemps(dht.readTemperature(), getTempFromTempSensor());
  printHuminity(dht.readHumidity());
  delay(10000);
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
