#include "domain/renderer/renderer.hpp"
#include "domain/editor/mode/mode_enum.hpp"
#include "infra/terminal.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>

namespace mini_vim::domain::renderer {

Renderer::Renderer(infra::Terminal &t) : terminal(t) {
  clear(0);
}

void Renderer::clear(int _) { std::cout << "\x1B[2J\x1B[H"; }

void Renderer::render(EditorState &editorState) {
  const std::string contents = editorState.getTerminalBuffer().toString();
  int rows = terminal.getRows();

  std::string frame;
  frame.reserve(rows * terminal.getColumns() + 256);

  frame += "\033[?25l";
  frame += "\033[H";
  frame += "\033[2J";

  auto appendPrefix = [&](int line) {
    frame += std::to_string(line);
    frame += " ";
  };

  int lineIndex = 1;
  int colIndex = 0;
  
  const int cursorIndex = editorState.getTerminalBuffer().cursor();
  int cursorLine = 1;
  int cursorCol = 0;
  bool cursorFound = false;

  int bufIndex = 0;

  appendPrefix(lineIndex);

  for (char c : contents) {
    if (!cursorFound && bufIndex == cursorIndex) {
      const std::string prefix = std::to_string(lineIndex) + " ";
      cursorLine = lineIndex;
      cursorCol = colIndex + (int) prefix.length();
      cursorFound = true;
    }

    if (c == '\0') break;

    if (c == '\r'){
      bufIndex++;
      continue;
    } 

    if (c != '\n') {
      frame += c;
      colIndex++;
      bufIndex++;
      cursorCol= 0;
      continue;
    }

    frame += '\n';
    lineIndex++;
    colIndex = 0;
    bufIndex++;

    appendPrefix(lineIndex);
  }

  if (!cursorFound && bufIndex == cursorIndex) {
    const std::string prefix = std::to_string(lineIndex) + " ";
    cursorLine = lineIndex;
    cursorCol = cursorIndex + prefix.length() + 1;
    cursorFound = true;
  }

  while (lineIndex < rows) {
    lineIndex++;
    frame += '\n';
  }

  editor::mode::Mode currentMode = editorState.getMode(); 
  std::string modeString =  mini_vim::domain::editor::mode::to_string(currentMode);
  frame.append(modeString + " " + std::to_string(editorState.getTerminalBuffer().cursor()));

  switch (editorState.getMode()) {
  case mini_vim::domain::editor::mode::Mode::Normal:
  case mini_vim::domain::editor::mode::Mode::Insert: {
    break;
  }
  case mini_vim::domain::editor::mode::Mode::Command: {
    cursorLine = lineIndex;
    cursorCol = modeString.length() + 2;
    for (char c : editorState.getCommandBuffer().toString()) {
      if (c == '\n' || c == '\r' || c == '\0')
        continue;
      frame += c;
      colIndex++;
    }

    break;
  }
  }

  frame += "\033[" + std::to_string(cursorLine) + ";" +
           std::to_string(cursorCol ) + "H";
  frame += "\033[?25h";
  ::write(STDOUT_FILENO, frame.data(), frame.size());
}

} // namespace mini_vim::domain::renderer
