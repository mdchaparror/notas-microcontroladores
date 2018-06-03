#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// Wifi: SSID and password
const char* WIFI_SSID = "ssid";
const char* WIFI_PASSWORD = "pass";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "office_light1";
const PROGMEM char* MQTT_SERVER_IP = "192.168.1.105";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "user_mqtt";
const PROGMEM char* MQTT_PASSWORD = "pass_mqtt";
const char* MQTT_TOPIC = "casa/led";
const char* LED_ON = "ON";
const char* LED_OFF = "OFF";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }

  if (String(MQTT_TOPIC).equals(p_topic)) {
    if (payload.equals(String(LED_ON))) {
        digitalWrite(LED_BUILTIN, LOW);      
      }
    else if (payload.equals(String(LED_OFF))) {
       digitalWrite(LED_BUILTIN, HIGH); 
    }
  }
}

void reconnect() {
    while (!client.connected()) {
     Serial.print("INFO: Attempting MQTT connection...");
     if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
       Serial.println("INFO: connected");
       client.subscribe(MQTT_TOPIC);
    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
      Serial.println("DEBUG: try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.print("INFO: Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.print("INFO: IP address: ");
  Serial.println(WiFi.localIP());
  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(callback);

}

void loop() {
   if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
