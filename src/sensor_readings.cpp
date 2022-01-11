#include <Arduino.h>
#include <sensor_readings.h>
#include <settings.h>

void refresh_reading(Adafruit_BME280 bme)
{

    float f_temperature;
    float f_humidity;
    float f_pressure;
    float f_altitude;

    digitalWrite(LED_BUILTIN, HIGH);

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

    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("============================");
};
