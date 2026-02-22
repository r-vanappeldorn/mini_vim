#include "domain/editor/editor_state.hpp"
#include "domain/events/event.hpp"
#include "domain/events/event_manager.hpp"
#include "infra/terminal.hpp"
#include "domain/editor/editor.hpp"
#include "domain/renderer/renderer.hpp"

#include <sys/types.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

namespace events = mini_vim::domain::events;
namespace editor = mini_vim::domain::editor;
namespace renderer = mini_vim::domain::renderer;

int main() {
  mini_vim::infra::Terminal terminal;
  events::EventManager eventManager;
  editor::Editor editor = editor::Editor(eventManager);
  editor::EditorState editorState;
  renderer::Renderer renderer = renderer::Renderer(terminal);

  eventManager.on(events::Event::MODE_CHANED, renderer.clear);

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
