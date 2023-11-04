# Projeto MQTT com ESP8266 e Sensor de Distância Arduino

Este repositório contém um projeto que utiliza o ESP8266 e o Arduino para detectar a presença de veículos usando sensores de distância e publicar alertas através do MQTT.

## Requisitos

- Placa ESP8266.
- Placa Arduino.
- Sensores de distância compatíveis (usados no código: 2 sensores).
- IDE Arduino com as bibliotecas ESP8266, PubSubClient, NewPing e SoftwareSerial instaladas.
- Um broker MQTT para testes (neste projeto, utilizamos `test.mosquitto.org` e `broker.hivemq.com`).

## Configuração

### Configuração do ESP8266:

1. Clone este repositório para sua máquina local.
2. Abra o arquivo do projeto ESP8266 (`.ino`) na IDE Arduino.
3. Instale as bibliotecas necessárias através do Gerenciador de Bibliotecas da IDE Arduino.
4. Atualize as configurações de WiFi (`ssid` e `password`) com suas próprias credenciais.
5. Se desejar usar outro broker MQTT, atualize a variável `mqtt_server` com o endereço apropriado.

### Configuração do Arduino:

1. Conecte os sensores de distância nos pinos definidos no código (TRIGGER_PIN1, ECHO_PIN1, TRIGGER_PIN2, ECHO_PIN2).
2. Conecte a comunicação serial entre o Arduino e o ESP8266 nos pinos definidos (ESP_RX, ESP_TX).
3. Abra o arquivo do projeto Arduino (`.ino`) na IDE Arduino.
4. Faça o upload do sketch para a placa Arduino.

## Execução

### ESP8266:

1. Conecte seu ESP8266 ao computador.
2. Selecione a placa e a porta corretas na IDE Arduino.
3. Faça upload do sketch para o ESP8266.
4. Abra o Monitor Serial para visualizar as mensagens de log e diagnosticar a conexão.
5. Use um cliente MQTT para se inscrever no tópico `esp8266/alerta` e ouvir as mensagens publicadas pelo ESP8266.

### Arduino:

1. Conecte seu Arduino ao computador.
2. Selecione a placa e a porta corretas na IDE Arduino.
3. Faça upload do sketch para o Arduino.
4. Abra o Monitor Serial para visualizar as mensagens de log e os alertas gerados pelos sensores de distância.

## Diagnóstico

Se você encontrar problemas ao tentar publicar mensagens:

- Certifique-se de que seu ESP8266 está conectado à rede WiFi.
- Verifique se o broker MQTT que você está usando está online e acessível.
- Se estiver usando `test.mosquitto.org`, tente mudar para `broker.hivemq.com` ou outro broker de sua preferência.

## Contribuições

Contribuições são bem-vindas! Se você encontrar um bug ou tiver uma sugestão de melhoria, sinta-se à vontade para abrir uma issue ou enviar um pull request.
