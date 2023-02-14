#define ACTUATOR_FILL_TANK 25

void fillTankSN(int levelFillTankSN)
{
    int levelSN = measureLevelSN();

    while (levelSN < levelFillTankSN)
    {
        digitalWrite(ACTUATOR_FILL_TANK, HIGH);
        levelSN = measureLevelSN();
    }
}

void initFillTankSN()
{
    pinMode(ACTUATOR_FILL_TANK, OUTPUT);
}