#pragma once
#include "domain/editor/editor_state.hpp"

#include "domain/editor/mode/mode_enum.hpp"
#include "domain/editor/mode/mode_interface.hpp"
#include "domain/events/event_manager.hpp"

#include <memory>
#include <unordered_map>

using namespace mini_vim::domain::editor::mode;

using ModeInterface = mini_vim::domain::editor::mode::ModeInterface;
using ModeKind = mini_vim::domain::editor::mode::Mode;
using ModeMap = std::unordered_map<ModeKind, std::unique_ptr<ModeInterface>>;

namespace mini_vim::domain::editor {

class Editor {
  private:
    ModeMap modeMap;
    mini_vim::domain::events::EventManager& eventManager;

  public:
    Editor(mini_vim::domain::events::EventManager& e);
    void process(EditorState& editorState);
    void kill();
};

};
