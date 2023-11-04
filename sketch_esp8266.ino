#include <ESP8266WiFi.h>
#define MQTT_MAX_PACKET_SIZE 512  // Aumenta o tamanho máximo do pacote para 512 bytes
#include <PubSubClient.h>

// Configurações WiFi
const char* ssid = "FAMILIA RODRIGUES";
const char* password = "13016023";

// Configuração MQTT
const char* mqtt_server = "broker.hivemq.com";  // Endereço do broker MQTT da HiveMQ
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

bool tryConnectMQTT() {
    String clientId = "ESP8266Client-";
    clientId += WiFi.macAddress();  // Adiciona o MAC address ao ID do cliente para torná-lo único
    if (client.connect(clientId.c_str())) {
        Serial.println("Conectado ao MQTT!");
        return true;
    } else {
        Serial.print("Falha na conexão MQTT, rc=");
        Serial.println(client.state());
        return false;
    }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  if (!client.connected()) {
      tryConnectMQTT();
  }
}

void loop() {
  if (!client.connected()) {
    Serial.println("Tentando reconectar ao MQTT...");
    tryConnectMQTT();
    delay(5000);  // Aguarda 5 segundos antes de tentar novamente
  }
  client.loop();

  if (Serial.available() > 0) {
    String received = Serial.readStringUntil('\n');
    Serial.print("Recebido do Arduino: ");
    Serial.println(received);

    if (received.startsWith("ENTRADA:")) {
      Serial.println("ESP8266: Alerta de ENTRADA recebido e confirmado.");
      bool isPublished = client.publish(mqtt_topic, "ENTRADA de veiculo!");
      
      if (isPublished) {
        Serial.println("Mensagem publicada com sucesso!");
      } else {
        Serial.println("Falha ao publicar a mensagem.");
      }
    } else if(received.startsWith("SAIDA:")){
      Serial.println("ESP8266: Alerta de SAIDA recebido e confirmado.");
      bool isPublished = client.publish(mqtt_topic, "SAIDA de veiculo!");
      
      if (isPublished) {
        Serial.println("Mensagem publicada com sucesso!");
      } else {
        Serial.println("Falha ao publicar a mensagem.");
      }
    }
  }

  delay(100);
}
