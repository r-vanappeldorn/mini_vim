#include "domain/editor/mode/mode_enum.hpp"

namespace mini_vim::domain::editor::mode {
std::string to_string(Mode mode)
{
    std::string result;
    
    switch (mode)
    {
      case Mode::Insert: result = "Insert";
            break;
      case Mode::Normal: result = "Normal";
            break;
    }

    return result;
}
}
