#include "MechaponicsSInit.hpp"

void setup()
{
  initMechaponicsSystem();

  connectionWiFiOrServer();
}

void loop()
{
  firebaseSchedulerState.execute();
  Serial.println("Nodos activos");
  Serial.println(activeNodes);
  writeUART();
  switch (modeOperatingSystem)
  {
  case MODE_AUTOMATIC_VALUE:
  {
    Serial.println("Modo de operación automatico");
    
    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_CC, cProfileCC);

    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(PATH_SD_PROFILE_CC);

    Serial.println(cProfileCC.valTemProfileCC);
    Serial.println(cProfileCC.valHumProfileCC);
    Serial.println(cProfileCC.valLumProfileCC);

    prepareCC();

    readNode2VariablesCC();
    break;
  }

  case MODE_DEMOSTRATIVE_VALUE:
  {
    Serial.println("Modo de operación demostrativo");

    readTestingModeDemonstrative();

    if(cProfileDemonostrative.measures){takeMeasurements();}

    if(cProfileDemonostrative.humidity){lightning();}

    if(cProfileDemonostrative.temperature){ventilation();}

    break;
  }

  default:
  {
    Serial.println("Modo de operación desconocido");
    delayWithMillisMecha(1000);
    break;
  }
  }
}