void initSubmersiblePump(){
    pinMode(PIN_RELAY_SUBMERSIBLE_PUMP, OUTPUT);
    digitalWrite(PIN_RELAY_SUBMERSIBLE_PUMP, LOW);
}

// This function irrigates SN the time indicated
void irrigateSN(uint32_t irrigationTimeMs){
    digitalWrite(PIN_RELAY_SUBMERSIBLE_PUMP, HIGH);
    delayWithMillisMecha(irrigationTimeMs);
    digitalWrite(PIN_RELAY_SUBMERSIBLE_PUMP, LOW);
}