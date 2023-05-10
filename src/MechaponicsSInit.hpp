#include "MechaponicsSConfig.hpp"
#include "MechaponicsSTime.hpp"
#include "MechaponicsSCultivate.hpp"
#include "MechaponicsSSPIFFS.hpp"
#include "MechaponicsSWiFiManager.hpp"
#include "MechaponicsSFirebase.hpp"
#include "MechaponicsSUART.hpp"
#include "MechaponicsSOLED.hpp"
#include "MechaponicsSModeDemonstrative.hpp"
// #include "MechaponicsSMicroSD.hpp"

Scheduler firebaseSchedulerState;

Task TaskFirebaseState(TASK_HOUR * 1, TASK_FOREVER, &readStateMechaSystem);
Task TaskFirebaseStateNodes(TASK_HOUR * 1, TASK_FOREVER, &readStateNodesMechaSystem);
Task TaskFirebasePerfil(TASK_HOUR * 1, TASK_FOREVER, &readPerfilMechaSystem);
Task TaskOLEDParameters(TASK_MINUTE * 10, TASK_FOREVER, &showParametersOLED);
Task TaskWriteDBNodeSN(TASK_MINUTE * 10, TASK_FOREVER, &writeFirebaseBD);

void initMechaponicsSystem()
{
    Serial.begin(115200);
    initOLED();
    initSerialPortUART();
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
        firebaseSchedulerState.addTask(TaskFirebasePerfil);
        firebaseSchedulerState.addTask(TaskOLEDParameters);
        firebaseSchedulerState.addTask(TaskFirebaseStateNodes);
        firebaseSchedulerState.addTask(TaskWriteDBNodeSN);

        TaskFirebaseState.enable();
        TaskFirebasePerfil.enable();
        TaskOLEDParameters.enable();
        TaskFirebaseStateNodes.enable();
        TaskWriteDBNodeSN.enable();
    }
    else
    {
        // Conexión con el punto de acceso
        connectWiFiServer();
    }
}