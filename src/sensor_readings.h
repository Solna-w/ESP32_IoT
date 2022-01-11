#ifndef SENSOR_READINGS_H
#define SENSOR_READINGS_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME280_Addr 0x76
#define SEALEVELPRESSURE_HPA (1013.25)

void refresh_reading(Adafruit_BME280 bme);

#endif