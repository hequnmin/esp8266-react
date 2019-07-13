#ifndef StepSettingsService_h
#define StepSettingsService_h

#include <Arduino.h>
// #include <ets_sys.h>
// #include <osapi.h>
// #include <user_interface.h>
// #include <eagle_soc.h>
// #include <gpio.h>
// #include <PWM.h>

#include <silkworm/Comm.h>
#include <SettingsService.h>

#define MANAGE_STEP_DELAY 10
#define GPIO_START 14

#define STEP_SETTINGS_FILE "/config/stepSettings.json"
#define STEP_SETTINGS_SERVICE_PATH "/rest/stepSettings"

class StepSettingsService : public AdminSettingsService {
    public:

        StepSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager);
        ~StepSettingsService();

        void loop();
    protected:
        void readFromJsonObject(JsonObject& root);
        void writeToJsonObject(JsonObject& root);
        void onConfigUpdated();        
    private:
        // for the mangement delay loop
        unsigned long _lastManaged;

        uint8_t _stepMode;

        unsigned long lastLog;
        static os_timer_t timerStay;
        uint8_t stepCurrent;
        uint8_t stepNext;

        void manageStart();
        void manageStep();

        void handleStep();
};




#endif