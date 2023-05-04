actuatorPumpMotor aPMIrrigateSN = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_IRRIGATE, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_IRRIGATE_SN};

void initSubmersiblePump()
{
    pinMode(PIN_RELAY_SUBMERSIBLE_PUMP, OUTPUT);
    ledcSetup(aPMIrrigateSN.channelPWM, aPMIrrigateSN.frecuencyPWM, aPMIrrigateSN.resolutionPWM);
    ledcAttachPin(PIN_RELAY_SUBMERSIBLE_PUMP, aPMIrrigateSN.channelPWM);
}

// This function irrigates SN the time indicated
void irrigateSN()
{
    Serial.println("Activando irrigación");
    ledcWrite(aPMIrrigateSN.channelPWM, aPMIrrigateSN.dutyCyclePWM);
    delayWithMillisMecha(30000);
    ledcWrite(aPMIrrigateSN.channelPWM, 0);
}