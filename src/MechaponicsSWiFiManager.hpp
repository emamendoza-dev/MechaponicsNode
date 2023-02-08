#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

// Crear objeto AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// Buscar parámetro en la solicitud HTTP POST
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";

// Rutas de archivo para guardar los valores de entrada de forma permanente
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";

//Variables para guardar valores del formulario HTML
String ssid;
String pass;

// Variables de tiempo
unsigned long previousMillis = 0;
const long interval = 10000;  // intervalo de espera para conexión Wi-Fi  (milliseconds)


// Inicialización WiFi
// Esta funcion inicializa la conexión con la red WiFi con las credenciales que fueron pasadas
bool initWiFi() {
  // Variables para tiempo de respuesta
  unsigned long currentMillis = millis();
  previousMillis = currentMillis;
  
  // Se reconecta
  Serial.println("Reconectando a WiFi...");
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("No se logro reconectar");
  
  // Se configura el modo WiFi como estación
  WiFi.mode(WIFI_STA);

  // Se inicializa la conexión WiFi
  WiFi.begin(ssid.c_str(), pass.c_str());
  Serial.println("Conectando a WiFi...");

  // Verificacion del estado de conexión si no hay conexión manda un error
  while (WiFi.status() != WL_CONNECTED) {
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      Serial.println("Error al conectar.");
      return false;
    }
  }

  // Muestra la IP conectada
  Serial.println(WiFi.localIP());
  return true;
}

void connectWiFiServer() {
  // Conectar a la red Wi-Fi con SSID y contraseña
  // Se notifica al usuario
  Serial.println("Ajustando AP (Access Point)");

  // Se establece el punto de acceso
  WiFi.softAP("MECHA_ESP_SN", "123456789");

  // Se obtiene la dirección IP de la red para mostrar al usuario
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP dirección: ");
  Serial.println(IP);

  // Estableciendo el servidor en el puerto 192.168.4.1
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/wifimanager.html", "text/html");
  });

  // Configurando el servidor para la obtencion de las credenciales de red
  server.serveStatic("/", SPIFFS, "/");

  // Estableciendo el servidor en el puerto por defecto
  server.on("/", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      if (p->isPost()) {
        // HTTP POST ssid valor
        if (p->name() == PARAM_INPUT_1) {
          ssid = p->value().c_str();
          Serial.print("SSID establecida en: ");
          Serial.println(ssid);
          // Escribir archivo para guardar valor
          writeFile(SPIFFS, ssidPath, ssid.c_str());
        }
        // HTTP POST pass valor
        if (p->name() == PARAM_INPUT_2) {
          pass = p->value().c_str();
          Serial.print("Contraseña establecida en: ");
          Serial.println(pass);
          // Escribir archivo para guardar valor
          writeFile(SPIFFS, passPath, pass.c_str());
        }
      }
    }
    request->send(200, "text/plain", "Hecho. ESP se reiniciará y se conectará a su enrutador. " );
    delay(3000);
    ESP.restart();
  });
  server.begin();
}