struct sensorLevelSN {
  long timeDelayEcho;
  long distanceEquivalent;
  int levelPercentageTank;
};

sensorLevelSN sLevelSN = {0, 0, 100.0};

void initSensorLevelSN() {
  pinMode(SENSOR_LEVEL_SN_TRIG, OUTPUT);
  pinMode(SENSOR_LEVEL_SN_ECHO, INPUT);
  digitalWrite(SENSOR_LEVEL_SN_TRIG, LOW);
}

int measureLevelSN()
{
  // Code for measure level for SN
  digitalWrite(SENSOR_LEVEL_SN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_LEVEL_SN_TRIG, LOW);

  sLevelSN.timeDelayEcho = pulseIn(SENSOR_LEVEL_SN_ECHO, HIGH);
  sLevelSN.distanceEquivalent = sLevelSN.timeDelayEcho / 59;

  sLevelSN.levelPercentageTank = ((LEVEL_TANK_SN_MAX - (sLevelSN.distanceEquivalent - LEVEL_TANK_SN_OFFSET)) * 100 ) / LEVEL_TANK_SN_MAX;

  return sLevelSN.levelPercentageTank;
}