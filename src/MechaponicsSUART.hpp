// Inicialización del puerto serie
void initUART()
{
  if (Serial1.available())
  {
    Serial.println("Mensaje recibido");
    message = Serial1.readString();
    messageReady = true;
  }
}

void writeUART()
{
  String json;

  StaticJsonDocument<192> doc;

  doc["board_status"] = board;
  doc["n1pH_status"] = n1pH;
  doc["n1CE_status"] = n1CE;
  doc["n1Temp_status"] = n1Temp;
  doc["n1NT_status"] = n1NT;
  doc["n1NAcd_status"] = n1NAcd;
  doc["n1NBas_status"] = n1NBas;
  doc["n1NAg_status"] = n1NAg;
  doc["n1NSN_status"] = n1NSN;

  serializeJson(doc, json);

  Serial.println(json);
  Serial1.println(json);
}

// Recepción de datos por el puerto serie
void readUART()
{
  if (messageReady)
  {
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, message);
    if (error)
    {
      messageReady = false;
      return;
    }

    if (doc["type"] == "request")
    {
      doc["type"] = "response";
      doc["board_status"] = board;
      doc["n1pH_status"] = n1pH;
      doc["n1CE_status"] = n1CE;
      doc["n1Temp_status"] = n1Temp;
      doc["n1NT_status"] = n1NT;
      doc["n1NAcd_status"] = n1NAcd;
      doc["n1NBas_status"] = n1NBas;
      doc["n1NAg_status"] = n1NAg;
      doc["n1NSN_status"] = n1NSN;
      serializeJson(doc, Serial);
      serializeJson(doc, Serial1);
    }
    messageReady = false;
  }
}

void initSerialPortUART(){
  Serial1.begin(115200, SERIAL_8N1, PERIPHERAL_ESP8266_RXD1, PERIPHERAL_ESP8266_TXD1);
}