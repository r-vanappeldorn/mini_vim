#pragma once

#include <string>
namespace mini_vim::domain::editor::mode {

enum class Mode : char {
  Insert,
  Normal
};

std::string to_string(Mode mode);

};
