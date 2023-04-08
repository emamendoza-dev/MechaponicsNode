// Struct statement for water pump

actuatorPumpMotor aPMWater = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_WATER, PWM_RESOLUTION_ACTUATOR, ACTUATOR_DUTY_CYLCE_WATER};

// Function for fill tank SN

void fillTankSN(){
    Serial.println("LLenando almacén SN");
    int levelSNLocal = measureLevelSN();
    int counter = 0;
    while (counter <= 3){
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
        delayWithMillisMecha(3000);
        levelSNLocal = measureLevelSN();
        Serial.print("SN LEVEL (%): "); Serial.println(levelSNLocal);
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

bool isLowSNLevel(){
    int levelSNLocal = measureLevelSN(); 
    Serial.print("LOW SN LEVEL:");
    Serial.println(levelSNLocal < LEVEL_TANK_SN_FULL);
    return (levelSNLocal < LEVEL_TANK_SN_FULL);
}