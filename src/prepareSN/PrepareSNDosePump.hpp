#define ACTUATOR_PUMP_SA 13
#define ACTUATOR_PUMP_SB 12
#define ACTUATOR_PUMP_SNM 14

#define PWM_SPEED_BUFFER_SA 150
#define PWM_SPEED_BUFFER_SB 150
#define PWM_SPEED_BUFFER_SNM 200

#define TIME_ACTIVATION_PUMP_SA 500
#define TIME_ACTIVATION_PUMP_SB 500
#define TIME_ACTIVATION_PUMP_SNM 2000

void dose(int actuatorActivation, int pwmSpeedBuffer, uint32_t timeDosePump)
{
    switch (actuatorActivation)
    {
    case 0:
        analogWrite(ACTUATOR_PUMP_SA, pwmSpeedBuffer);
        delay(timeDosePump);
        break;
    case 1:
        analogWrite(ACTUATOR_PUMP_SB, pwmSpeedBuffer);
        delay(timeDosePump);
        break;
    case 2:
        analogWrite(ACTUATOR_PUMP_SNM, pwmSpeedBuffer);
        delay(timeDosePump);
        break;
    default:
        break;
    }
}

void initDosePump()
{
    pinMode(ACTUATOR_PUMP_SA, OUTPUT);
    pinMode(ACTUATOR_PUMP_SB, OUTPUT);
    pinMode(ACTUATOR_PUMP_SNM, OUTPUT);
}