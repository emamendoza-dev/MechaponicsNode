
void initLightIntensity() {
    pinMode(PIN_STRIP_LED, OUTPUT);
    analogWrite(PIN_STRIP_LED, 255);
}

void turnOnLighting(int brightness){
    analogWrite(PIN_STRIP_LED, brightness);
}

void turnOffLighting(){
    analogWrite(PIN_STRIP_LED, 0);
}