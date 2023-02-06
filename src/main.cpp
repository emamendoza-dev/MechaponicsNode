#include <Arduino.h>

#include <WiFi.h>
#include "MechaponicsSSPIFFS.h"
#include "MechaponicsSWiFiManager.h"
#include "MechaponicsSFirebase.h"
#include "MechaponicsSUART.h"

//--------------------------------Pines

// GPIO LED
const int ledWiFiPin = 2;
const int ejemploOPS;

// Serial2 pins of ESP32
#define RXD2 16
#define TXD2 17

//--------------------------------Configuracion en el setup
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

  initSPIFFS();

  // GPIO 2 como OUTPUT
  pinMode(ledWiFiPin, OUTPUT);
  digitalWrite(ledWiFiPin, LOW);

  // Cargando valores guardados en SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  Serial.println(ssid);
  Serial.println(pass);

  // Verificando conexión a la red o establecimiento del AP
  if (initWiFi()) {
    // Encendiendo led para mostrar conexión WiFi establecida
    digitalWrite(ledWiFiPin, HIGH);
    Serial.println("Conectado a la red");

    //---------------------------------Firebase
    // Conectando a Firebase
    connectFirebaseBD();

    int NumAleatorio = 0;
    float ValorMedidoSensor = 0;

    //------------------Actualización dentro de MechaponicsSystem------------------------
    // Sensor de pH
    NumAleatorio = random(4, 6);
    n1pH = NumAleatorio + 0.4;
    // Sensor de CE
    NumAleatorio = random(1, 4);
    n1CE = NumAleatorio * 0.32;
    // Sensor de Temperatura
    NumAleatorio = random(14, 24);
    n1Temp = NumAleatorio + 0.5;
    // Sensor de Nivel Tanque SN
    NumAleatorio = random(10, 100);
    n1NT = NumAleatorio;
    // Sensor de Nivel SN Madre
    NumAleatorio = random(10, 100);
    n1NSN = NumAleatorio;
    // Sensor de Nivel Acido
    NumAleatorio = random(10, 100);
    n1NAcd = NumAleatorio;
    // Sensor de Nivel Base
    NumAleatorio = random(10, 100);
    n1NBas = NumAleatorio;
    // Sensor de Nivel Agua
    NumAleatorio = random(10, 100);
    n1NAg = NumAleatorio;
    // Escritura de datos
    writeFirebaseBD();

    //-------------Lectura de datos dentro de MechaponicsSystem--------------
    // Lectura de datos
    readFirebaseBD();
  }
  else {
    // Conexión con el punto de acceso
    connectWiFiServer();
  }
}

//--------------------------------Configuracion en el loop
void loop() {
  // Envío de datos en formato JSON por el puerto serie
  writeUART();
  delay(5000);
   // Comunicación UART para envío de datos del Nodo 1
  //initUART();
  //readUART();
}