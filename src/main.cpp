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
  case 0:
    Serial.println("Modo de operación automatico");
    
    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_SN, cProfileSN);

    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(PATH_SD_PROFILE_SN);

    Serial.println(cProfileSN.valpHProfileSN);
    Serial.println(cProfileSN.valECProfileSN);

    TaskIrrigationSN.disable();
    prepareSN();
    TaskIrrigationSN.enable();

    while(isLowSNLevel())
        fillTankSN();

    mixer(15000);

    delayWithMillisMecha(5000);

    readNode1VariablesSN();

    break;
  case 1:
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
    break;
  default:
    Serial.println("Modo de operación desconocido");
    delayWithMillisMecha(1000);
    break;
  }
}