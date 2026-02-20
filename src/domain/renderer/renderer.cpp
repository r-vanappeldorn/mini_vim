#include "domain/renderer/renderer.hpp"
#include "domain/editor/mode/mode_enum.hpp"
#include "infra/terminal.hpp"

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

namespace mini_vim::domain::renderer {

Renderer::Renderer(infra::Terminal &t) : terminal(t) {}

void Renderer::render(EditorState &editorState) {
  switch (editorState.getMode()) {
  case mini_vim::domain::editor::mode::Mode::Insert: {
    std::vector<std::string> out;
    out.reserve(terminal.getRows());
    for (int i = 0; i < terminal.getRows() + 1; i++) {
      std::string lineNumber = std::to_string(i);
      out.push_back(lineNumber + " ");
    }

    const char *terminalContents = editorState.getTerminalBuffer().contents().c_str();
    int len = 0;
    int lineIndex = 0;
    while (terminalContents[len] != '\0') {
      if (lineIndex >= (int)out.size()) {
        break;
      }

      if (terminalContents[len] == '\r') {
        len++;
        continue;
      }

      if (terminalContents[len] == '\n') {
        lineIndex++;
        len++;
        continue;
      }

      if (lineIndex == 0) {
        lineIndex++;
      }

      out[lineIndex].push_back(terminalContents[len]);
      len++;
    }

    std::cout << "\033[2J\033[1;1H";
    for (int i = 0; i < terminal.getRows(); i++) {
      std::cout << out[i] << '\n';
    }
  } break;
  case mini_vim::domain::editor::mode::Mode::Normal: {
    std::cout << "\033[2J\033[1;1H" << editorState.getCommandBuffer().contents()
              << "\n"
              << mini_vim::domain::editor::mode::to_string(
                     editorState.getMode())
              << '\n';
  } break;
  }
}
} 
