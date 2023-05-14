#include "MechaponicsSConfig.hpp"
#include "MechaponicsSTime.hpp"
#include "MechaponicsSTask.hpp"
#include "MechaponicsSPrepareSN.hpp"
#include "MechaponicsSSPIFFS.hpp"
#include "MechaponicsSWiFiManager.hpp"
#include "MechaponicsSFirebase.hpp"
#include "MechaponicsSUART.hpp"
#include "MechaponicsSOLED.hpp"
#include "MechaponicsSModeDemonstrative.hpp"
// #include "MechaponicsSMicroSD.hpp"

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

        readStateMechaSystem();

        enableMechaSystemTask();
    }
    else
    {
        // Conexión con el punto de acceso
        connectWiFiServer();
    }
}

void loadProfileMechaSystem()
{
    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_SN, cProfileSN);

    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(PATH_SD_PROFILE_SN);

    Serial.println(cProfileSN.valpHProfileSN);
    Serial.println(cProfileSN.valECProfileSN);
}