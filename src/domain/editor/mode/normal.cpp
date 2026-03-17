#include "domain/editor/mode/normal.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp"

namespace mini_vim::domain::editor::mode {

void Normal::execute(EditorState& editorState) {
  if (editorState.getKeyPressed() == (unsigned int) Keys::h) {
    editorState.getTerminalBuffer().moveLeft();
    return;
  }

  if (editorState.getKeyPressed() == (unsigned int) Keys::l) {
    editorState.getTerminalBuffer().moveRight();
    return;
  }
}

};
