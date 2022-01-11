#include <Arduino.h>
#include <Wire.h>
#include <sensor_readings.h>
#include <settings.h>

// void refresh_reading();
void I2C_Scan();

Adafruit_BME280 bme; //I2C
TwoWire I2CBME = TwoWire(0);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(BME280_Addr);
  // I2C_Scan();

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