// Struct statement for sensor level

sensorLevelSN sLevelSN = {0, 0, 100};

// Function for measure level of tank SN

int measureLevelSN()
{
  // Code for measure level for SN
  digitalWrite(SENSOR_LEVEL_SN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_LEVEL_SN_TRIG, LOW);

  sLevelSN.timeDelayEcho = pulseIn(SENSOR_LEVEL_SN_ECHO, HIGH);
  sLevelSN.distanceEquivalent = sLevelSN.timeDelayEcho / 59;

  int levelPercentageT = ((LEVEL_TANK_SN_MAX - (sLevelSN.distanceEquivalent - LEVEL_TANK_SN_OFFSET)) * 100) / LEVEL_TANK_SN_MAX;

  Serial.println("Nivel real solucion");
  Serial.println(levelPercentageT);

  if ( levelPercentageT < 0 || levelPercentageT > 100 ){
    sLevelSN.levelPercentageTank = 100;
  }else{
    sLevelSN.levelPercentageTank = levelPercentageT;
  }

  return sLevelSN.levelPercentageTank;
}

// Function configuration for sensor level SN

void initSensorLevelSN()
{
  pinMode(SENSOR_LEVEL_SN_TRIG, OUTPUT);
  pinMode(SENSOR_LEVEL_SN_ECHO, INPUT);
  digitalWrite(SENSOR_LEVEL_SN_TRIG, LOW);

  // Baseline SN level measurements
  Serial.println("Tomando lecturas iniciales del nivel de SN");
  for(indexSNSensorSample=0; indexSNSensorSample<SENSOR_LEVEL_MAX_SAMPLES; indexSNSensorSample++){
    levelSNSensorSamples[indexSNSensorSample] = measureLevelSN();
    Serial.print("Nivel de SN: ");
    Serial.println(levelSNSensorSamples[indexSNSensorSample]);
    delayWithMillisMecha(1000);
  }
  indexSNSensorSample = 0;
}