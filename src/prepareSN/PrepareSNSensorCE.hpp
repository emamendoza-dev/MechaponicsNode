// Function to configurate and init CE sensor

void initCESensor() {
    Serial2.begin(9600, SERIAL_8N1, SENSOR_CE_RX, SENSOR_CE_TX);
    answerSensorCE.reserve(30);
}

// Function to send a String command to the CE sensor

void sendCommandToCESensor(String command){
    Serial2.print(command);
    Serial2.print('\r');
}

// Function to read the answer from the CE sensor and save it in "answerSensorCE" variable

void readAnswerFromCESensor() {
    while(answerSensorCEComplete == false){
        if(Serial2.available() > 0) {
            char inchar = (char)Serial2.read();
            answerSensorCE += inchar;
            if(inchar == '\r')
            answerSensorCEComplete = true;
        }
    }
}

// Function to get only the CE value from the answer of the sensor
float getCEValueFromSensorAnswer(){
    char answerSensorCE_Array[30];
    char *CE;
    answerSensorCE.toCharArray(answerSensorCE_Array, 30);
    CE = strtok(answerSensorCE_Array, ",");
    answerSensorCE = "";
    answerSensorCEComplete = false;
    return atof(CE);
}

// Function to measure the CE level for SN

float measureLevelCE() {
    float CE_f;
    sendCommandToCESensor("R");
    readAnswerFromCESensor();
    CE_f = getCEValueFromSensorAnswer();
    return CE_f;
}

// Function to get the averaged CE level of SN in 5 seconds

float measureLevelCEAveraged() {
    float CELevel = 0.0;
    for(int i=0; i<5; i++){
        CELevel += measureLevelCE();
        delay(1000);
    }
    return CELevel/5.0;
}