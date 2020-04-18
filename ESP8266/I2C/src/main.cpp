#include <Arduino.h>
#include <Wire.h>

void setup()
{

  pinMode(D0, OUTPUT);
  Serial.begin(115200);
  Wire.begin(D2, D1); /* I2C bus  SDA=D2 and SCL=D1 */
}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Escaneando...");
  Serial.println("**************");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Encontrado dispositivo I2C dirección 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  Serial.println("**************");
  delay(2000); 
}
