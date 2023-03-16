void initTemperatureSensor(){
    temperatureSensor.begin();
    temperatureSensor.setResolution(12);
}

float measureSNTemperature() {
    temperatureSensor.requestTemperatures();
    float temperatureSNCentigrades = temperatureSensor.getTempCByIndex(0);
    return temperatureSNCentigrades;
}