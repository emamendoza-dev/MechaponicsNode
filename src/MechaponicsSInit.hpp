#include "MechaponicsSConfig.hpp"
#include "MechaponicsSTime.hpp"
#include "MechaponicsSPrepareSN.hpp"
#include "MechaponicsSSPIFFS.hpp"
#include "MechaponicsSWiFiManager.hpp"
#include "MechaponicsSFirebase.hpp"
#include "MechaponicsSUART.hpp"
#include "MechaponicsSOLED.hpp"
#include "MechaponicsSModeDemonstrative.hpp"
// #include "MechaponicsSMicroSD.hpp"

Scheduler firebaseSchedulerState;

Task TaskFirebaseState(10000, TASK_FOREVER, &readStateMechaSystem);
Task TaskFirebasePerfil(15000, TASK_FOREVER, &readPerfilMechaSystem);
Task TaskOLEDParameters(20000, TASK_FOREVER, &showParametersOLED);

void initMechaponicsSystem()
{
    Serial.begin(115200);
    initOLED();
    initSerialPortUART();
    initSPIFFS();
    initWiFiIndicator();
    initPrepareSN();
}

void connectionWiFiOrServer()
{
    // Cargando valores guardados en SPIFFS
    ssid = readFile(SPIFFS, ssidPath);
    pass = readFile(SPIFFS, passPath);
    Serial.println(ssid);
    Serial.println(pass);

    // Verificando conexión a la red o establecimiento del AP
    if (initWiFi())
    {
        // Encendiendo led para mostrar conexión WiFi establecida
        digitalWrite(INDICATOR_WIFI, HIGH);
        Serial.println("Conectado a la red");

        //---------------------------------Firebase
        // Conectando a Firebase
        connectFirebaseBD();

        // readFirebaseBD();
        readStateMechaSystem();

        firebaseSchedulerState.addTask(TaskFirebaseState);
        firebaseSchedulerState.addTask(TaskFirebasePerfil);
        firebaseSchedulerState.addTask(TaskOLEDParameters);


        TaskFirebaseState.enable();
        TaskFirebasePerfil.enable();
        TaskOLEDParameters.enable();

        initPrepareSN();
    }
    else
    {
        // Conexión con el punto de acceso
        connectWiFiServer();
    }
    
}