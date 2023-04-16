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

// Write data to database in Firebase
void writeFirebaseBD()
{
  Serial.println("------------------------------------");
  Serial.println("  ACTUALIZAR EL ESTADO DE SISTEMA SN ");
  // Sensor pH
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable1", dBaseVarSN.dbNode1pH))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor EC
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable2", dBaseVarSN.dbNode1EC))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Temp
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable3", dBaseVarSN.dbNode1Temp))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Level SN
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable4", dBaseVarSN.dbNode1LevelSN))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Level SA
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable5", dBaseVarSN.dbNode1LevelSA))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Level SB
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable6", dBaseVarSN.dbNode1LevelSB))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Level SNM
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable8", dBaseVarSN.dbNode1LevelSNM))
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

void readStateNodesMechaSystem()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER EL ESTADO DE LOS NODOS ");

  if (Firebase.getInt(firebaseData, pathS + pathNodes + "/N4"))
  {
    if (firebaseData.to<int>() == 1)
    {
      activeNodes = 4;
    }
    else
    {
      if (Firebase.getInt(firebaseData, pathS + pathNodes + "/N3"))
      {
        if (firebaseData.to<int>() == 1)
        {
          activeNodes = 3;
        }
        else
        {
          if (Firebase.getInt(firebaseData, pathS + pathNodes + "/N2"))
          {
            if (firebaseData.to<int>() == 1)
            {
              activeNodes = 2;
            }
            else
            {
              activeNodes = 1;
            }
            InformacionGet();
          }
          else
          {
            MostrarError();
          }
        }
        InformacionGet();
      }
      else
      {
        MostrarError();
      }
    }
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
}

void readPerfilMechaSystem()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER EL PERFIL DEL SISTEMA ");

  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/pH"))
  {
    cProfileSN.valpHProfileSN = firebaseData.to<float>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/CE"))
  {
    cProfileSN.valECProfileSN = firebaseData.to<float>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/Temp"))
  {
    cProfileCC.valTemProfileCC = firebaseData.to<float>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathPerfilMechaSystem + "/Hum"))
  {
    cProfileCC.valHumProfileCC = firebaseData.to<int>();
    InformacionGet();
  }
  else
  {
    MostrarError();
  }
  if (Firebase.getInt(firebaseData, pathS + pathPerfilMechaSystem + "/Lum"))
  {
    cProfileCC.valLumProfileCC = firebaseData.to<int>();
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