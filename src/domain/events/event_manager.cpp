#include "domain/events/event_manager.hpp"
#include "domain/events/event.hpp"
#include <algorithm>
#include <vector>

namespace mini_vim::domain::events {

EventManager *EventManager::on(Event event, void (*callback)(int)) {
  std::vector<void (*)(int)> *listeners = &events[event];
  if (std::find(listeners->begin(), listeners->end(), callback) != listeners->end()) {
    return this;
  }

  listeners->push_back(callback);

  return this;
}

bool EventManager::emit(Event event, int arg) {
  std::vector<void (*)(int)> listeners = events[event];
  
  if (listeners.size() == 0) {
    return false;
  }

  for (int i = 0; i < (int) listeners.size(); i+=1) {
    listeners[i](arg);
  }

  return true;
}
}
