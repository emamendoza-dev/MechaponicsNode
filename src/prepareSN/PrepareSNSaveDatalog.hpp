void saveDatalog(const char *filename, const DataBaseVariablesSN &dBaseVarSN)
{
  File file = SD.open(filename, FILE_APPEND);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<300> doc;

  doc["valpHDataLogCC"] = dBaseVarSN.dbNode1pH;
  doc["valECDataLogCC"] = dBaseVarSN.dbNode1EC;
  doc["valTempDataLogCC"] = dBaseVarSN.dbNode1Temp;
  doc["valLevelSNDataLogCC"] = dBaseVarSN.dbNode1LevelSN;
  doc["valLevelSADataLogCC"] = dBaseVarSN.dbNode1LevelSA;
  doc["valLevelSBDataLogCC"] = dBaseVarSN.dbNode1LevelSB;
  doc["valLevelSNMDataLogCC"] = dBaseVarSN.dbNode1LevelSNM;

  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void saveMechaSystemDatalog()
{
  Serial.println(F("Saving datalog..."));
  
  readNode1VariablesSN();

  saveDatalog(PATH_SD_DATALOG_SN, dBaseVarSN);
  
  printFile(PATH_SD_DATALOG_SN);
}