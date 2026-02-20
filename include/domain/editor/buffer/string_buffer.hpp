#pragma once

#include <string>

namespace mini_vim::domain::editor::buffer {
class StringBuffer {
  std::string content;

  public:
    StringBuffer();
    const std::string& contents() const;
    void insert(char c);
    void backspace();
    void newLine();
    void clear();
};
};;
