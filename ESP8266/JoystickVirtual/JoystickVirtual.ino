/* JOYSTICK VIRTUAL
 
 Para su funcionamiento es necesario guardar el fichero index.html 
 (http://www.esploradores.com/wp-content/uploads/2017/03/index.zip) 
 en el Sistema de Archivos para Memoria Flash (SPIFF).
 
 Esto se realiza utilizando el complemento del IDE de Arduino ESP8266FS  
 (https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.3.0/ESP8266FS-0.3.0.zip)
 
 Este código de ejemplo es de público dominio.
 Dani No www.esploradores.com   */
 
#include <ESP8266WiFi.h>                      //Librería de conexión WiFi del módulo ESP8266
#include <ESP8266WebServer.h>                 //Librería ESP8266WebServer (simplifica la creación del servidor)
#include "FS.h"                               //Librería del Sistema de Archivos para Memoria Flash (SPIFFS)
 
const char *ssid = "xxxxxxx",        // Credenciales del Punto de Acceso
           *password = "xxxxxx";
int contconexion = 0;
 
ESP8266WebServer server(80);            
 
void setup() {
 
  Serial.begin(115200); Serial.println("");   // Inicialización del Puerto Serie
  SPIFFS.begin();                             // Inicializamos el sistema de Archivos para Memoria Flash (SPIFFS)
  
   WiFi.softAP(ssid, password);  
 /* 
  WiFi.mode(WIFI_STA); //para que no inicie el SoftAP en el modo normal
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED and contconexion <50) { //Cuenta hasta 50 si no se puede conectar lo cancela
    ++contconexion;
    delay(500);
    Serial.print(".");
  }
  if (contconexion <50) {
      //para usar con ip fija
      IPAddress Ip(192,168,1,180); 
      IPAddress Gateway(192,168,1,1); 
      IPAddress Subnet(255,255,255,0); 
      WiFi.config(Ip, Gateway, Subnet); 
      Serial.println("");
      Serial.println("WiFi conectado");
      Serial.println(WiFi.localIP());
  }
  else { 
      Serial.println("");
      Serial.println("Error de conexion");
  }
 */
  server.on("/", []() {                       // Sirve la página index.html desde el SPIFFS cuando se solicita
    File index = SPIFFS.open("/index.html", "r");
    server.streamFile(index, "text/html");
    index.close();
  });
  server.on("/stick", []() {                  // Recibe los datos (dx y dy)
    String dx=server.arg("dx");
    String dy=server.arg("dy");
    server.send(200);
    int x = dx.toInt();                       // Convierte los datos de tipo String a Int      
    int y = dy.toInt();
    Serial.print(x);  Serial.print("  ");  Serial.println(y);  
  }); 
 
  server.begin();                             // Inicializa el servidor
}
 
void loop() {
  server.handleClient();
}
