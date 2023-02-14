struct StatusParametersSN {
 float valpHSN;
 float valCESN;
 float valTempSN;
 int valLevelSA;
 int valLevelSB;
 int valLevelSNM;
};

StatusParametersSN sParametersSN;

void loadParametersSN(const char *filename, StatusParametersSN &sParametersSN) {
  File file = SD.open(filename);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  sParametersSN.valpHSN = doc["valpHSN"];
  sParametersSN.valCESN = doc["valCESN"];
  sParametersSN.valTempSN = doc["valTempSN"];
  sParametersSN.valLevelSA = doc["valLevelSA"];
  sParametersSN.valLevelSB = doc["valLevelSB"];
  sParametersSN.valLevelSNM = doc["valLevelSNM"];

  file.close();
}

void saveParametersSN(const char *filename, const StatusParametersSN &sParametersSN) {
  SD.remove(filename);

  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<100> doc;

  doc["valpHSN"] = sParametersSN.valpHSN;
  doc["valCESN"] = sParametersSN.valCESN;
  doc["valTempSN"] = sParametersSN.valTempSN;
  doc["valLevelSA"] = sParametersSN.valLevelSA;
  doc["valLevelSB"] = sParametersSN.valLevelSB;
  doc["valLevelSNM"] = sParametersSN.valLevelSNM;

  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void printFile(const char *filename) {
  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }
  
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  file.close();
}