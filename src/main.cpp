#include <Arduino.h>
#include <Wire.h>
#include <sensor_readings.h>
#include <TFT_eSPI.h>
#include <I2C_Scan.h>
#include <settings.h>
#include <SPIFFS.h>
#include <DHT.h>
// #include <dht22_reading.h>

void refresh_reading();
void I2C_Scan();

Adafruit_BME280 bme; //I2C
TwoWire I2CBME = TwoWire(0);

#define DHTPIN 22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE); //DHT22 Define

TFT_eSPI tft = TFT_eSPI();

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS initialization faild!");
    while (1)
      yield();
  }

  Wire.begin();
  Wire.beginTransmission(BME280_Addr);
  I2C_Scan();
  tft.init();

  tft.setTextColor(fg, bg);
  tft.loadFont("SpoqaHanSansNeoBold15");
  tft.setRotation(3);
  tft.fillScreen(bg);
  tft.setCursor(5, 5);
  tft.loadFont("SpoqaHanSansNeoBold15");
  tft.println("ShieldKhan Loading...");
  tft.println("Starting I2C Scan...");

  bool status;

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
  dht.begin();

  tft.fillScreen(bg); // Clear the Screen
}

void loop()
{
  // put your main code here, to run repeatedly:
  refresh_reading(&bme, &tft);
  I2C_Scan();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
}
