#include "domain/editor/mode/normal.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp"

namespace mini_vim::domain::editor::mode {

void Normal::execute(EditorState& editorState) {
  char key = editorState.getKeyPressed();

  if (key == (int)(unsigned char) Keys::Enter) {
    if (editorState.getCommandBuffer().contents() == ":q") {
      editorState.killProcess();
    }

    return;
  }

  if (key == (int)(unsigned char) Keys::Backspace && !editorState.getCommandBuffer().contents().empty()) {
    editorState.getCommandBuffer().backspace();
    return;
  }

  if (key >= 32 && key <= 126) {
    editorState.getCommandBuffer().insert(key);
    return;
  }
}

};
