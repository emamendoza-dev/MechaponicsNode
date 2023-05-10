#include "MechaponicsSInit.hpp"

unsigned long timeNow = 0;
bool activeLighting = true;
int velocityFan = FAN_VALUE;

void setup()
{
  initMechaponicsSystem();

  connectionWiFiOrServer();
}

void loop()
{
  
  firebaseSchedulerState.execute();
  /*
  Serial.println("Nodos activos");
  Serial.println(activeNodes);
  writeUART();
  */
  switch (modeOperatingSystem)
  {
  case 0:
  {
    Serial.println("Modo de operación automatico");
    /*
    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_SN, cProfileSN);

    // Dump config file
    Serial.println(F("Print config file..."));
    printFile(PATH_SD_PROFILE_SN);

    Serial.println(cProfileSN.valpHProfileSN);
    Serial.println(cProfileSN.valECProfileSN);
    */
    // CULTIVATE CODE
    // Obtener hora
    int hora = getHour();
    int minuto = getMinute();
    Serial.print("La hora es ");
    Serial.println(hora);
    Serial.print("Minuto: ");
    Serial.println(minuto);
    // Iluminar 16 horas
    if(hora >= 22 || hora < 7 ){
    //if((minuto>10 && minuto<15) || (minuto>20 && minuto<25) || (minuto>30 && minuto<35) || (minuto>40 && minuto<45) || (minuto>50 && minuto<55)) {
      turnOffLighting();
      Serial.println("Luz apagada");
    } else {
      turnOnLighting(BRIGHTNESS);
      Serial.println("Luz encendida");
    }
    /*if (millis() > timeNow + PERIOD_ON && activeLighting)
    {
      turnOffLighting();
      activeLighting = false;
      timeNow = millis();
      Serial.println("Luz apagada");
    }
    // Apagar durante 8 horas
    if (millis() > timeNow + PERIOD_OFF && !activeLighting)
    {
      turnOnLighting(BRIGHTNESS);
      activeLighting = true;
      timeNow = millis();
      Serial.println("Luz encendida");
    }*/
    // Medir variables
    float humidityCell = measureHumidityGrowingCell();
    delayWithMillisMecha(1000);
    float temperatureCell = measureTemperatureGrowingCell();
    delayWithMillisMecha(1000);
    Serial.print("HR [%]: ");
    Serial.println(humidityCell);
    Serial.print("Temperatura [°C]: ");
    Serial.println(temperatureCell);
    // Temperatura deseada
    float desiredTemperature = 18; // °C
    Serial.print("Temperatura deseada[°C]: ");
    Serial.println(desiredTemperature);
    // Error
    float temperatureError;
    temperatureError = desiredTemperature - temperatureCell;
    Serial.print("Error en la temperatura [°C]: ");
    Serial.println(temperatureError);
    // Control
    if (temperatureError > 0)
    {
      velocityFan--;
      Serial.print("Velocidad del ventilador reduce a ");
    }
    else if (temperatureError < 0)
    {
      velocityFan++;
      Serial.print("Velocidad del ventilador aumenta a ");
    }
    if (velocityFan < 0)
      velocityFan = 0;
    if (velocityFan > 255)
      velocityFan = 255;
    Serial.println(velocityFan);
    // Actuador
    changeVelocityFan(velocityFan);
    //readNode1VariablesSN();
    break;
  }

  case 1:
  {
    /**/
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
  }

  default:
  {
    Serial.println("Modo de operación desconocido");
    delayWithMillisMecha(1000);
    break;
  }
  }
}