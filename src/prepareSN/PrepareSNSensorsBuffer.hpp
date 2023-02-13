struct sensorsLevelBuffer {
  int flagLevelMinSA;
  int flagLevelMinSB;
  int flagLevelMinSNM;
};

sensorsLevelBuffer sLevelBuffer = {0, 0, 0};

void initSensorsLevelBuffer(){
  pinMode(SENSOR_LEVEL_SA, INPUT);
  pinMode(SENSOR_LEVEL_SB, INPUT);
  pinMode(SENSOR_LEVEL_SNM, INPUT);
}

bool measureLevelContainers(){
  // Code for measure level for solutions buffers
  sLevelBuffer.flagLevelMinSA = digitalRead(SENSOR_LEVEL_SA);
  sLevelBuffer.flagLevelMinSB = digitalRead(SENSOR_LEVEL_SB);
  sLevelBuffer.flagLevelMinSNM = digitalRead(SENSOR_LEVEL_SNM);

  return ((sLevelBuffer.flagLevelMinSA == 1) && (sLevelBuffer.flagLevelMinSB == 1) && (sLevelBuffer.flagLevelMinSNM == 1));
}