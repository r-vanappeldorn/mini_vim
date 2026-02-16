#pragma once

#include "domain/editor/editor_state.hpp"
namespace mini_vim::domain::editor::mode {

class ModeInterface {
  public:
    virtual ~ModeInterface() = default;
    virtual void execute(EditorState& editorState) = 0;
};

};
