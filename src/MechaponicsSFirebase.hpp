void printResult(FirebaseData &data)
{
  if (data.dataType() == "int")
    Serial.println(data.intData());
  else if (data.dataType() == "float")
    Serial.println(data.floatData(), 5);
  else if (data.dataType() == "double")
    printf("%.9lf\n", data.doubleData());
  else if (data.dataType() == "boolean")
    Serial.println(data.boolData() == 1 ? "true" : "false");
  else if (data.dataType() == "string")
    Serial.println(data.stringData());
}

void InformacionGet(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println();
}

void InformacionSet(void)
{
  Serial.println("Aprobado");
  Serial.println("Ruta: " + firebaseData.dataPath());
  Serial.println("Tipo: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.print("Valor: ");
  printResult(firebaseData);
  Serial.println("------------------------------------");
  Serial.println();
}

void MostrarError(void)
{
  Serial.println("ERROR");
  Serial.println("RAZON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}

// Conectando a Firebase
void connectFirebaseBD()
{
  // Conectando con Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Reconectando WiFi
  Firebase.reconnectWiFi(true);

  // Tiempo de espera de lectura de la base de datos en 1 minuto (máximo 15 minutos)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);

  // Tamaño y  tiempo de espera de escritura
  // Tiny tiempo en ls
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

// Escribir datos en la base de datos en Firebase
void writeFirebaseBD()
{
  Serial.println("------------------------------------");
  Serial.println("  ACTUALIZAR EL ESTADO DE SISTEMA SN ");
  // Sensor de pH
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable1", n1pH))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de CE
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable2", n1CE))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de CE
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable3", n1Temp))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de Nivel Tanque SN
  if (Firebase.setInt(firebaseData, pathS + pathN + "/Variable4", n1NT))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de Nivel SN Madre
  if (Firebase.setInt(firebaseData, pathS + pathN + "/Variable8", n1NSN))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de Nivel Acido
  if (Firebase.setInt(firebaseData, pathS + pathN + "/Variable5", n1NAcd))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de Nivel Base
  if (Firebase.setInt(firebaseData, pathS + pathN + "/Variable6", n1NBas))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor de Nivel Agua
  if (Firebase.setInt(firebaseData, pathS + pathN + "/Variable7", n1NAg))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
}

// Leyendo datos de la base de datos en FIrebase
void readFirebaseBD()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER EL ESTADO DEL NODO 1 ");
  if (Firebase.getFloat(firebaseData, pathS + pathN + "/Variable1"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathN + "/Variable2"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathN + "/Variable3"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathN + "/Variable4"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathN + "/Variable8"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathN + "/Variable5"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathN + "/Variable6"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathN + "/Variable7"))
  {
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
}

void readStateMechaSystem(){
  Serial.println("------------------------------------");
  Serial.println("  LEER EL ESTADO DEL SISTEMA ");

  if (Firebase.getInt(firebaseData, pathS + pathStateMechaSystem + "/Modo"))
  {
    modeOperatingSystem = firebaseData.to<int>();
    //Serial.println(modeOperatingSystem);
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
}

void readPerfilMechaSystem(){
  Serial.println("------------------------------------");
  Serial.println("  LEER EL PERFIL DEL SISTEMA ");

  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/pH"))
  {
    cProfileSN.valpHDown = firebaseData.to<float>() - 0.1;
    cProfileSN.valpHUp = firebaseData.to<float>() + 0.1;
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/CE"))
  {
    cProfileSN.valECDown = firebaseData.to<float>() - 0.1;
    cProfileSN.valECUp = firebaseData.to<float>() + 0.1;
    InformacionGet();
  }
  else
  {
    MostrarError();
  }

  // Create configuration file
    Serial.println(F("Saving configuration..."));
    saveConfiguration(PATH_SD_PROFILE_SN, cProfileSN); 
}