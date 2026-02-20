#pragma once

#include <atomic>
#include <sys/ioctl.h>
#include <termios.h>
#include <string>

namespace mini_vim::infra {

class Terminal final {
  public:
    Terminal();
    ~Terminal();

  private: 
    termios g_orig;
    struct winsize ws;
    std::atomic_bool g_resized{false};


    void enableRawMode();
    void disableRawMode();

  public:
    void die(std::string msg);

  Terminal(const Terminal&) = delete;
  Terminal& operator=(const Terminal) = delete;
};

};
