#include "prepareSN/PrepareSNSensorLevelTank.hpp"
#include "prepareSN/PrepareSNSensorsBuffer.hpp"
#include "prepareSN/PrepareSNLoadProfile.hpp"
#include "prepareSN/PrepareSNSaveDatalog.hpp"

bool flagWiFi;
bool flagOnOffLine;
bool flagLevelSN;

void initPrepareSN()
{
    initLoadProfile();
    initSensorLevelSN();
    initSensorsLevelBuffer();
}

void fillTankSN()
{
    bool flagLevelContainers = measureLevelContainers();

    do
    {
        flagLevelSN = measureLevelSN();

        // Code for fill Tank SN

    } while (flagLevelContainers && flagLevelSN);
}

float measurepHSN()
{

    return 5.0;
}

void dose(int mode, float valReference)
{
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
            dose(1, valLevelSNpH);
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
            dose(1, valLevelSNEC);
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

    bool flagLevelContainers = measureLevelContainers();

    fillTankSN();

    regulatepHSN(cProfileSN.valpHDown, cProfileSN.valpHUp);

    regulateECSN(cProfileSN.valECDown, cProfileSN.valECUp);

    Serial.println(F("Saving datalog..."));
    saveParametersSN(PATH_SD_DATALOG_SN, sParametersSN);
}