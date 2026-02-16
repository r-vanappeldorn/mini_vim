#pragma once

#include "domain/editor/mode/mode_interface.hpp"
namespace mini_vim::domain::editor::mode {

class Insert : public ModeInterface  {
  void execute(EditorState& editorState) override;
};

};
