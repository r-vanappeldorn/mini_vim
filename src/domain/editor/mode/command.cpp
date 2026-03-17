#include "domain/editor/mode/command.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp"

namespace mini_vim::domain::editor::mode {

void Command::execute(EditorState& editorState) {
  char key = editorState.getKeyPressed();

  if (key == (int)(unsigned char) Keys::Enter) {
    if (editorState.getCommandBuffer().toString() == ":q") {
      editorState.killProcess();
    }

    return;
  }

  if (key == (int)(unsigned char) Keys::Backspace) {
    editorState.getCommandBuffer().backspace();
    return;
  }

  if (key >= 32 && key <= 126) {
    editorState.getCommandBuffer().insert(key);
    return;
  }
}

};
