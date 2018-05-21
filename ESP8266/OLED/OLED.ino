 #include <ESP8266WiFi.h>
#include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
 #include "SSD1306Spi.h"

 const char *ssid         = "........";
 const char *password     = ".......";

 
SSD1306Spi        display(D9, D10, D8);
 
void setup() {
  WiFi.begin ( ssid, password );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 10 );
  }
 display.init();
  display.flipScreenVertically();
  display.setContrast(20);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "IP:");
  display.drawString(0, 17, WiFi.localIP().toString());
  display.drawString(0, 34, "Martin Chaparro");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 50, "github.com/mdchaparror");
  display.display();

}

void loop() {
  // put your main code here, to run repeatedly:

}
