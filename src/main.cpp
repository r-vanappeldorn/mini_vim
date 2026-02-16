#include "domain/editor/editor_state.hpp"
#include "infra/terminal.hpp"
#include "domain/editor/editor.hpp"

#include <iostream>

#include <sys/types.h>
#include <unistd.h>

int main() {
  mini_vim::infra::Terminal terminal;
  mini_vim::domain::editor::Editor editor;
  mini_vim::domain::editor::EditorState editorState;

  while (editorState.running()) {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    editorState.setKeyPressed(c);
    if (n == -1) {
      terminal.die("read");
      break;
    }

    editor.process(editorState);

    std::cout << "\033[2J\033[1;1H" << editorState.getTerminalBuffer().contents();
    std::cout.flush();
  }

  return 0;
}
