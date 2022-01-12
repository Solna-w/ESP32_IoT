#include <Arduino.h>
#include <sensor_readings.h>
#include <settings.h>

void refresh_reading(Adafruit_BME280 *bme, TFT_eSPI *tft)
{

    float f_temperature;
    float f_humidity;
    float f_pressure;
    float f_altitude;

    uint16_t bg = TFT_BLACK;
    // uint16_t fg = TFT_WHITE;

    digitalWrite(LED_BUILTIN, HIGH);

    f_temperature = bme->readTemperature();
    f_humidity = bme->readHumidity();
    f_pressure = bme->readPressure() / 100.0F;
    f_altitude = bme->readAltitude(SEALEVELPRESSURE_HPA);

    tft->setTextColor(TFT_YELLOW, bg);
    tft->loadFont("ChalkboardBold15");
    tft->setCursor(5, 5);
    tft->print("===========TEST ChalkBoard Font============");

    // Temperature
    Serial.print("Temperature: ");
    tft->println(f_temperature);

    // Humidity
    Serial.print("Humidity: ");
    tft->println(f_humidity);

    // Pressure
    Serial.print("Pressure: ");
    tft->println(f_pressure);

    // Altitude
    Serial.print("Altitude: ");
    tft->println(f_altitude);

    digitalWrite(LED_BUILTIN, LOW);
    tft->loadFont("SpoqaHanSansNeoBold15");
    tft->print("============SpoqaHanSansNeoBold Font================");
};
