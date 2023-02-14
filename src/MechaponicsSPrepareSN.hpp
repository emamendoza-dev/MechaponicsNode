#include "prepareSN/PrepareSNSensorLevelTank.hpp"
#include "prepareSN/PrepareSNSensorsBuffer.hpp"
#include "prepareSN/PrepareSNLoadProfile.hpp"
#include "prepareSN/PrepareSNSaveDatalog.hpp"
#include "prepareSN/PrepareSNFillTankSN.hpp"
#include "prepareSN/PrepareSNDosePump.hpp"

bool flagWiFi;
bool flagOnOffLine;
bool flagLevelSN;

void initPrepareSN()
{
    initLoadProfile();
    initSensorLevelSN();
    initSensorsLevelBuffer();
    initFillTankSN();
    initDosePump();
}

float measurepHSN()
{

    return 5.0;
}

void regulatepHSN(float valpHDown, float valpHUp)
{
    bool flagLevelContainers = measureLevelContainers();

    bool flagStatuspHSN = false;

    do
    {
        float valLevelSNpH = measurepHSN();

        // Code for dose pH buffer

        if (valLevelSNpH >= valpHDown && valLevelSNpH <= valpHUp)
        {
            flagStatuspHSN = true;
        }
        else
        {
            flagStatuspHSN = false;
            dose(0, PWM_SPEED_BUFFER_SA, TIME_ACTIVATION_PUMP_SA);
        }
    } while (!(flagLevelContainers && flagStatuspHSN));
}

float measureECSN()
{

    return 5.0;
}

void regulateECSN(float valECDown, float valECUp)
{
    bool flagLevelContainers = measureLevelContainers();

    bool flagStatusECSN = false;

    do
    {
        float valLevelSNEC = measureECSN();

        // Code for dose pH buffer

        if (valLevelSNEC >= valECDown && valLevelSNEC <= valECUp)
        {
            flagStatusECSN = true;
        }
        else
        {
            flagStatusECSN = false;
            dose(2, PWM_SPEED_BUFFER_SA, TIME_ACTIVATION_PUMP_SNM);
        }
    } while (!(flagLevelContainers && flagStatusECSN));
}

bool prepareSN()
{
    // Ask WiFi connected
    if (flagWiFi)
    {
        flagOnOffLine = true;
    }
    else
    {
        flagOnOffLine = false;
    }

    Serial.println(F("Loading configuration..."));
    loadConfiguration(PATH_SD_PROFILE_SN, cProfileSN);

    fillTankSN(LEVEL_TANK_SN_MIN);

    regulatepHSN(cProfileSN.valpHDown, cProfileSN.valpHUp);

    regulateECSN(cProfileSN.valECDown, cProfileSN.valECUp);

    fillTankSN(LEVEL_TANK_SN_FULL);

    Serial.println(F("Saving datalog..."));
    saveParametersSN(PATH_SD_DATALOG_SN, sParametersSN);
}