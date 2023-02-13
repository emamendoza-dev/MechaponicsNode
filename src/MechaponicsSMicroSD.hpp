String readFile(const char * path) {

  String completeMessage = "";
  char messageReadFile;

  File dataFile = SD.open(path, FILE_READ);

  while (dataFile.available())
  {
    messageReadFile = dataFile.read();
    completeMessage = completeMessage + messageReadFile;
  }
  dataFile.close();
  
  return completeMessage;
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

void initSDFile() {
  if (!SD.begin(5)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
}

String readDataSD(int pathFileRead) {
  String messageReadSD;
  switch (pathFileRead) {
    case 0:
      messageReadSD = readFile(PATH_SD_PROFILE_SN);
      break;
    case 1:
      messageReadSD = readFile(PATH_SD_DATALOG_SN);
      break;
    default:
      messageReadSD = readFile("/error.txt");
      break;
  }

  return messageReadSD;
}

void writeDataSD(int pathFileWrite, const char * messageWriteSD) {
  switch (pathFileWrite) {
    case 0:
      writeFile(SD, PATH_SD_PROFILE_SN, messageWriteSD);
      break;
    case 1:
      writeFile(SD, PATH_SD_DATALOG_SN, messageWriteSD);
      break;
    default:
      writeFile(SD, "/error.txt", messageWriteSD);
      break;
  }
}