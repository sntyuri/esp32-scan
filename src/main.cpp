#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>

// instancia o servidor web na porta 80
AsyncWebServer server(80);

void setup() {
  //comunicacao serial definida no platformio.ini
  Serial.begin(115200);
  
  //delay no início pra máquina montar a porta /dev/ttyACM0 antes do chip comecar a enviar os logs do processo de boot pra não perder os logs
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

  // == servidor web ==
  
  //inicializa o sistema de arquivos (LittleFS)
  if (!LittleFS.begin(true)) {
    Serial.printf("[%lu] [SYSTEM] ERRO: Falha ao montar o LittleFS!\n", millis());
    return;
  }
  Serial.printf("[%lu] [SYSTEM] LittleFS montado com sucesso.\n", millis());

  // cria a rota principal pra entregar o HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.begin();
  Serial.printf("[%lu] [WEB] Servidor HTTP Assíncrono rodando na porta 80.\n", millis());
}

void loop() {
  //imprime o estado da memoria a cada 5 segundos para sabermos que ele nao travou
  Serial.printf("[%lu] [SYSTEM] Standby. Free Heap: %u bytes | Clients: %d\n", millis(), ESP.getFreeHeap(), WiFi.softAPgetStationNum());
  delay(5000);
}