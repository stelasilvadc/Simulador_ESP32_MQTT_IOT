#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

#define ID_MQTT "SENAI_IOT01"
#define pubSensor1IotSenai "Sensor1IotSenai"
#define subLed1IotSenai "Led1IotSenai"
#define USERNAME_MQTT "SENAI_IOT01_web_client"
#define PASSWORD_MQTT "Aa123456789"
#define LED_PIN 25

const char* SSID = "Wokwi-GUEST";
const char* BROKER_MQTT = "52068913ceb040eb8f97f47fd7e906fd.s1.eu.hivemq.cloud";

WiFiClientSecure wifiClient;
PubSubClient MQTT(wifiClient);

bool ledState = false;

void setLed(bool estado) {
  digitalWrite(LED_PIN, estado ? HIGH : LOW);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  bool novoEstado = (msg == "1" || msg == "ON");
  ledState = novoEstado;
  setLed(ledState);
  Serial.println("LED " + String(ledState ? "ON" : "OFF") + " (MQTT)");
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(SSID, "");
  wifiClient.setInsecure();
  MQTT.setServer(BROKER_MQTT, 8883);
  MQTT.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    return;
  }

  if (!MQTT.connected()) {
    if (MQTT.connect(ID_MQTT, USERNAME_MQTT, PASSWORD_MQTT)) {
      MQTT.subscribe(subLed1IotSenai);
      Serial.println("MQTT OK");
    }
  }

  MQTT.loop();
}