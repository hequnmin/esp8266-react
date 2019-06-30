#if !defined(MotorStatus_h)
#define MotorStatus_h

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#elif defined(ESP_PLATFORM)
  #include <WiFi.h>
  #include <AsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncArduinoJson6.h>
#include <SecurityManager.h>

#define MAX_MOTOR_STATUS_SIZE 1024
#define MOTOR_STATUS_SERVICE_PATH "/rest/motorStatus"

class MotorStatus
{
    
    public:
        MotorStatus(AsyncWebServer *server, SecurityManager* securityManager);

    private:
        AsyncWebServer* _server;
        SecurityManager* _securityManager;

        void motorStatus(AsyncWebServerRequest *request);
};


#endif // MotorStatus_h
