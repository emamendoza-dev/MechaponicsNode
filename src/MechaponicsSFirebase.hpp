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
  Serial.println("  ACTUALIZAR EL ESTADO DE SISTEMA CC ");
  // Sensor Temperature
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable1", dBaseVarCC.dbNode2Temp))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Sensor Humidity
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable2", dBaseVarCC.dbNode2Hum))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Luminosity
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable3", dBaseVarCC.dbNode2Lum))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
  // Irrigation
  if (Firebase.setFloat(firebaseData, pathS + pathN + "/Variable4", dBaseVarCC.dbNode2Irri))
  {
    InformacionSet();
  }
  else
  {
    MostrarError();
  }
}

void readStateMechaSystem()
{
  Serial.println("------------------------------------");
  Serial.println("  LEER EL ESTADO DEL SISTEMA ");

  if (Firebase.getInt(firebaseData, pathS + pathStateMechaSystem + "/Modo"))
  {
    modeOperatingSystem = firebaseData.to<int>();
    InformacionGet();
  }
  else
  {
    MostrarError();
    modeOperatingSystem = 0;
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

  if (Firebase.getFloat(firebaseData, pathS + pathPerfilMechaSystem + "/Temp"))
  {
    cProfileCC.valTemProfileCC = firebaseData.to<float>();
    InformacionGet();
  }
  else
  {
    MostrarError();
    cProfileCC.valTemProfileCC = 18.0;
  }
  if (Firebase.getInt(firebaseData, pathS + pathPerfilMechaSystem + "/Hum"))
  {
    cProfileCC.valHumProfileCC = firebaseData.to<int>();
    InformacionGet();
  }
  else
  {
    MostrarError();
    cProfileCC.valHumProfileCC = 40;
  }
  if (Firebase.getInt(firebaseData, pathS + pathPerfilMechaSystem + "/Lum"))
  {
    cProfileCC.valLumProfileCC = map(firebaseData.to<int>(), 0, 100, 0, 255);
    InformacionGet();
  }
  else
  {
    MostrarError();
    cProfileCC.valLumProfileCC = 100;
  }
  // Create configuration file
  Serial.println(F("Saving configuration..."));
  saveConfiguration(PATH_SD_PROFILE_CC, cProfileCC);
}