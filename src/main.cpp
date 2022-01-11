#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define I2C_SDA 21
#define I2C_SCL 22

void refresh_reading();
void I2C_Scan();

#define SEALEVELPRESSURE_HPA (1013.25)

TwoWire I2CBME = TwoWire(0);
Adafruit_BME280 bme; //I2C

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  // I2C_Scan();

  I2CBME.begin(I2C_SDA, I2C_SCL, 100000);
  bool status;

  //
  Serial.println((int)&I2CBME, HEX);
  status = bme.begin(0x76, &I2CBME);

  if (!status)
  {
    Serial.println("could not find a valid BME280 seonsor, Check Wiring");
    I2C_Scan();
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

  // put your main code here, to run repeatedly:
  refresh_reading();
  delay(2000);
}