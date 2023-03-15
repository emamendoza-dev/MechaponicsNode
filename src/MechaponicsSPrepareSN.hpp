#include "prepareSN/PrepareSNSensorLevelTank.hpp"
#include "prepareSN/PrepareSNSensorsBuffer.hpp"
//#include "prepareSN/PrepareSNLoadProfile.hpp"
//#include "prepareSN/PrepareSNSaveDatalog.hpp"
#include "prepareSN/PrepareSNFillTankSN.hpp"
#include "prepareSN/PrepareSNDosePump.hpp"
#include "prepareSN/PrepareSNMixerTank.hpp"

bool flagWiFi;
bool flagOnOffLine;
bool flagLevelSN;

void initPrepareSN()
{
    // initLoadProfile();
    initSensorLevelSN();
    initSensorsLevelBuffer();
    initFillTankSN();
    initDosePump();
    initMixer();
}

/*
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
            dose(0, TIME_ACTIVATION_PUMP_SA);
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
            dose(2, TIME_ACTIVATION_PUMP_SNM);
        }
    } while (!(flagLevelContainers && flagStatusECSN));
}
*/

void prepareSN()
{
    /*
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
    

    int levelSN = measureLevelSN();

    fillTankSN(LEVEL_TANK_SN_MIN, levelSN);

    regulatepHSN(cProfileSN.valpHDown, cProfileSN.valpHUp);

    regulateECSN(cProfileSN.valECDown, cProfileSN.valECUp);

    fillTankSN(LEVEL_TANK_SN_FULL, levelSN);

    Serial.println(F("Saving datalog..."));
    saveParametersSN(PATH_SD_DATALOG_SN, sParametersSN);
    */

    Serial.println("LLenando almacén SN");
    int levelSN = measureLevelSN();
    Serial.println(levelSN);
    fillTankSN(LEVEL_TANK_SN_FULL, levelSN);
    delay(2000);

    Serial.println("Activando bomba de SA");
    dose(0, TIME_ACTIVATION_PUMP_SA);
    Serial.println("Activando bomba de SB");
    dose(1, TIME_ACTIVATION_PUMP_SB);
    Serial.println("Activando bomba de SNM");
    dose(2, TIME_ACTIVATION_PUMP_SNM);
    Serial.println("Activando mezcladores");
    mixer(TIME_ACTIVATION_MOTOR_R);
    measureLevelContainers();
}