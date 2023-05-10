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
    /*
    Serial.println("Modo de operación demostrativo");
    readTestingModeDemonstrative();
    if (cProfileDemonostrative.dispensers)
    {
      Serial.println("Activando dosificadores");
    }
    if (cProfileDemonostrative.measures)
    {
      dBaseVarSN.dbNode1Temp = measureSNTemperature();
      dBaseVarSN.dbNode1EC = measureLevelCEAveraged(temperatureSNCentigrade);
      dBaseVarSN.dbNode1pH = measureAveragedPHLevel();
      Serial.print("Temp (°C): ");
      Serial.println(dBaseVarSN.dbNode1Temp);
      Serial.print("pH: ");
      Serial.println(dBaseVarSN.dbNode1pH);
      Serial.print("CE (uS/cm): ");
      Serial.println(dBaseVarSN.dbNode1EC);

      writeFirebaseBD();
    }
    delayWithMillisMecha(1000);
    */
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