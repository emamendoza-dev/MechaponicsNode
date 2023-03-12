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

// PINOUT-CONFIG ACTUATORS AND SENSORS NODE1

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

// SENSOR LEVEL SA PINTOUT AND CONSTANTS

#define SENSOR_LEVEL_SA 36

// SENSOR LEVEL SB PINTOUT AND CONSTANTS

#define SENSOR_LEVEL_SB 39

// SENSOR LEVEL SNM PINTOUT AND CONSTANTS

#define SENSOR_LEVEL_SNM 34

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

#define PATH_SD_PROFILE_SN "/profile/node1_profile.txt"
#define PATH_SD_DATALOG_SN "/datalog/node1_datalog.txt"

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