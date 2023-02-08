#include "SPIFFS.h"

// Inicializar SPIFFS
void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Se ha producido un error al montar SPIFFS");
  }
  Serial.println("SPIFFS montado con éxito");
}

// Leer archivo de SPIFFS
String readFile(fs::FS &fs, const char * path) {
  Serial.printf("Leyendo archivo: %s\r\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory()) {
    Serial.println("- no se pudo abrir el archivo para leer");
    return String();
  }

  String fileContent;
  while (file.available()) {
    fileContent = file.readStringUntil('\n');
    break;
  }
  return fileContent;
}

// Escribir archivo en SPIFFS
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Escribiendo archivo: %s\r\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("- no se pudo abrir el archivo para escribir");
    return;
  }
  if (file.print(message)) {
    Serial.println("- archivo escrito");
  } else {
    Serial.println("- escritura fallida");
  }
}