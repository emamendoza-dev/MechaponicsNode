#include "MechaponicsSInit.hpp"

Scheduler firebaseSchedulerState;

Task TaskFirebaseState(10000, TASK_FOREVER, &readStateMechaSystem);

void setup()
{
  initMechaponicsSystem();

  connectionWiFiOrServer();
}

//--------------------------------Configuracion en el loop
void loop()
{
  firebaseSchedulerState.execute();
  switch (modeOperatingSystem)
  {
  case 0:
    Serial.println("Modo de operación automatico");
    delay(1000);
    break;
  case 1:
    Serial.println("Modo de operación demostrativo");
    delay(1000);
    break;
  default:
    Serial.println("Modo de operación desconocido");
    delay(1000);
    break;
  }
}