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
    Serial.println("Modo de operación automatico");
    
    loadProfileMechaSystem();

    prepareSN();

    while(isLowSNLevel())
        fillTankSN();

    readNode1VariablesSN();

    break;
  case MODE_DEMOSTRATIVE_VALUE:
    Serial.println("Modo de operación demostrativo");
    readTestingModeDemonstrative();
    if (cProfileDemonostrative.dispensers)
    {
      modeDemonstrativeDispensers();
    }
    if (cProfileDemonostrative.measures)
    {
      modeDemonstrativeMeasures();
    }
    if (cProfileDemonostrative.solution)
    {
      prepareSN();
    }
    if (cProfileDemonostrative.irrigation)
    {
      irrigateSN();
    }
    delayWithMillisMecha(1000);
    break;
  default:
    Serial.println("Modo de operación desconocido");
    delayWithMillisMecha(1000);
    break;
  }
}