struct sensorsLevelBuffer
{
  int flagLevelMinSA;
  int flagLevelMinSB;
  int flagLevelMinSNM;
};

sensorsLevelBuffer sLevelBuffer = {0, 0, 0};

void initSensorsLevelBuffer()
{
  pinMode(SENSOR_LEVEL_SA, INPUT);
  pinMode(SENSOR_LEVEL_SB, INPUT);
  pinMode(SENSOR_LEVEL_SNM, INPUT);
}

int conversionLevelContainers(int measureLevel){
  int levelReturn;

  if (measureLevel == 1) levelReturn=80; else levelReturn=20;

  return levelReturn; 
}

bool measureLevelContainers()
{
  // Code for measure level for solutions buffers
  sLevelBuffer.flagLevelMinSA = digitalRead(SENSOR_LEVEL_SA);
  Serial.println("Sensor SA");
  Serial.println(sLevelBuffer.flagLevelMinSA);
  sLevelBuffer.flagLevelMinSB = digitalRead(SENSOR_LEVEL_SB);
  Serial.println("Sensor SB");
  Serial.println(sLevelBuffer.flagLevelMinSB);
  sLevelBuffer.flagLevelMinSNM = digitalRead(SENSOR_LEVEL_SNM);
  Serial.println("Sensor SNM");
  Serial.println(sLevelBuffer.flagLevelMinSNM);

  return ((sLevelBuffer.flagLevelMinSA == 1) && (sLevelBuffer.flagLevelMinSB == 1) && (sLevelBuffer.flagLevelMinSNM == 1));
}