## Conexão com Servidor MQTT
####  HiveMQ
Para gerar credenciais de servidor no hive MQ
1. abrir https://console.hivemq.cloud/ e realizar login
2. Criar "New Cloud Cluster"
3. Em "Manager Cluster", copiar URL e utilizar na variável "const char* BROKER_MQTT"
4.  Ainda em "Manage Cluster", copiar PORT para a conexão com a porta na função void setup:

 ''void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(SSID, "");
  wifiClient.setInsecure();
**MQTT.setServer(BROKER_MQTT, 8883);**
  MQTT.setCallback(callback);
}'''
5. Criar credenciais de acesso em "Access management"
