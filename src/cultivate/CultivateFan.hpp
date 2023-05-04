void initFan() {
    pinMode(PIN_FAN, OUTPUT);
    analogWrite(PIN_FAN, INITIAL_FAN_VALUE);
}

void regulateVelocityFan(int velocity){
    analogWrite(PIN_FAN, velocity);
}