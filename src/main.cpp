#include <Arduino.h>

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
}

void loop() {
  //imprime o estado da memoria a cada 5 segundos para sabermos que ele nao travou (útil para detectar vazamentos futuros)
  Serial.printf("[%lu] [SYSTEM] Standby. Free Heap: %u bytes\n", millis(), ESP.getFreeHeap());
  delay(5000);
}