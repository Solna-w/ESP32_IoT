#include <Arduino.h>
#include <Wire.h>
#include <sensor_readings.h>
#include <settings.h>
#include <TFT_eSPI.h>
#include <Ticker.h>

// void refresh_reading();
void I2C_Scan();

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

  tft.setTextColor(fg, bg);
  tft.loadFont("SansSerif-36");
  tft.setRotation(3);
  tft.setCursor(5, 5);
  tft.println("ShieldKhan Loading...");

  bool status;

  //
  status = bme.begin(BME280_Addr);

  if (!status)
  {
    Serial.println("could not find a valid BME280 seonsor, Check Wiring");
    I2C_Scan();
    while (1)
      ;
  }
  else
  {
    Serial.println("BME280 Sensor Found");
    Serial.print("TFT_LCD Loaded!");
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  refresh_reading(bme);
  delay(2000);
}

void I2C_Scan()
{
  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
  delay(5000);
}