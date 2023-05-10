void loadConfiguration(const char *filename, ConfigProfileCC &cProfileCC)
{
  File file = SD.open(filename);

  StaticJsonDocument<512> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  cProfileCC.valTemProfileCC = doc["valTemProfileCC"];
  cProfileCC.valHumProfileCC = doc["valHumProfileCC"];
  cProfileCC.valLumProfileCC = doc["valLumProfileCC"];

  file.close();
}

void saveConfiguration(const char *filename, const ConfigProfileCC &cProfileCC)
{
  SD.remove(filename);

  File file = SD.open(filename, FILE_WRITE);
  if (!file)
  {
    Serial.println(F("Failed to create file"));
    return;
  }

  StaticJsonDocument<150> doc;

  doc["valTemProfileCC"] = cProfileCC.valTemProfileCC;
  doc["valHumProfileCC"] = cProfileCC.valHumProfileCC;
  doc["valLumProfileCC"] = cProfileCC.valLumProfileCC;

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