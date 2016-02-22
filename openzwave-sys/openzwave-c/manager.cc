#include <string>
#include "manager.h"

extern "C" {

Manager * manager_create() {
  return Manager::Create();
}

Manager * manager_get() {
  return Manager::Get();
}

void manager_destroy() {
  Manager::Destroy();
}

bool manager_add_watcher(Manager * manager, Manager::pfnOnNotification_t _watcher, void* _context) {
  return manager->AddWatcher(_watcher, _context);
}

bool manager_remove_watcher(Manager * manager, Manager::pfnOnNotification_t _watcher, void* _context) {
  return manager->RemoveWatcher(_watcher, _context);
}

bool manager_add_driver(Manager * manager, const char * _controllerPath, const Driver::ControllerInterface * _interface) {
  const std::string controllerPath(_controllerPath);
  return manager->AddDriver(controllerPath, *_interface);
}

bool manager_remove_driver(Manager * manager, const char * _controllerPath) {
  const std::string controllerPath(_controllerPath);
  return manager->RemoveDriver(controllerPath);
}

uint8 manager_get_controller_node_id(Manager * manager, const uint32 home_id) {
  return manager->GetControllerNodeId(home_id);
}

uint8 manager_get_suc_node_id(Manager * manager, const uint32 home_id) {
  return manager->GetSUCNodeId(home_id);
}

bool manager_is_primary_controller(Manager * manager, const uint32 home_id) {
  return manager->IsPrimaryController(home_id);
}

bool manager_is_bridge_controller(Manager * manager, const uint32 home_id) {
  return manager->IsBridgeController(home_id);
}

uint32 manager_get_send_queue_count(Manager * manager, const uint32 home_id) {
  return manager->GetSendQueueCount(home_id);
}

void manager_log_driver_statistics(Manager * manager, const uint32 home_id) {
  manager->LogDriverStatistics(home_id);
}

Driver::ControllerInterface manager_get_controller_interface_type(Manager * manager, const uint32 home_id) {
  return manager->GetControllerInterfaceType(home_id);
}

char * manager_get_library_version(Manager * manager, const uint32 home_id, const RustStringCreator stringCreator) {
  // We can't just return c_str() because the underlying buffer for "string"
  // would be deallocated after the end of this function. Thats why we have a
  // complex dance with the Rust function stringCreator.
  return stringCreator(manager->GetLibraryVersion(home_id).c_str()); // stringCreator expects a NUL-ended string.
}

char * manager_get_library_type_name(Manager * manager, const uint32 home_id, const RustStringCreator stringCreator) {
  return stringCreator(manager->GetLibraryTypeName(home_id).c_str());
}

char * manager_get_controller_path(Manager * manager, const uint32 home_id, const RustStringCreator stringCreator) {
  return stringCreator(manager->GetControllerPath(home_id).c_str());
}

int32 manager_get_poll_interval(Manager * manager) {
  return manager->GetPollInterval();
}

void manager_set_poll_interval(Manager * manager, int32 interval, bool between_poll) {
  manager->SetPollInterval(interval, between_poll);
}

bool manager_enable_poll_with_intensity(Manager * manager, const ValueID * value, uint8 intensity) {
  return manager->EnablePoll(*value, intensity);
}

bool manager_enable_poll(Manager * manager, const ValueID * value) {
  return manager->EnablePoll(*value);
}

bool manager_disable_poll(Manager * manager, const ValueID * value) {
  return manager->DisablePoll(*value);
}

bool manager_is_polled(Manager * manager, const ValueID * value) {
  return manager->isPolled(*value);
}

void manager_set_poll_intensity(Manager * manager, const ValueID * value, uint8 intensity) {
  manager->SetPollIntensity(*value, intensity);
}

uint8 manager_get_poll_intensity(Manager * manager, const ValueID * value) {
  return manager->GetPollIntensity(*value);
}

char * manager_get_value_label(Manager * manager, const ValueID * id, const RustStringCreator stringCreator) {
  return stringCreator(manager->GetValueLabel(*id).c_str());
}

void manager_set_value_label(Manager * manager, const ValueID * id, char const * str) {
  const std::string string(str);
  manager->SetValueLabel(*id, string);
}

char * manager_get_value_units(Manager * manager, const ValueID * id, const RustStringCreator stringCreator) {
  return stringCreator(manager->GetValueUnits(*id).c_str());
}

void manager_set_value_units(Manager * manager, const ValueID * id, char const * str) {
  const std::string string(str);
  manager->SetValueUnits(*id, string);
}

char * manager_get_value_help(Manager * manager, const ValueID * id, const RustStringCreator stringCreator) {
  return stringCreator(manager->GetValueHelp(*id).c_str());
}

void manager_set_value_help(Manager * manager, const ValueID * id, char const * str) {
  const std::string string(str);
  manager->SetValueHelp(*id, string);
}

int32 manager_get_value_min(Manager * manager, const ValueID * id) {
  return manager->GetValueMin(*id);
}

int32 manager_get_value_max(Manager * manager, const ValueID * id) {
  return manager->GetValueMax(*id);
}

bool manager_is_value_read_only(Manager * manager, const ValueID * id) {
  return manager->IsValueReadOnly(*id);
}

bool manager_is_value_write_only(Manager * manager, const ValueID * id) {
  return manager->IsValueWriteOnly(*id);
}

bool manager_is_value_set(Manager * manager, const ValueID * id) {
  return manager->IsValueSet(*id);
}

bool manager_is_value_polled(Manager * manager, const ValueID * id) {
  return manager->IsValuePolled(*id);
}

GET_VALUE_FUNC(as_bool, bool* value) {
  return manager->GetValueAsBool(*id, value);
}

GET_VALUE_FUNC(as_byte, uint8* value) {
  return manager->GetValueAsByte(*id, value);
}

GET_VALUE_FUNC(as_float, float* value) {
  return manager->GetValueAsFloat(*id, value);
}

GET_VALUE_FUNC(as_int, int32* value) {
  return manager->GetValueAsInt(*id, value);
}

GET_VALUE_FUNC(as_short, int16* value) {
  return manager->GetValueAsShort(*id, value);
}

GET_VALUE_FUNC(as_string, char** value, const RustStringCreator stringCreator) {
  std::string result;
  bool res =  manager->GetValueAsString(*id, &result);
  *value = stringCreator(result.c_str());
  return res;
}

GET_VALUE_FUNC(as_raw, uint8** value, uint8* length) {
  return manager->GetValueAsRaw(*id, value, length);
}

GET_VALUE_FUNC(list_selection_as_string, char** value, const RustStringCreator stringCreator) {
  std::string result;
  bool res = manager->GetValueListSelection(*id, &result);
  *value = stringCreator(result.c_str());
  return res;
}

GET_VALUE_FUNC(list_selection_as_int, int32* value) {
  return manager->GetValueListSelection(*id, value);
}

} /* extern "C" */
