#include <Arduino.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <FirebaseESP32.h>
#include <ArduinoJson.h>
#include "FS.h"
#include "SD.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <OneWire.h> 
#include <TaskScheduler.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

// *** GROWING SYSTEM VALUES ***

// DHT21 SENSOR
#define DHT_SENSOR_PIN 33 // Cualquier pin digital
#define DHT_TYPE DHT21 // Definimos el modelo del sensor

DHT dhtSensor(DHT_SENSOR_PIN, DHT_TYPE); // Instancia del objeto sensor 

// LED STRIP
#define PIN_STRIP_LED 26 // Analógica
//#define PERIOD_ON 57600000 // 16 horas
//#define PERIOD_OFF 28800000 // 8 horas
#define PERIOD_ON 60000 // 
#define PERIOD_OFF 30000 // 

// FAN
#define PIN_FAN 0 // Analógica 
#define FAN_VALUE 50 // En 45 se empieza a mover

// GetTime
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC -21600
#define DAYLIGHT_OFFSET_SEC 0

unsigned long timeNow = 0;
bool activeLighting = true;
int velocityFan = FAN_VALUE;

// WiFi PINOUT AND CONSTANTS

// GPIO LED INDICATOR FOR WiFi

#define INDICATOR_WIFI 2

// GPIO UART PORT INIT

#define PERIPHERAL_ESP8266_RXD1 16
#define PERIPHERAL_ESP8266_TXD1 17

// ASYNCWEBSERVER OBJECT ON PORT 80

AsyncWebServer server(80);

// PARAMETER IN HTTP POST REQUEST

const char *PARAM_INPUT_1 = "ssid";
const char *PARAM_INPUT_2 = "pass";

// FILE PATHS TO SAVE INPUT VALUES PERMANENTLY

const char *ssidPath = "/ssid.txt";
const char *passPath = "/pass.txt";

// VARIABLES TO STORE HTML FORM VALUES

String ssid;
String pass;

// VARIABLES OF TIME WIFI FUNCTION

unsigned long previousMillis = 0;
const long interval = 10000;

// PROJECT DEFINITIONS IN FIREBASE AND THE AUTHENTICATION TOKEN AS A KEY

#define FIREBASE_HOST "mechaponicssystem-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "ri9eXeF41NCanBQ4EsqQc097AOrUaYFQWYurJJvu"

// FIREBASE TYPE OBJECT

FirebaseData firebaseData;

// FIREBASE TREE PATHS

String pathS = "/MechaponicsSystem";
String pathStateMechaSystem = "/Estado";
String pathPerfilMechaSystem = "/Perfil";
String pathN = "/Nodo2";
//String pathN = "/Nodo3";
String pathNodes = "/Nodos";

// MICRO SD PATHS 

#define PATH_SD_PROFILE_CC "/profile/node2_profile.txt"
#define PATH_SD_DATALOG_CC "/datalog/node2_datalog.txt"

//#define PATH_SD_PROFILE_CC "/profile/node3_profile.txt"
//#define PATH_SD_DATALOG_CC "/datalog/node3_datalog.txt"

// OPERATING MODE VARIABLES

#define MODE_AUTOMATIC_VALUE 0
#define MODE_DEMOSTRATIVE_VALUE 1

int modeOperatingSystem = 0;

// STRUCT PROFILE MODE DEMONSTRATIVE

struct ConfigProfileDemonostrative {
 bool dispensers;
 bool measures;
 bool solution;
};

ConfigProfileDemonostrative cProfileDemonostrative;

// VARIABLES OLED DISPLAY

#define OLED_WIDTH 128
#define OLED_HIGH 32
const uint8_t OLED_ADDRESS = 0X3C;
const int8_t OLED_RESET = -1;

// STRUCT DATABASE VARIABLES SN

struct DataBaseVariablesCC {
 float dbNode2Temp;
 int dbNode2Hum;
 int dbNode2Lum;
 int dbNode2Irri;
};

DataBaseVariablesCC dBaseVarCC;

// STRUCT CONFIGURATION PROFILE CC

struct ConfigProfileCC {
 float valTemProfileCC;
 int valHumProfileCC;
 int valLumProfileCC;
};

ConfigProfileCC cProfileCC;

// VARIABLE FOR ACTIVE NODES MECHA SYSTEM

int activeNodes;

// Variables a transmitir vía UART
int board = 2;
String message = "";
bool messageReady = false;