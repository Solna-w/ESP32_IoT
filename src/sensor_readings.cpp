#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define Addr 0x76
#define I2C_SDA 21
#define I2C_SCL 22

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme; //I2C

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
