
#include <silkworm/StepSettingsService.h>

StepSettingsService::StepSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) : AdminSettingsService(server, fs, securityManager, STEP_SETTINGS_SERVICE_PATH, STEP_SETTINGS_FILE) {
    onConfigUpdated();
}

StepSettingsService::~StepSettingsService() {}

void StepSettingsService::loop() {
	unsigned long currentMillis = millis();
	unsigned long manageElapsed = (unsigned long)(currentMillis - _lastManaged);
	if (manageElapsed >= MANAGE_STEP_DELAY){
		_lastManaged = currentMillis;
    	manageStep();
	}    
}

void StepSettingsService::manageStart(){

}

void StepSettingsService::manageStep(){
	if (_stepMode == 0) {

  	} else {

	}
}

void StepSettingsService::readFromJsonObject(JsonObject& root) {
	_stepMode = root["step_mode"];
}

void StepSettingsService::writeToJsonObject(JsonObject& root) {
	root["step_mode"] = _stepMode;
}

void StepSettingsService::onConfigUpdated() {
  	_lastManaged = millis() - MANAGE_STEP_DELAY;

	stepNext = 0;
    handleStep();
}

void StepSettingsService::handleStep(void) {



}

