#pragma once

#include "domain/events/event.hpp"
#include <map>
#include <vector>

namespace mini_vim::domain::events {

class EventManager {
  private:
    std::map<Event, std::vector<void (*)(int)>> events;

  public:
    EventManager *on(Event, void (*callback)(int));
    bool emit(Event event, int arg);
};

};
