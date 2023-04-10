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
}