#ifndef MotorSettingsService_h
#define MotorSettingsService_h

#include <Servo.h>
#include <silkworm/Comm.h>
#include <SettingsService.h>

#define MANAGE_MOTOR_DELAY 10000

#define MOTOR_MODE_DISABLED 0
#define MOTOR_MODE_ALWAYS 1
#define MOTOR_MODE_MANUAL 2

#define MOTOR_FREQ_VAL_MIN 0
#define MOTOR_FREQ_VAL_MAX 1024
#define MOTOR_FREQ_VAL_DEFAULT 512
#define MOTOR_DIRECT_CLOCKWISE 0
#define MOTOR_DIRECT_ANTICLOCKWISE 1

#define MOTOR_SETTINGS_FILE "/config/motorSettings.json"
#define MOTOR_SETTINGS_SERVICE_PATH "/rest/motorSettings"

class MotorSettingsService : public AdminSettingsService {
    public:
        MotorSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager);
        ~MotorSettingsService();
        
        void loop();
    protected:
        void readFromJsonObject(JsonObject& root);
        void writeToJsonObject(JsonObject& root);
        void onConfigUpdated();

    private:
        uint8_t _motorMode;
        uint8_t _motorFreqPin;
        uint16_t _motorFreqVal;
        uint8_t _motorDirectPin;
        uint8_t _motorDirectVal;

        // for the mangement delay loop
        unsigned long _lastManaged;

        Servo *_motor;

        void manageMotor();
        void startMotor();
        void stopMotor();
};

#endif