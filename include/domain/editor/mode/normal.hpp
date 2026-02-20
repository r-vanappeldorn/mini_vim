#pragma once

#include "domain/editor/mode/mode_interface.hpp"

namespace mini_vim::domain::editor::mode {

class Normal : public ModeInterface  {
  void execute(EditorState& editorState) override;
  void runCommand(EditorState& bufferContents);
};

};
