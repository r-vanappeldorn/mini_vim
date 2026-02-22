#include "domain/renderer/renderer.hpp"
#include "domain/editor/mode/mode_enum.hpp"
#include "infra/terminal.hpp"

#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

namespace mini_vim::domain::renderer {

Renderer::Renderer(infra::Terminal &t) : terminal(t) {
  clear(0);
}

void Renderer::clear(int _) {
    std::cout << "\x1B[2J\x1B[H";
}

void Renderer::parseBuffer(const char *terminalContents, std::vector<std::string>& out) {
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

  this->lineIndex = lineIndex;
}

void Renderer::render(EditorState &editorState) {
  switch (editorState.getMode()) {
  case mini_vim::domain::editor::mode::Mode::Insert: {

    std::vector<std::string> out;
    out.reserve(terminal.getRows());

    for (int i = 0; i < terminal.getRows() + 1; i++) {
      std::string lineNumber = std::to_string(i);
      out.push_back(lineNumber + " ");
    }

    parseBuffer(editorState.getTerminalBuffer().contents().c_str(), out);
    for (int i = 0; i < terminal.getRows(); i++) {
      std::cout << out[i] << '\n';
    }
    std::cout << "\033[" << (lineIndex) << ";" << (out[lineIndex].length() +1) << "H";
    std::cout.flush();

  } break;
  case mini_vim::domain::editor::mode::Mode::Normal: {
    std::cout << editorState.getCommandBuffer().contents()
              << "\n"
              << mini_vim::domain::editor::mode::to_string(
                     editorState.getMode())
              << '\n';
  } break;
  }
}
} 
