#pragma once

#include "domain/editor/buffer/string_buffer.hpp"
#include "domain/editor/mode/mode_enum.hpp"

namespace mini_vim::domain::editor {

class EditorState {
  private:
    buffer::StringBuffer terminalBuffer;
    buffer::StringBuffer commandBuffer;
    bool isRunning;
    mode::Mode mode;
    char keyPressed;

  public:
    EditorState();
    void setMode(mode::Mode mode);
    bool running();
    mode::Mode getMode();
    buffer::StringBuffer& getTerminalBuffer();
    buffer::StringBuffer& getCommandBuffer();
    char getKeyPressed() const;
    void setKeyPressed(char keyPressed);
    void killProcess();
};

};
