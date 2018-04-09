#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define LED_RED      // D1

const char* ssid = "mdchaparror";
const char* password = "un260874";
int contconexion = 0;

String pagina ="<html>"
"<head>"
"<script>"
"var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);"
"connection.onopen = function ()       { connection.send('Connect ' + new Date()); };"
"connection.onerror = function (error) { console.log('WebSocket Error ', error);};"
"connection.onmessage = function (e)   { console.log('Server: ', e.data);};"
"function sendvalue() {"
" var r = parseInt(document.getElementById('r').value).toString(16);"
" var valor = '#'+r;"
" connection.send(valor);"
"}"
"</script>"
"</head>"
"<body>"
"LED Control:<br/><br/>"
"BRILLO: <input id='r' type='range' min='0' max='255' step='1' value='0' oninput='sendvalue();'/><br/>"
"</body>"
"</html>";

ESP8266WebServer server = ESP8266WebServer(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED: {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

            // send message to client
            webSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
           
            if(payload[0] == '#') {
                // we get RGB data

                // decode rgb data
                uint8_t valor = (uint8_t) strtol((const char *) &payload[1], NULL, 16);
                valor=255-valor;
                Serial.println(valor);

                analogWrite(LED_BUILTIN,  valor);
                
            }
            break;
    }
}

void setup() {
  
  Serial.begin(115200);
  Serial.println();

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

  pinMode(LED_BUILTIN, OUTPUT);
  

  // start webSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  if(MDNS.begin("control")) {
    Serial.println("MDNS responder started");
  }

  // handle index
  server.on("/", []() {
      server.send(200, "text/html", pagina);
  });

  server.begin();

  // Add service to MDNS
  MDNS.addService("http", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);

  digitalWrite(LED_BUILTIN,HIGH);
  analogWriteRange(255);

}

void loop() {
    webSocket.loop();
    server.handleClient();
}

