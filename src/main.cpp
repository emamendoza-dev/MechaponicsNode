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
    readTestingModeDemonstrative();
    if (cProfileDemonostrative.dispensers)
    {
      dose(0, 3000);
      dose(1, 3000);
      dose(2, 3000);
    }
    if (cProfileDemonostrative.measures)
    {
      // PH, CE, temperature tests
      float CELevelNoCompensation = measureLevelCEAveraged(25.0);
      Serial.print("Nivel de CE sin compensación (uS/cm): ");
      Serial.println(CELevelNoCompensation);

      float temperatureSNCentigrade = measureSNTemperature();
      Serial.print("Temperatura de SN (°C): ");
      Serial.println(temperatureSNCentigrade);

      float CELevel = measureLevelCEAveraged(temperatureSNCentigrade);
      Serial.print("Nivel de CE con compensación (uS/cm): ");
      Serial.println(CELevel);

      float PHLevel = measureAveragedPHLevel();
      Serial.print("Nivel de pH: ");
      Serial.println(PHLevel);
    }
    delay(1000);
    break;
  default:
    Serial.println("Modo de operación desconocido");
    delay(1000);
    break;
  }
}