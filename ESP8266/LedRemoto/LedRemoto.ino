
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char *ssid="ssid";
const char *pass="******";

WiFiServer servidorTCP(8266);
WiFiClient clienteTCP;

void setup() {
  
        pinMode(LED_BUILTIN, OUTPUT);//led tarjeta NodeMCU 1.0

        Serial.begin(115200);
        delay(100);
        Serial.println("Led Remoto");
        Serial.print("Conectandose a la red: ");
        Serial.println(ssid);
        WiFi.begin(ssid,pass);
        while(WiFi.status() != WL_CONNECTED) {
                delay(200);
        }
        Serial.print("conectado ip:");
        Serial.println(WiFi.localIP());
        servidorTCP.begin();
}

void loop() {

        if(!clienteTCP.connected()) {
                clienteTCP=servidorTCP.available();
        }else{
                if(clienteTCP.available()>0) {
                        char dato=clienteTCP.read();
                        Serial.write(dato);
                        if(dato=='1') {
                                digitalWrite(LED_BUILTIN, LOW);
                        }else if(dato=='0') {
                                digitalWrite(LED_BUILTIN, HIGH);
                        }
                }
        }

}
