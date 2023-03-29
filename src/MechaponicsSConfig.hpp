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
#include <ph_grav.h>
#include <OneWire.h>                
#include <DallasTemperature.h>
#include <TaskScheduler.h>

// PINOUT-CONFIG ACTUATORS AND SENSORS NODE1

// CE SENSOR PINOUT AND GLOBAL VARIABLES

#define SENSOR_CE_RX 9
#define SENSOR_CE_TX 10
String answerSensorCE = "";
boolean answerSensorCEComplete = false;

// PH SENSOR PINOUT AND GLOBAL INSTANCE

#define SENSOR_PH_ANALOGIC_INPUT 33
Gravity_pH pHSensor = Gravity_pH(SENSOR_PH_ANALOGIC_INPUT);

// TEMPERATURE SENSOR PINOUT AND OBJECTS

#define SENSOR_TEMPERATURE_SN_PIN 15 
OneWire ourWireTemperatureSensor(SENSOR_TEMPERATURE_SN_PIN); 
DallasTemperature temperatureSensor(&ourWireTemperatureSensor);

// ULTRASONIC SENSOR PINOUT AND CONSTANS

#define SENSOR_LEVEL_SN_TRIG 32
#define SENSOR_LEVEL_SN_ECHO 35

#define LEVEL_TANK_SN_OFFSET 2
#define LEVEL_TANK_SN_MIN 40
#define LEVEL_TANK_SN_FULL 95
#define LEVEL_TANK_SN_MAX 13

// STRUCT SENSOR LEVEL SN

struct sensorLevelSN {
  long timeDelayEcho;
  long distanceEquivalent;
  int levelPercentageTank;
};

// SETTING PWM PROPERTIES

#define PWM_FRECUENCY_ACTUATOR 30000
#define PWM_RESOLUTION_ACTUATOR 8

// PUMP WATER PINOUT AND CONSTANTS

#define ACTUATOR_FILL_TANK 26
#define ACTUATOR_DUTY_CYLCE_WATER 200
#define PWM_CHANNEL_WATER 0

// PUMP SA PINOUT AND CONSTANTS

#define ACTUATOR_PUMP_SA 13
#define PWM_SPEED_BUFFER_SA 150
#define TIME_ACTIVATION_PUMP_SA 2000
#define PWM_CHANNEL_SA 1

// PUMP SB PINOUT AND CONSTANTS

#define ACTUATOR_PUMP_SB 12
#define PWM_SPEED_BUFFER_SB 150
#define TIME_ACTIVATION_PUMP_SB 2000
#define PWM_CHANNEL_SB 2

// PUMP SNM PINOUT AND CONSTANTS

#define ACTUATOR_PUMP_SNM 27
#define PWM_SPEED_BUFFER_SNM 150
#define TIME_ACTIVATION_PUMP_SNM 2000
#define PWM_CHANNEL_SNM 3

// MOTOR RIGH PINOUT AND CONSTANTS

#define ACTUATOR_MOTOR_R 14
#define PWM_SPEED_MOTOR_R 100
#define TIME_ACTIVATION_MOTOR_R 2000
#define PWM_CHANNEL_MOTOR_R 4

// MOTOR LEFT PINOUT AND CONSTANTS

#define ACTUATOR_MOTOR_L 25
#define PWM_SPEED_MOTOR_L 100
#define TIME_ACTIVATION_MOTOR_L 2000
#define PWM_CHANNEL_MOTOR_L 5

// STRUCT PUMP AND MOTOR

struct actuatorPumpMotor {
  const int frecuencyPWM;
  const int channelPWM;
  const int resolutionPWM;
  int dutyCyclePWM;
};

// SENSOR LEVEL SA PINOUT AND CONSTANTS

#define SENSOR_LEVEL_SA 36

// SENSOR LEVEL SB PINOUT AND CONSTANTS

#define SENSOR_LEVEL_SB 39

// SENSOR LEVEL SNM PINOUT AND CONSTANTS

#define SENSOR_LEVEL_SNM 34

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
String pathN = "/Nodo1";

// MICRO SD PATHS 

#define PATH_SD_PROFILE_SN "/profile/node1_profile.txt"
#define PATH_SD_DATALOG_SN "/datalog/node1_datalog.txt"

// STRUCT CONFIGURATION PROFILE SN

struct ConfigProfileSN {
 float valpHUp;
 float valpHDown;
 float valECUp;
 float valECDown;
};

ConfigProfileSN cProfileSN;

// OPERATING MODE VARIABLES

#define MODE_AUTOMATIC_VALUE 0
#define MODE_DEMOSTRATIVE_VALUE 1

int modeOperatingSystem = 2;

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