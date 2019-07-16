#ifndef StepSettingsService_h
#define StepSettingsService_h

#include <ets_sys.h>
#include <osapi.h>
#include <user_interface.h>
#include <eagle_soc.h>
#include <gpio.h>
#include <PWM.h>

#include <silkworm/Comm.h>
#include <SettingsService.h>

#define MANAGE_STEP_DELAY               10
#define GPIO_START                      14

#define STEP_SETTINGS_FILE              "/config/stepSettings.json"
#define STEP_SETTINGS_SERVICE_PATH      "/rest/stepSettings"

#define SWITCH_NUM		                5    //D1
#define SWITCH_FUNC		                FUNC_GPIO5
#define SWITCH_MUX		                PERIPHS_IO_MUX_GPIO5_U

#define SWITCH_RD_INIT()	            GPIO_DIS_OUTPUT(SWITCH_NUM)
#define SWITCH_WR_INIT()	            GPIO_OUTPUT_SET(SWITCH_NUM,0)
#define SWITCH_SET_HIGH()               GPIO_OUTPUT_SET(SWITCH_NUM,1)
#define SWITCH_SET_LOW()                GPIO_OUTPUT_SET(SWITCH_NUM,0)
#define SWITCH_ACTIVE                   ( GPIO_INPUT_GET(SWITCH_NUM) != 0 )


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
        uint8_t _stepNext;
        uint8_t _stepCurrent;  

        void manageStart();
        void manageStep();

        static void handleStep(uint8_t arg);
};




#endif