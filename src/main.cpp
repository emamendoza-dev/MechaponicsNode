#include "MechaponicsSInit.hpp"

void setup()
{
  initMechaponicsSystem();

  connectionWiFiOrServer();
}

void loop()
{
  firebaseSchedulerState.execute();
  switch (modeOperatingSystem)
  {
  case 0:
    Serial.println("Modo de operación automatico");

    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_SN, cProfileSN);

    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(PATH_SD_PROFILE_SN);

    Serial.println(cProfileSN.valpHUp);
    Serial.println(cProfileSN.valpHDown);
    Serial.println(cProfileSN.valECUp);
    Serial.println(cProfileSN.valECDown);

    showParametersOLED();

    delay(1000);
    break;
  case 1:
    Serial.println("Modo de operación demostrativo");
    delay(1000);
    break;
  default:
    Serial.println("Modo de operación desconocido");
    delay(1000);
    break;
  }
}