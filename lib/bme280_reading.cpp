#include "Arduino.h"
#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define Addr 0x76
#define I2C_SDA 21
#define I2C_SCL 22

TwoWire I2CSensors = TwoWire(0);

Adafruit_BME280 bme;

float temperature, humidity;

void setup()
{
    Wire.begin();
    Serial.begin(115200);
    I2CSensors.begin(I2C_SCL, I2C_SDA, 100000);

    if (!bme.begin(0x76, &I2CSensors))
    {
        Serial.println("Couldn't Find BME280 Sensor");
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
    Wire.beginTransmission(Addr);
    unsigned int b1[24];
    unsigned int data[8];
    unsigned int dig_H1 = 0;
    for (int i = 0; i < 24; i++)
    {
        // Start I2C Transmission
        Wire.beginTransmission(Addr);
        // Select data register
        Wire.write((136 + i));
        // Stop I2C Transmission
        Wire.endTransmission();

        // Request 1 byte of data
        Wire.requestFrom(Addr, 1);

        // Read 24 bytes of data
        if (Wire.available() == 1)
        {
            b1[i] = Wire.read();
        }
    }
}