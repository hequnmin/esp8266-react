#ifndef StepSettingsService_h
#define StepSettingsService_h

#include <Arduino.h>
#include <gpio.h>
#include <silkworm/Comm.h>
#include <SettingsService.h>

#define MANAGE_STEP_DELAY 10

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

        void manageStep();
};




#endif