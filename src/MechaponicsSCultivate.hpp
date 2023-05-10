#include "cultivate/CultivateLedStrip.hpp"
#include "cultivate/CultivateSensorDht21.hpp"
#include "cultivate/CultivateFan.hpp"
#include "cultivate/CultivateGetTime.hpp"

void initCultivate(){
    initDht21Sensor();
    initLightIntensity();
    initFan();
    initGetTime();
}

void cultivate() {
    // Encender luz por 16 horas(57600000) y apagar durante 8 horas (28800000 ms)

}