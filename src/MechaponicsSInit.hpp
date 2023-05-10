#include "MechaponicsSConfig.hpp"
#include "MechaponicsSTime.hpp"
#include "MechaponicsSPrepareSN.hpp"
#include "MechaponicsSSPIFFS.hpp"
#include "MechaponicsSWiFiManager.hpp"
#include "MechaponicsSFirebase.hpp"
#include "MechaponicsSUART.hpp"
#include "MechaponicsSOLED.hpp"
#include "MechaponicsSModeDemonstrative.hpp"
#include "MechaponicsSCultivate.hpp"

// #include "MechaponicsSMicroSD.hpp"

Scheduler firebaseSchedulerState;

Task TaskFirebaseState(TASK_HOUR * 1, TASK_FOREVER, &readStateMechaSystem);

void initMechaponicsSystem()
{
    Serial.begin(115200);
    //initOLED();
    //initSerialPortUART();
    initSPIFFS();
    initWiFiIndicator();
    initCultivate();
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

        readStateMechaSystem();

        firebaseSchedulerState.addTask(TaskFirebaseState);


        TaskFirebaseState.enable();
    }
    else
    {
        // Conexión con el punto de acceso
        connectWiFiServer();
    }
    
}