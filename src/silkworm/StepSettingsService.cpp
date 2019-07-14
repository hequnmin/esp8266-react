
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

	_stepNext = 0;
    handleStep(0);
}

void ICACHE_RAM_ATTR StepSettingsService::handleStep(uint8_t arg) {

	switch (arg)
	{
		case 0:
			Serial.println("Step 0");

			SWITCH_WR_INIT();
			PIN_FUNC_SELECT( SWITCH_MUX, SWITCH_FUNC );
			ETS_GPIO_INTR_DISABLE();
			ETS_GPIO_INTR_ATTACH( &handleStep, 1 );

			gpio_pin_intr_state_set( GPIO_ID_PIN( SWITCH_NUM ), GPIO_PIN_INTR_POSEDGE );

			GPIO_REG_WRITE( GPIO_STATUS_W1TC_ADDRESS, BIT(SWITCH_NUM) );
			ETS_GPIO_INTR_ENABLE();
			break;
		case 1:
			ETS_GPIO_INTR_DISABLE();
			Serial.println("Step 1");
			break;
		default:
			break;
	}




}

