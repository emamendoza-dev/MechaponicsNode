void initLightIntensity() {
    pinMode(PIN_STRIP_LED, OUTPUT);
    analogWrite(PIN_STRIP_LED, INITIAL_BRIGHTNESS);
}

void regulateLightIntensity(int brightness){
    analogWrite(PIN_STRIP_LED, brightness);
}