// Struct statement for motors mixer

actuatorPumpMotor aPMMixerRigh = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_MOTOR_R, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_MOTOR_R};
actuatorPumpMotor aPMMixerLeft = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_MOTOR_L, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_MOTOR_L};

// Function for activation mixers

void mixer(uint32_t timeMixer)
{
    ledcWrite(aPMMixerRigh.channelPWM, aPMMixerRigh.dutyCyclePWM);
    ledcWrite(aPMMixerLeft.channelPWM, aPMMixerLeft.dutyCyclePWM);
    delay(timeMixer);
    ledcWrite(aPMMixerRigh.channelPWM, 0);
    ledcWrite(aPMMixerLeft.channelPWM, 0);
}

// Function configuration for actuators dose

void initMixer()
{
    pinMode(ACTUATOR_MOTOR_R, OUTPUT);
    ledcSetup(aPMMixerRigh.channelPWM, aPMMixerRigh.frecuencyPWM, aPMMixerRigh.resolutionPWM);
    ledcAttachPin(ACTUATOR_MOTOR_R, aPMMixerRigh.channelPWM);

    pinMode(ACTUATOR_MOTOR_L, OUTPUT);
    ledcSetup(aPMMixerLeft.channelPWM, aPMMixerLeft.frecuencyPWM, aPMMixerLeft.resolutionPWM);
    ledcAttachPin(ACTUATOR_MOTOR_L, aPMMixerLeft.channelPWM);
}