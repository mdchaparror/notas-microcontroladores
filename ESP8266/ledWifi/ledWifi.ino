#include <ESP8266WiFi.h>

const char* ssid = "ssid";
const char* password = "password";

WiFiServer server(80);
int pin =LED_BUILTIN; //led NodeMCU_DEVKIT_1_0
void setup() {
        Serial.begin(115200);
        delay(10);
        pinMode(pin, OUTPUT);
        digitalWrite(pin, 0);

        //conectando a la red  WiFi
        Serial.println();
        Serial.println();
        Serial.print("Connecting to ");
        Serial.println(ssid);

        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
        }
        Serial.println("");
        Serial.println("WiFi connected");

        // Iniciando el servidor
        server.begin();
        Serial.println("Server started");

        // Print the IP address
        Serial.println(WiFi.localIP());
}

void loop() {

        WiFiClient client = server.available();
        if (!client) {
                return;
        }

        while(!client.available()) {
                delay(1);
        }

        String req = client.readStringUntil('\r');
        Serial.println(req);

        delay(1);
        client.flush();

        int val;
        if (req.indexOf("gpio/?estado=ON") != -1)
                val = 0;
        else if (req.indexOf("gpio/?estado=OFF") != -1)
                val = 1;
        else {

                client.print("dato invalido");
                client.stop();
                return;
        }

        digitalWrite(pin, val);
        client.flush();

        // Peparando respuesta par el cliente
        String s = "LED   ";
        s += (val) ? "Apagado" : "Prendido";
        client.print(s);
        delay(1);
}
