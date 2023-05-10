void initDht21Sensor() {
    dhtSensor.begin();
}

float measureHumidityGrowingCell() {
    float h = dhtSensor.readHumidity(); // %HR
    if(isnan(h))
        Serial.println("Falló la medición de humedad del sensor DHT21");

    Serial.print("Humidity: ");
    Serial.println(h);

    return(h);
}

float measureTemperatureGrowingCell() {
    float t = dhtSensor.readTemperature(); // °C
    if(isnan(t))
        Serial.println("Falló la medición de temperatura del sensor DHT21");

    Serial.print("Temperature: ");
    Serial.println(t);

    return(t);
}