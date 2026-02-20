#include "domain/editor/editor_state.hpp"
#include "domain/editor/buffer/string_buffer.hpp"
#include "domain/editor/mode/mode_enum.hpp"

namespace mini_vim::domain::editor {

EditorState::EditorState() {
  isRunning = true;
  mode = mode::Mode::Insert;
  commandBuffer = buffer::StringBuffer();
  terminalBuffer = buffer::StringBuffer();
}

void EditorState::setMode(mode::Mode mode) {
  this->mode = mode;
}

mode::Mode EditorState::getMode() {
  return mode;
}

buffer::StringBuffer& EditorState::getCommandBuffer() {
  return commandBuffer;
}
 
buffer::StringBuffer& EditorState::getTerminalBuffer() {
  return terminalBuffer;
}

bool EditorState::running(){
  return isRunning; 
}

void EditorState::setKeyPressed(char keyPressed) {
  this->keyPressed = keyPressed;
}

char EditorState::getKeyPressed() const {
  return keyPressed;
}

void EditorState::killProcess() {
  isRunning = false;
}

};
