#include "domain/editor/buffer/string_buffer.hpp"

namespace mini_vim::domain::editor::buffer {

StringBuffer::StringBuffer() {
  content = "";
}

const std::string& StringBuffer::contents() const {
  return content;
}

void StringBuffer::insert(char c) {
  content.push_back(c);
};

void StringBuffer::newLine() {
  content.push_back('\n');
}

void StringBuffer::backspace() {
  content.pop_back();
}

void StringBuffer::clear() {
  content.clear();
}
};
