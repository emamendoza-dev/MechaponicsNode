// Struct statement for water pump

actuatorPumpMotor aPMWater = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_WATER, PWM_RESOLUTION_ACTUATOR, ACTUATOR_DUTY_CYLCE_WATER};

// Function for fill tank SN

void fillTankSN(int levelFillTankSN, int levelTankSN)
{
    if (levelTankSN < levelFillTankSN)
    {
        ledcWrite(aPMWater.channelPWM, aPMWater.dutyCyclePWM);
    }
    else
    {
        ledcWrite(aPMWater.channelPWM, 0);
    }
}

// Function configuration for water actuator

void initFillTankSN()
{
    //
    pinMode(ACTUATOR_FILL_TANK, OUTPUT);
    ledcSetup(aPMWater.channelPWM, aPMWater.frecuencyPWM, aPMWater.resolutionPWM);
    ledcAttachPin(ACTUATOR_FILL_TANK, aPMWater.channelPWM);
}