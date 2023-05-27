void readTestingModeDemonstrative()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER LAS PRUEBAS DEL SISTEMA ");

  if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Humedad"))
  {
    cProfileDemonostrative.humidity = firebaseData.to<bool>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }

  if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Temperatura"))
  {
    cProfileDemonostrative.temperature = firebaseData.to<bool>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }

    if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Mediciones"))
  {
    cProfileDemonostrative.measures = firebaseData.to<bool>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  
}

void takeMeasurements(){
  // S3: temperatura, HR 
  readNode2VariablesCC();
  writeFirebaseBD();
  return;
}

void lightning(){
  for(int i=0; i<255; i++){
    turnOnLighting(255-i);
    delayWithMillisMecha(50);
  }
  for(int i=0; i<255; i++){
    turnOnLighting(i);
    delayWithMillisMecha(50);
  }
  return;
}

void ventilation(){
  for(int i=FAN_VALUE; i<255; i++){
    changeVelocityFan(255-i);
    delayWithMillisMecha(50);
  }
  for(int i=FAN_VALUE; i<255; i++){
    changeVelocityFan(i);
    delayWithMillisMecha(50);
  }
  return;
}
