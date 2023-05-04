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
#include "prepareSN/PrepareSNIrrigateSN.hpp"

bool flagWiFi;
bool flagOnOffLine;
bool flagLevelSN;
float temperatureSNCentigrade;
float CELevel;
float PHLevel;
int levelSN;

void initPrepareSN()
{
    initLoadProfile();
    initSensorLevelSN();
    initSensorsLevelBuffer();
    initFillTankSN();
    initDosePump();
    initMixer();
    initSubmersiblePump();

    initCESensor();
    initPHSensor();
    initTemperatureSensor();
}

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

void readNode1VariablesSN(){
    dBaseVarSN.dbNode1Temp = measureSNTemperature();
    dBaseVarSN.dbNode1EC = measureLevelCEAveraged(temperatureSNCentigrade);
    dBaseVarSN.dbNode1pH = measureAveragedPHLevel();
    dBaseVarSN.dbNode1LevelSN = measureLevelSN();
    dBaseVarSN.dbNode1LevelSA = conversionLevelContainers(digitalRead(SENSOR_LEVEL_SA));
    dBaseVarSN.dbNode1LevelSB = conversionLevelContainers(digitalRead(SENSOR_LEVEL_SB));
    dBaseVarSN.dbNode1LevelSNM = conversionLevelContainers(digitalRead(SENSOR_LEVEL_SNM));
    Serial.print("Temp (°C): ");
    Serial.println(dBaseVarSN.dbNode1Temp);
    Serial.print("pH: ");
    Serial.println(dBaseVarSN.dbNode1pH);
    Serial.print("CE (uS/cm): ");
    Serial.println(dBaseVarSN.dbNode1EC);
    Serial.print("Level SN (%): ");
    Serial.println(dBaseVarSN.dbNode1LevelSN);
    Serial.print("Level SA (%): ");
    Serial.println(dBaseVarSN.dbNode1LevelSA);
    Serial.print("Level SB (%): ");
    Serial.println(dBaseVarSN.dbNode1LevelSB);
    Serial.print("Level SNM (%): ");
    Serial.println(dBaseVarSN.dbNode1LevelSNM);
}

void prepareSN()
{
    levelSN = measureLevelSN();
    Serial.print("SN LEVEL (%): "); Serial.println(levelSN);

    while(isLowSNLevel())
        fillTankSN();
    
    // Desired Values of pH and CE
    //float desiredPH = 5.75;
    float desiredPH = cProfileSN.valpHProfileSN;
    //float desiredCE = 2000.0;
    float desiredCE = cProfileSN.valECProfileSN;

    // Permissible pH and CE errors
    float pHPermissibleError = 0.1;
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

    delayWithMillisMecha(20000);

    readNode1VariablesSN();

    Serial.println("Solución preparada");
}