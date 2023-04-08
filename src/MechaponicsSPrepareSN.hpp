#include "prepareSN/PrepareSNSensorLevelTank.hpp"
#include "prepareSN/PrepareSNSensorsBuffer.hpp"
#include "prepareSN/PrepareSNLoadProfile.hpp"
// #include "prepareSN/PrepareSNSaveDatalog.hpp"
#include "prepareSN/PrepareSNFillTankSN.hpp"
#include "prepareSN/PrepareSNDosePump.hpp"
#include "prepareSN/PrepareSNMixerTank.hpp"
#include "prepareSN/PrepareSNSensorCE.hpp"
#include "prepareSN/PrepareSNSensorPH.hpp"
#include "prepareSN/PrepareSNSensorTemperature.hpp"
#include "prepareSN/PrepareSNFuzzyControl.hpp"

bool flagWiFi;
bool flagOnOffLine;
bool flagLevelSN;
float temperatureSNCentigrade;
float CELevel;
float PHLevel;
int levelSN;

void initPrepareSN()
{
    // initLoadProfile();
    initSensorLevelSN();
    initSensorsLevelBuffer();
    initFillTankSN();
    initDosePump();
    initMixer();

    // PH, CE, temperature tests
    initCESensor();
    initPHSensor();
    initTemperatureSensor();
}

/*

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

// This function measure temperature, SN and CE
void measureSN()
{
    temperatureSNCentigrade = measureSNTemperature();
    CELevel = measureLevelCEAveraged(temperatureSNCentigrade);
    PHLevel = measureAveragedPHLevel();
    Serial.print("Temp (°C): ");
    Serial.println(temperatureSNCentigrade);
    Serial.print("pH: ");
    Serial.println(PHLevel);
    Serial.print("CE (uS/cm): ");
    Serial.println(CELevel);
}

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

    /*
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
    */
    // PH, CE, temperature tests
    /*float CELevelNoCompensation = measureLevelCEAveraged(25.0);
    Serial.print("Nivel de CE sin compensación (uS/cm): ");
    Serial.println(CELevelNoCompensation);*/


    levelSN = measureLevelSN();
    Serial.print("SN LEVEL (%): "); Serial.println(levelSN);

    while(isLowSNLevel())
        fillTankSN();
    
    // Desired Values of pH and CE
    float desiredPH = 5.75;
    float desiredCE = 2000.0;

    // Permissible pH and CE errors
    float pHPermissibleError = 0.2;
    float CEPermissibleError = 30.0;

    // Measure pH and CE of SN
    measureSN();

    // Calculates pH and CE error (inputs of controller) and adjust it to fuzzy control intervals established
    prepareInputsFuzzyControl(desiredPH, desiredCE, PHLevel, CELevel);


    while(is_pH_CE_Error(pHPermissibleError, CEPermissibleError)){
        // Apply fuzzy control
        fis_evaluate();

        prepareOutputsFuzzyControl(5);
        Serial.print("SA pump: ");
        Serial.println(g_fisOutput[0]);
        Serial.print("SB pump: ");
        Serial.println(g_fisOutput[1]);
        Serial.print("SNM pump: ");
        Serial.println(g_fisOutput[2]);

        // Getting results
        float timeAcidePump = g_fisOutput[0]; // In seconds
        float timeBasePump = g_fisOutput[1];
        float timeSNMPump = g_fisOutput[2];

        // Activating the pumps
        dose(0, timeAcidePump);
        dose(1, timeBasePump);
        dose(2, timeSNMPump);

        // Activating mixers
        mixer(45000);

        // Wait
        delayWithMillisMecha(15000);

        // Measure pH and CE levels
        measureSN();

        // Calculates pH and CE error (inputs of controller) and adjust it to fuzzy control intervals established
        prepareInputsFuzzyControl(desiredPH, desiredCE, PHLevel, CELevel);
    }

    delayWithMillisMecha(120000); // Repeat process every 15 minutes (900000)
}