#pragma once
#include "domain/editor/editor_state.hpp"

#include "domain/editor/mode/mode_enum.hpp"
#include "domain/editor/mode/mode_interface.hpp"

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

  public:
    Editor();
    void process(EditorState& editorState);
    void kill();
};

};
