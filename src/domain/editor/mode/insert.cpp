#include "domain/editor/mode/insert.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp"

namespace mini_vim::domain::editor::mode {

void Insert::execute(EditorState& editorState) {
  char key = editorState.getKeyPressed();
  if (key == (int)(unsigned char) Keys::Backspace) {
    editorState.getTerminalBuffer().backspace();
    return;
  }

  if (key == (int)(unsigned char) Keys::Enter) {
    editorState.getTerminalBuffer().insert('\n');
  }

  if (key >= 32 && key <= 126) {
    editorState.getTerminalBuffer().insert(key);
    return;
  }
}

};
