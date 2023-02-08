#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Wire.h>

// Crear objeto AsyncWebServer en el puerto 80
AsyncWebServer server(80);

// Buscar parámetro en la solicitud HTTP POST
const char *PARAM_INPUT_1 = "ssid";
const char *PARAM_INPUT_2 = "pass";

// Rutas de archivo para guardar los valores de entrada de forma permanente
const char *ssidPath = "/ssid.txt";
const char *passPath = "/pass.txt";

// Variables para guardar valores del formulario HTML
String ssid;
String pass;

// Variables de tiempo
unsigned long previousMillis = 0;
const long interval = 10000; // intervalo de espera para conexión Wi-Fi  (milliseconds)

// Definiciones del proyecto en Firebase y el token de autenticacion como llave
#define FIREBASE_HOST "mechaponicssystem-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ri9eXeF41NCanBQ4EsqQc097AOrUaYFQWYurJJvu"

// Objeto de tipo Firebase
FirebaseData firebaseData;

// Nombre del Path principal del proyecto
String pathS = "/MechaponicsSystem";
// Nombre del Path principal del proyecto
String pathN = "/Nodo1";

// Variables a transmitir a la base de datos
float n1pH = 0;
float n1CE = 0;
float n1Temp = 0;
int n1NT = 0;
int n1NSN = 0;
int n1NAcd = 0;
int n1NBas = 0;
int n1NAg = 0;

// Variables a transmitir vía UART
int board = 1;
String message = "";
bool messageReady = false;