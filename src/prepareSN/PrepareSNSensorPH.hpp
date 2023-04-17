// Function to init a pH sensor instance

void initPHSensor()
{
    pHSensor.begin();
}

// Function to measure pH level and get a averaged value in 5 seconds

float measureAveragedPHLevel()
{
    float pHLevel = 0.0;
    for (int i = 0; i < 5; i++)
    {
        pHLevel += pHSensor.read_ph();
        delayWithMillisMecha(1000);
    }
    return pHLevel / 5.0;
}