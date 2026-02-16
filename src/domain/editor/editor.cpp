#include "domain/editor/editor.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp" #include "domain/editor/mode/mode_enum.hpp"
op
#include "domain/editor/mode/insert.hpp"

#include <memory>

namespace mini_vim::domain::editor {
  
Editor::Editor() {
  this->modeMap[mode::Mode::Insert] = std::make_unique<Insert>();
  this->modeMap[mode::Mode::Normal] = std::make_unique<Insert>();
}

void Editor::process(EditorState& editorState) {
  if (editorState.getMode() == mode::Mode::Normal && editorState.getKeyPressed() == (int)(unsigned char) Keys::i)  {
    editorState.setMode(mode::Mode::Insert);
    return;
  }

  modeMap[editorState.getMode()]->execute(editorState);
}
}
