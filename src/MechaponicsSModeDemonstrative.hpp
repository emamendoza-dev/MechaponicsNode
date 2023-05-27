void readTestingModeDemonstrative()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER LAS PRUEBAS DEL SISTEMA ");

  if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Dosificadores"))
  {
    cProfileDemonostrative.dispensers = firebaseData.to<bool>();
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
  if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Solucion"))
  {
    cProfileDemonostrative.solution = firebaseData.to<bool>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathStateMechaSystem + "/Irrigacion"))
  {
    cProfileDemonostrative.irrigation = firebaseData.to<bool>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
}

void modeDemonstrativeDispensers()
{
  mixer(5000);
}

void modeDemonstrativeMeasures()
{
  readNode1VariablesSN();
  writeFirebaseBD();
}