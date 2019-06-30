
#include <silkworm/MotorSettingsService.h>

MotorSettingsService::MotorSettingsService(AsyncWebServer* server, FS* fs, SecurityManager* securityManager) : AdminSettingsService(server, fs, securityManager, MOTOR_SETTINGS_SERVICE_PATH, MOTOR_SETTINGS_FILE) {
  onConfigUpdated();
}

MotorSettingsService::~MotorSettingsService() {}

void MotorSettingsService::loop() {
  unsigned long currentMillis = millis();
  unsigned long manageElapsed = (unsigned long)(currentMillis - _lastManaged);
  if (manageElapsed >= MANAGE_MOTOR_DELAY){
    _lastManaged = currentMillis;
     manageMotor();
  }
}

void MotorSettingsService::manageMotor(){
  if (_motorMode == MOTOR_MODE_ALWAYS) {
    startMotor();
  } else {
    // if (_motorMode == MOTOR_MODE_DISABLED) {
    //   stopMotor();
    // }
  }
}

void MotorSettingsService::startMotor() {
  Serial.println("Starting software access motor.");
  
  //PWM
  pinMode(_motorFreqPin, OUTPUT);
  analogWrite(_motorFreqPin, _motorFreqVal);

  //Direct
  pinMode(_motorDirectPin, OUTPUT);
  digitalWrite(_motorDirectPin, _motorDirectVal);

}

void MotorSettingsService::stopMotor() {
  Serial.println("Stopping software access motor.");

  //PWM
  pinMode(_motorFreqPin, OUTPUT);
  analogWrite(_motorFreqPin, 0);
}


void MotorSettingsService::readFromJsonObject(JsonObject& root) {
  // _motorMode = root["motor_mode"] | MOTOR_MODE_DISABLED;
  // switch (_motorMode) {
  //   case MOTOR_MODE_MANUAL:
  //   case MOTOR_MODE_DISABLED:
  //   default:
  //     _motorMode = MOTOR_MODE_DISABLED;
  // }
  // _motorFreqPin = root["motor_freq_pin"] | ESP8266_PIN_D1;
  // _motorFreqVal = root["motor_freq_val"] | MOTOR_FREQ_VAL_DEFAULT;
  // _motorDirectPin = root["motor_direct_pin"] | ESP8266_PIN_D2;
  // _motorDirectVal = root["motor_direct_val"] | MOTOR_DIRECT_CLOCKWISE;
  _motorMode = root["motor_mode"];
  _motorFreqPin = root["motor_freq_pin"];
  _motorFreqVal = root["motor_freq_val"];
  _motorDirectPin = root["motor_direct_pin"];
  _motorDirectVal = root["motor_direct_val"];
}

void MotorSettingsService::writeToJsonObject(JsonObject& root) {
  root["motor_mode"] = _motorMode;
  root["motor_freq_pin"] = _motorFreqPin;
  root["motor_freq_val"] = _motorFreqVal;
  root["motor_direct_pin"] = _motorDirectPin;
  root["motor_direct_val"] = _motorDirectVal;
}

void MotorSettingsService::onConfigUpdated() {
  _lastManaged = millis() - MANAGE_MOTOR_DELAY;
  stopMotor();
}

