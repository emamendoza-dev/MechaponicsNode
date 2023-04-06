// Function to emulate the delay() behaviour using millis() 
void delayWithMillisMecha(uint32_t milliseconds){
  unsigned long timeNow = millis();
  while(millis() < timeNow + milliseconds){}
}