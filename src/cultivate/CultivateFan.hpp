void initFan() {
    pinMode(PIN_FAN, OUTPUT);
    analogWrite(PIN_FAN, FAN_VALUE);
}

void changeVelocityFan(int velocity){
    analogWrite(PIN_FAN, velocity);
}

void turnOffFan(){
    analogWrite(PIN_FAN, 0);
}
