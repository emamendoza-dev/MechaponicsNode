Scheduler firebaseSchedulerState;

void readStateMechaSystem();
void readStateNodesMechaSystem();
void readPerfilMechaSystem();
void showParametersOLED();
void irrigateSN();
void writeFirebaseBD();

Task TaskFirebaseState(TASK_HOUR * 1, TASK_FOREVER, &readStateMechaSystem);
Task TaskFirebaseStateNodes(TASK_HOUR * 1, TASK_FOREVER, &readStateNodesMechaSystem);
Task TaskFirebasePerfil(TASK_HOUR * 1, TASK_FOREVER, &readPerfilMechaSystem);
Task TaskOLEDParameters(TASK_MINUTE * 2, TASK_FOREVER, &showParametersOLED);
Task TaskIrrigationSN(TASK_MINUTE * 3, TASK_FOREVER, &irrigateSN);
Task TaskWriteDBNodeSN(TASK_MINUTE * 15, TASK_FOREVER, &writeFirebaseBD);

void enableMechaSystemTask()
{
    firebaseSchedulerState.addTask(TaskFirebaseState);
    firebaseSchedulerState.addTask(TaskFirebasePerfil);
    firebaseSchedulerState.addTask(TaskOLEDParameters);
    firebaseSchedulerState.addTask(TaskFirebaseStateNodes);
    firebaseSchedulerState.addTask(TaskIrrigationSN);
    firebaseSchedulerState.addTask(TaskWriteDBNodeSN);

    TaskFirebaseState.enable();
    TaskFirebasePerfil.enable();
    TaskOLEDParameters.enable();
    TaskFirebaseStateNodes.enable();
    TaskIrrigationSN.enable();
    TaskWriteDBNodeSN.enable();
}