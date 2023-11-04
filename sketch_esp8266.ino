#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Configurações WiFi
const char* ssid = "FAMILIA RODRIGUES";
const char* password = "";

// Configuração MQTT
const char* mqtt_server = ""; // Substitua pelo IP do seu PC onde o Mosquitto está rodando.
const char* mqtt_user = "username";  // O nome de usuário que você definiu com mosquitto_passwd
const char* mqtt_password = "password"; // A senha que você definiu
const char* mqtt_topic = "esp8266/alerta";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMessageSent = 0;

void setup_wifi() {
    Serial.println("Conectando ao WiFi...");
    delay(10);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Tentando conectar ao WiFi...");
        delay(500);
    }
    Serial.println("Conectado ao WiFi!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conectar MQTT...");
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    Serial.print("Recebido do Arduino: ");
    Serial.println(received);

    if (received.startsWith("ALERTA:")) {
      Serial.println("ESP8266: Alerta recebido e confirmado.");
      client.publish(mqtt_topic, "Objeto detectado próximo!");  // Publica mensagem no tópico MQTT
    }
  }

  if (millis() - lastMessageSent > 6000) {
    Serial.println("Olá Arduino");
    lastMessageSent = millis();
  }
  
  delay(100);
}
