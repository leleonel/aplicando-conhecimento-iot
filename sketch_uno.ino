#include <NewPing.h>
#include <SoftwareSerial.h>

#define TRIGGER_PIN1  9
#define ECHO_PIN1     10
#define TRIGGER_PIN2  11
#define ECHO_PIN2     12
#define MAX_DISTANCE  200  // Máxima distância a ser medida

#define ESP_RX        2
#define ESP_TX        3

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);
SoftwareSerial espSerial(ESP_RX, ESP_TX); // RX, TX

void setup() {
  Serial.begin(9600);  // Altera a taxa de baud para 9600
  espSerial.begin(9600); // Altera a taxa de baud para 9600
}

void loop() {
  delay(50);

  unsigned int distance1 = sonar1.ping_cm();
  unsigned int distance2 = sonar2.ping_cm();

  Serial.print("Sensor 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Sensor 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Se a distância for menor que 20cm, envia um alerta para o ESP8266
  if (distance1 < 20) {
    espSerial.println("ENTRADA: Entrou um veiculo!");
    Serial.println("Alerta de ENTRADA de veiculo.");
  } else if (distance2 < 20){
    espSerial.println("SAIDA: Saiu um veiculo!");
    Serial.println("Alerta de SAIDA de veiculo.");
  }

  // Lê e imprime todas as mensagens recebidas do ESP8266
  while (espSerial.available()) {
    String messageFromESP = espSerial.readStringUntil('\n');
    Serial.print("Mensagem do ESP8266: ");
    Serial.println(messageFromESP);
  }

  delay(1000);
}
