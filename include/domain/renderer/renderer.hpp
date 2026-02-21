#pragma once

#include "domain/editor/editor_state.hpp"
#include "infra/terminal.hpp"

#include <sys/ioctl.h>

using mini_vim::domain::editor::EditorState;

namespace mini_vim::domain::renderer {

class Renderer {
  private:
    infra::Terminal& terminal;

  public:
    Renderer(infra::Terminal& terminal);
    void render(EditorState& editorState);
    void clear();
};

};
