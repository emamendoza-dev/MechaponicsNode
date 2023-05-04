#include "cultivate/CultivateLedStrip.hpp"
#include "cultivate/CultivateSensorDht21.hpp"
#include "cultivate/CultivateFan.hpp"

void initCultivate(){
    initDht21Sensor();
    initLightIntensity();
}