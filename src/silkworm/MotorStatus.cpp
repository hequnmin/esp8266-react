#include <silkworm/MotorStatus.h>

MotorStatus::MotorStatus(AsyncWebServer *server, SecurityManager* securityManager) : _server(server), _securityManager(securityManager) {
  _server->on(MOTOR_STATUS_SERVICE_PATH, HTTP_GET, 
    _securityManager->wrapRequest(std::bind(&MotorStatus::motorStatus, this, std::placeholders::_1), AuthenticationPredicates::IS_AUTHENTICATED)
  );
}

void MotorStatus::motorStatus(AsyncWebServerRequest *request) {
  AsyncJsonResponse * response = new AsyncJsonResponse(MAX_MOTOR_STATUS_SIZE);
  JsonObject root = response->getRoot();

  root["active"] =  0;
  root["motor_mode"] = 0;
  root["motor_freq_pin"] = 5;
  root["motor_freq_val"] = 256,
  root["motor_direct_pin"] = 4;
  root["motor_direct_val"] = 1;

  response->setLength();
  request->send(response);
}
