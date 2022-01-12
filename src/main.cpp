#include <Arduino.h>
#include <Wire.h>
#include <sensor_readings.h>
#include <TFT_eSPI.h>
#include <I2C_Scan.h>
#include <settings.h>

// void refresh_reading();
// void I2C_Scan();

Adafruit_BME280 bme; //I2C
TwoWire I2CBME = TwoWire(0);

TFT_eSPI tft = TFT_eSPI();

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(BME280_Addr);
  // I2C_Scan();
  tft.init();

  tft.setTextColor(fg, bg);
  tft.loadFont("SansSerif-36");
  tft.setRotation(3);
  tft.fillScreen(bg);
  tft.setCursor(5, 5);
  tft.println("ShieldKhan Loading...");
  tft.println("Starting I2C Scan  ...");

  bool status;

  //
  status = bme.begin(BME280_Addr);

  if (!status)
  {
    Serial.println("could not find a valid BME280 seonsor, Check Wiring");
    I2C_Scan();
    while (0)
      ;
  }
  else
  {
    Serial.println("BME280 Sensor Found");
    Serial.print("TFT_LCD Loaded!");
  }

  tft.fillScreen(bg); // Clear the Screen
}

void loop()
{
  // put your main code here, to run repeatedly:
  refresh_reading(&bme, &tft);
  I2C_Scan();
}
