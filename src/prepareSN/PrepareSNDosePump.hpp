// Struct statement for buffer pump

actuatorPumpMotor aPMBufferSA = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_SA, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_BUFFER_SA};
actuatorPumpMotor aPMBufferSB = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_SB, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_BUFFER_SB};
actuatorPumpMotor aPMBufferSNM = {PWM_FRECUENCY_ACTUATOR, PWM_CHANNEL_SNM, PWM_RESOLUTION_ACTUATOR, PWM_SPEED_BUFFER_SNM};

// Function for buffer dose, It is dosed by time

void dose(int actuatorActivation, uint32_t timeDosePump)
{
    switch (actuatorActivation)
    {
    case 0:
        ledcWrite(aPMBufferSA.channelPWM, aPMBufferSA.dutyCyclePWM);
        delay(timeDosePump);
        ledcWrite(aPMBufferSA.channelPWM, 0);
        break;
    case 1:
        ledcWrite(aPMBufferSB.channelPWM, aPMBufferSB.dutyCyclePWM);
        delay(timeDosePump);
        ledcWrite(aPMBufferSB.channelPWM, 0);
        break;
    case 2:
        ledcWrite(aPMBufferSNM.channelPWM, aPMBufferSNM.dutyCyclePWM);
        delay(timeDosePump);
        ledcWrite(aPMBufferSNM.channelPWM, 0);
        break;
    default:
        break;
    }
}

// Function configuration for actuators dose

void initDosePump()
{
    pinMode(ACTUATOR_PUMP_SA, OUTPUT);
    ledcSetup(aPMBufferSA.channelPWM, aPMBufferSA.frecuencyPWM, aPMBufferSA.resolutionPWM);
    ledcAttachPin(ACTUATOR_PUMP_SA, aPMBufferSA.channelPWM);

    pinMode(ACTUATOR_PUMP_SB, OUTPUT);
    ledcSetup(aPMBufferSB.channelPWM, aPMBufferSB.frecuencyPWM, aPMBufferSB.resolutionPWM);
    ledcAttachPin(ACTUATOR_PUMP_SB, aPMBufferSB.channelPWM);

    pinMode(ACTUATOR_PUMP_SNM, OUTPUT);
    ledcSetup(aPMBufferSNM.channelPWM, aPMBufferSNM.frecuencyPWM, aPMBufferSNM.resolutionPWM);
    ledcAttachPin(ACTUATOR_PUMP_SNM, aPMBufferSNM.channelPWM);
}