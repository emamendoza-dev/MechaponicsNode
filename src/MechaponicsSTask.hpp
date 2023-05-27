Scheduler firebaseSchedulerState;

void readStateMechaSystem();
void readStateNodesMechaSystem();
void readPerfilMechaSystem();
void showParametersOLED();
void irrigateSN();
void writeFirebaseBD();
void saveMechaSystemDatalog();

Task TaskFirebaseState(TASK_MINUTE * 1, TASK_FOREVER, &readStateMechaSystem); // 1 HOUR
Task TaskFirebaseStateNodes(TASK_HOUR * 1, TASK_FOREVER, &readStateNodesMechaSystem);
Task TaskFirebasePerfil(TASK_MINUTE * 1, TASK_FOREVER, &readPerfilMechaSystem); // 1 HOUR
Task TaskOLEDParameters(TASK_MINUTE * 2, TASK_FOREVER, &showParametersOLED);
Task TaskIrrigationSN(TASK_MINUTE * 3, TASK_FOREVER, &irrigateSN);
Task TaskWriteDBNodeSN(TASK_MINUTE * 3, TASK_FOREVER, &writeFirebaseBD); // 20 MINUTES
Task TaskWriteDatalogSN(TASK_SECOND * 20, TASK_FOREVER, &saveMechaSystemDatalog); // 20 MINUTES

void enableMechaSystemTask()
{
    firebaseSchedulerState.addTask(TaskFirebaseState);
    firebaseSchedulerState.addTask(TaskFirebasePerfil);
    firebaseSchedulerState.addTask(TaskOLEDParameters);
    firebaseSchedulerState.addTask(TaskFirebaseStateNodes);
    firebaseSchedulerState.addTask(TaskIrrigationSN);
    firebaseSchedulerState.addTask(TaskWriteDBNodeSN);
    firebaseSchedulerState.addTask(TaskWriteDatalogSN);

    TaskFirebaseState.enable();
    TaskFirebasePerfil.enable();
    TaskOLEDParameters.enable();
    TaskFirebaseStateNodes.enable();
    TaskIrrigationSN.enable();
    TaskWriteDBNodeSN.enable();
    TaskWriteDatalogSN.enable();
}