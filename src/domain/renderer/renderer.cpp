#include "domain/renderer/renderer.hpp"
#include "domain/editor/mode/mode_enum.hpp"

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

namespace mini_vim::domain::renderer {

void Renderer::render(EditorState &editorState) {

  switch (editorState.getMode()) {
  case mini_vim::domain::editor::mode::Mode::Insert:
    std::cout << "\033[2J\033[1;1H"
              << editorState.getTerminalBuffer().contents()
              << "\n"
              << mini_vim::domain::editor::mode::to_string(
                     editorState.getMode())
              << '\n';
    break;
  case mini_vim::domain::editor::mode::Mode::Normal:
    std::cout << "\033[2J\033[1;1H"
              << editorState.getCommandBuffer().contents()
              << "\n"
              << mini_vim::domain::editor::mode::to_string(
                     editorState.getMode())
              << '\n';
    break;
  }
}
} 

