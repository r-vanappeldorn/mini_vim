#include "domain/editor/editor_state.hpp"
#include "infra/terminal.hpp"
#include "domain/editor/editor.hpp"
#include "domain/renderer/renderer.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>


int main() {
  mini_vim::infra::Terminal terminal;
  mini_vim::domain::editor::Editor editor;
  mini_vim::domain::editor::EditorState editorState;
  mini_vim::domain::renderer::Renderer renderer = mini_vim::domain::renderer::Renderer(terminal);

  renderer.render(editorState);
  while (editorState.running()) {
    char c;
    ssize_t n = read(STDIN_FILENO, &c, 1);
    editorState.setKeyPressed(c);
    if (n == -1) {
      terminal.die("read");
      break;
    }

    editor.process(editorState);
    renderer.render(editorState);
  }

  return 0;
}
