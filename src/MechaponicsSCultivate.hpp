#include "cultivate/CultivateLedStrip.hpp"
#include "cultivate/CultivateSensorDht21.hpp"
#include "cultivate/CultivateFan.hpp"
#include "cultivate/CultivateGetTime.hpp"
#include "cultivate/CultiveLoadProfile.hpp"


void initCultivate()
{
    initDht21Sensor();
    initLightIntensity();
    initFan();
    initGetTime();
    initLoadProfile();
}

void setLighting(int brightnessCultivateC)
{
    // GET THE TIME
    int hourCultivateC = getHour();
    Serial.print("La hora es ");
    Serial.println(hourCultivateC);

    Serial.println("Valor de iluminacion");
    Serial.println(brightnessCultivateC);

    // ILLUMINATION FOR 16 HOURS
    if (hourCultivateC >= 22 || hourCultivateC < 7)
    {
        turnOffLighting();
        changeVelocityFan(60);
        Serial.println("Luz apagada");
    }
    else
    {
        turnOnLighting(brightnessCultivateC);
        changeVelocityFan(255);
        Serial.println("Luz encendida");
    }
}

void establishAcclimatization(float desiredTemperature){
    // Measure variables
    float humidityCell = measureHumidityGrowingCell();
    delayWithMillisMecha(1000);
    float temperatureCell = measureTemperatureGrowingCell();
    delayWithMillisMecha(1000);
    Serial.print("HR [%]: ");
    Serial.println(humidityCell);
    Serial.print("Temperatura [°C]: ");
    Serial.println(temperatureCell);

    // Desired temperature
    Serial.print("Temperatura deseada[°C]: ");
    Serial.println(desiredTemperature);
    // Error
    float temperatureError;
    temperatureError = desiredTemperature - temperatureCell;
    Serial.print("Error en la temperatura [°C]: ");
    Serial.println(temperatureError);
    // Control
    if (temperatureError > 0)
    {
      velocityFan--;
      Serial.print("Velocidad del ventilador reduce a ");
    }
    else if (temperatureError < 0)
    {
      velocityFan++;
      Serial.print("Velocidad del ventilador aumenta a ");
    }
    if (velocityFan < 0)
      velocityFan = 0;
    if (velocityFan > 255)
      velocityFan = 255;
    Serial.println(velocityFan);
    // Actuador
    changeVelocityFan(velocityFan);
}

void readNode2VariablesCC(){
    // Measure variables
    dBaseVarCC.dbNode2Hum = measureHumidityGrowingCell();
    delayWithMillisMecha(1000);
    dBaseVarCC.dbNode2Temp = measureTemperatureGrowingCell();
    delayWithMillisMecha(1000);
    dBaseVarCC.dbNode2Lum = map(cProfileCC.valLumProfileCC, 0, 255, 0, 100);
    dBaseVarCC.dbNode2Irri = 3;

    Serial.print("HR [%]: ");
    Serial.println(dBaseVarCC.dbNode2Hum);
    Serial.print("Temperatura [°C]: ");
    Serial.println(dBaseVarCC.dbNode2Temp);
    Serial.print("LuminsetLightingosidad: ");
    Serial.println(dBaseVarCC.dbNode2Lum);
}

void prepareCC()
{
    setLighting(cProfileCC.valLumProfileCC);

    // establishAcclimatization(cProfileCC.valTemProfileCC);
}

#include "cultivate/CultiveDatalog.hpp"