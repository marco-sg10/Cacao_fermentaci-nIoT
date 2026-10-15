#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ===== Sensores =====
extern Adafruit_SHT31 sht31;
extern OneWire oneWire;
extern DallasTemperature dsSensor;

// ===== Inicialización de sensores =====
void initSensors() {
  Wire.begin(26, 27);
  if (!sht31.begin(0x44)) {
    Serial.println("⚠️  No se detectó el sensor SHT31.");
  } else {
    Serial.println("✅ Sensor SHT31 inicializado");
  }
  
  dsSensor.begin();
  int numSensores = dsSensor.getDeviceCount();
  Serial.printf("✅ DS18B20: %d sensor(es) detectado(s)\n", numSensores);
}

// ===== Lectura de sensores =====
struct SensorReadings {
  float temperaturaAmbiente;
  float temperaturaGrano;
  float humedad;
  bool valid;
};

SensorReadings readSensors() {
  SensorReadings readings;
  
  float h = sht31.readHumidity();
  float t = sht31.readTemperature();
  
  dsSensor.requestTemperatures();
  float tGrano = dsSensor.getTempCByIndex(0);
  
  readings.valid = true;
  
  if (isnan(h) || isnan(t)) {
    Serial.println("⚠️ Error leyendo SHT31");
    readings.valid = false;
  }
  
  if (tGrano == DEVICE_DISCONNECTED_C || tGrano < -50 || tGrano > 125) {
    Serial.println("⚠️ Error leyendo DS18B20");
    readings.valid = false;
  }
  
  readings.temperaturaAmbiente = t;
  readings.temperaturaGrano = tGrano;
  readings.humedad = h;
  
  return readings;
}

#endif
