#include "domain/editor/editor.hpp"
#include "domain/editor/editor_state.hpp"
#include "domain/editor/keys.hpp"
#include "domain/editor/mode/mode_enum.hpp"

#include "domain/editor/mode/insert.hpp"
#include "domain/editor/mode/normal.hpp"
#include "domain/events/event.hpp"

#include <memory>

namespace mini_vim::domain::editor {
  
Editor::Editor(mini_vim::domain::events::EventManager& e) : eventManager(e) {
  this->modeMap[mode::Mode::Insert] = std::make_unique<Insert>();
  this->modeMap[mode::Mode::Normal] = std::make_unique<Normal>();
}

void Editor::process(EditorState& editorState) {
  char key = editorState.getKeyPressed();

  if (editorState.getMode() == mode::Mode::Insert && key == (int)(unsigned) Keys::Esc) {
    editorState.setMode(mode::Mode::Normal);
    eventManager.emit(events::Event::MODE_CHANED, 10);
    return;
  }

  if (editorState.getMode() == mode::Mode::Normal && editorState.getKeyPressed() == (int)(unsigned char) Keys::i)  {
    editorState.setMode(mode::Mode::Insert);
    eventManager.emit(events::Event::MODE_CHANED, 10);
    return;
  }

  modeMap[editorState.getMode()]->execute(editorState);
}
}
