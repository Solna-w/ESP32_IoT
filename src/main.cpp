#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void refresh_reading();

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme; //I2C

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  bool status;
  status = bme.begin(0x76);

  if (!status)
  {
    Serial.println("could not find a valid BME280 seonsor, Check Wiring");
    while (1)
      ;
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  refresh_reading();
  delay(2000);
}

void refresh_reading()
{
  float f_temperature;
  float f_humidity;
  float f_pressure;
  float f_altitude;

  // digitalWrite(LED_BUILTIN, HIGH);

  f_temperature = bme.readTemperature();
  f_humidity = bme.readHumidity();
  f_pressure = bme.readPressure() / 100.0F;
  f_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);

  // Temperature
  Serial.print("Temperature: ");
  Serial.println(f_temperature);

  // Humidity
  Serial.print("Humidity: ");
  Serial.println(f_humidity);

  // Pressure
  Serial.print("Pressure: ");
  Serial.println(f_pressure);

  // Altitude
  Serial.print("Altitude: ");
  Serial.println(f_altitude);

  // digitalWrite(LED_BUILTIN, LOW);
  Serial.print("============================");
};