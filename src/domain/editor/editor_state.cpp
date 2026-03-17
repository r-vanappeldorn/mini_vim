#include "domain/editor/editor_state.hpp"
#include "domain/editor/buffer/gap_buffer.hpp"
#include "domain/editor/mode/mode_enum.hpp"

namespace mini_vim::domain::editor {

EditorState::EditorState() {
  isRunning = true;
  mode = mode::Mode::Insert;
  buffer::GapBuffer terminalBuffer(64);
  buffer::GapBuffer commandBuffer(64);
}

void EditorState::setMode(mode::Mode mode) {
  this->mode = mode;
}

mode::Mode EditorState::getMode() {
  return mode;
}

buffer::GapBuffer& EditorState::getCommandBuffer() {
  return commandBuffer;
}
 
buffer::GapBuffer& EditorState::getTerminalBuffer() {
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
