#pragma once

#include "domain/editor/editor_state.hpp"
#include "infra/terminal.hpp"

#include <string>
#include <sys/ioctl.h>
#include <vector>

using mini_vim::domain::editor::EditorState;

namespace mini_vim::domain::renderer {

class Renderer {
  private:
    infra::Terminal& terminal;
    int lineIndex;

  public:
    Renderer(infra::Terminal& terminal);
    void render(EditorState& editorState);
    static void clear(int args);
    void parseBuffer(const char *terminalContents, std::vector<std::string>& out);
};

};
