#pragma once

#include <termios.h>
#include <string>

namespace mini_vim::infra {

class Terminal final {
  public:
    Terminal();
    ~Terminal();

  private: 
    termios g_orig;

    void enableRawMode();
    void disableRawMode();

  public:
    void die(std::string msg);

  Terminal(const Terminal&) = delete;
  Terminal& operator=(const Terminal) = delete;
};

};
