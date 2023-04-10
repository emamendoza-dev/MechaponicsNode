void loadConfiguration(const char *filename, ConfigProfileSN &cProfileSN)
{
  File file = SD.open(filename);

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  cProfileSN.valpHProfileSN = doc["valpHProfileSN"];
  cProfileSN.valECProfileSN = doc["valECProfileSN"];

  file.close();
}

void saveConfiguration(const char *filename, const ConfigProfileSN &cProfileSN)
{
  SD.remove(filename);

  File file = SD.open(filename, FILE_WRITE);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<100> doc;

  doc["valpHProfileSN"] = cProfileSN.valpHProfileSN;
  doc["valECProfileSN"] = cProfileSN.valECProfileSN;

  if (serializeJson(doc, file) == 0)
  {
    Serial.println(F("Failed to write to file"));
  }

  file.close();
}

void printFile(const char *filename)
{
  File file = SD.open(filename);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }

  while (file.available())
  {
    Serial.print((char)file.read());
  }
  Serial.println();

  file.close();
}

void initLoadProfile()
{
  while (!Serial)
    continue;

  while (!SD.begin())
  {
    Serial.println(F("Failed to initialize SD library"));
    delayWithMillisMecha(1000);
  }
}