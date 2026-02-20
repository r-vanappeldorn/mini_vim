#pragma once

#include "domain/editor/editor_state.hpp"

#include <sys/ioctl.h>

using mini_vim::domain::editor::EditorState;

namespace mini_vim::domain::renderer {

class Renderer {
  private:
    struct winsize ws;

  public:
    void render(EditorState& editorState);
};

};
