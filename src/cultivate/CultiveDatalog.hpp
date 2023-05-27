void saveDatalog(const char *filename, const DataBaseVariablesCC &dBaseVarCC)
{
  //SD.remove(filename);

  File file = SD.open(filename, FILE_APPEND);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<200> doc;

  doc["valTemDataLogCC"] = dBaseVarCC.dbNode2Temp;
  doc["valHumDataLogCC"] = dBaseVarCC.dbNode2Hum;
  doc["valLumDataLogCC"] = dBaseVarCC.dbNode2Lum;
  doc["valIrriDataLogCC"] = dBaseVarCC.dbNode2Irri;

  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void saveMechaSystemDatalog()
{
  Serial.println(F("Saving datalog..."));
  
  readNode2VariablesCC();

  saveDatalog(PATH_SD_DATALOG_CC, dBaseVarCC);
}