#include <Arduino.h>
#include <WiFi.h>

void setup() {
  //comunicacao serial definida no platformio.ini
  Serial.begin(115200);
  
  //truque do esp32 s3 que aprendi num video do YT: sempre coloque um delay no início 
  //pra dar tempo do seu PC (Linux) montar a porta /dev/ttyACM0 antes do chip comecar a enviar os logs do processo de boot.
  //sem esse delay os logs são perdidos!
  delay(3000); 
  //formato padrao de logs: [timestamp] [modulo] mensagem
  Serial.printf("[%lu] [SYSTEM] Initializing ESP32-S3 Core...\n", millis());
  Serial.printf("[%lu] [SYSTEM] Free Heap: %u bytes\n", millis(), ESP.getFreeHeap());
  Serial.printf("[%lu] [SYSTEM] Setup complete.\n", millis());

  //definindo o esp como acess point
  WiFi.mode(WIFI_AP);
  
  //Inicia a rede com nome "ESP32-Scan" e senha "senha123"
  WiFi.softAP("ESP32-Scan", "senha123");
  
  // printando o endereço IP gerado no terminal pra poder acessar depois
  Serial.printf("[%lu] [WIFI] Access Point Inicializado.\n", millis());
  Serial.printf("[%lu] [WIFI] IP de controle: %s\n", millis(), WiFi.softAPIP().toString().c_str());
}

void loop() {
  //imprime o estado da memoria a cada 5 segundos para sabermos que ele nao travou (útil para detectar vazamentos futuros)
  Serial.printf("[%lu] [SYSTEM] Standby. Free Heap: %u bytes | Clients: %d\n", millis(), ESP.getFreeHeap(), WiFi.softAPgetStationNum());
  delay(5000);
}