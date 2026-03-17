#pragma once

#include "domain/editor/buffer/gap_buffer.hpp"
#include "domain/editor/mode/mode_enum.hpp"

namespace mini_vim::domain::editor {

class EditorState {
  private:
    buffer::GapBuffer terminalBuffer;
    buffer::GapBuffer commandBuffer;
    bool isRunning;
    mode::Mode mode;
    char keyPressed;

  public:
    EditorState();
    void setMode(mode::Mode mode);
    bool running();
    mode::Mode getMode();
    buffer::GapBuffer& getTerminalBuffer();
    buffer::GapBuffer& getCommandBuffer();
    char getKeyPressed() const;
    void setKeyPressed(char keyPressed);
    void killProcess();
    void getEvent();
};

};
