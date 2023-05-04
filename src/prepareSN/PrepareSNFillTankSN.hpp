// Struct statement for water pump

actuatorPumpMotor aPMWater = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_WATER, PWM_RESOLUTION_ACTUATOR, ACTUATOR_DUTY_CYLCE_WATER};

// Function for fill tank SN

void fillTankSN()
{
    Serial.println("LLenando almacén SN");
    int levelSNLocal = measureLevelSN();
    int counter = 0;
    while (counter <= 3)
    {
        ledcWrite(aPMWater.channelPWM, aPMWater.dutyCyclePWM);
        if (levelSNLocal < 50)
            delayWithMillisMecha(30000);
        else if (levelSNLocal <= 70)
            delayWithMillisMecha(10000);
        else if (levelSNLocal < LEVEL_TANK_SN_FULL)
            delayWithMillisMecha(3000);
        else
            counter++;

        ledcWrite(aPMWater.channelPWM, 0);
        delayWithMillisMecha(10000);
        levelSNLocal = measureLevelSN();
        Serial.print("SN LEVEL (%): ");
        Serial.println(levelSNLocal);
    }
    Serial.println("Almacen lleno");
}

// Function configuration for water actuator

void initFillTankSN()
{
    pinMode(ACTUATOR_FILL_TANK, OUTPUT);
    ledcSetup(aPMWater.channelPWM, aPMWater.frecuencyPWM, aPMWater.resolutionPWM);
    ledcAttachPin(ACTUATOR_FILL_TANK, aPMWater.channelPWM);
}

bool isLowSNLevel()
{
    /*int levelSNLocal = measureLevelSN();
    Serial.print("LOW SN LEVEL:");
    Serial.println(levelSNLocal < LEVEL_TANK_SN_MIN);
    return (levelSNLocal < LEVEL_TANK_SN_MIN);*/

    // measure SN level and store in vector samples
    int sensorValue = measureLevelSN();
    levelSNSensorSamples[indexSNSensorSample] = sensorValue;
    indexSNSensorSample++; // update index
    if(indexSNSensorSample == SENSOR_LEVEL_MAX_SAMPLES) //reset index if greater than SENSOR_LEVEL_MAX_SAMPLES
        indexSNSensorSample=0;

    // get SN level average
    int sum=0;
    for(int i=0; i<SENSOR_LEVEL_MAX_SAMPLES; i++)
        sum += levelSNSensorSamples[i];

    float averageSNLevel = (float)sum/SENSOR_LEVEL_MAX_SAMPLES;

    // is the average level of SN less than LEVEL_TANK_SN_MIN
    /*Serial.print("SN LEVEL:");
    Serial.println(averageSNLevel < LEVEL_TANK_SN_MIN);*/
    Serial.print("Vector:");
    for(int i=0; i< SENSOR_LEVEL_MAX_SAMPLES; i++){
        Serial.print(levelSNSensorSamples[i]);
        Serial.print(", ");
    }
    Serial.println("");
    Serial.print("Indice modificado:");
    Serial.println(indexSNSensorSample-1);
    Serial.print("SN promedio: ");
    Serial.println(averageSNLevel);
    return (averageSNLevel < LEVEL_TANK_SN_MIN);

}