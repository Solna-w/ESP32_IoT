#include <Arduino.h>
#include <Wire.h>
#include "sensor_readings.cpp"

// void refresh_reading();
void I2C_Scan();

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.beginTransmission(Addr);
  // I2C_Scan();

  bool status;

  //
  Serial.println((int)&I2CBME, HEX);
  status = bme.begin(0x76, &I2CBME);

  if (!status)
  {
    Serial.println("could not find a valid BME280 seonsor, Check Wiring");
    I2C_Scan();
    Serial.println(I2C_SCL);
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
  refresh_reading();
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