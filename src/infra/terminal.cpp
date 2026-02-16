#include "infra/terminal.hpp"

#include <cerrno>
#include <iostream>

#include <termios.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

namespace mini_vim::infra {
  Terminal::Terminal() {
    this->enableRawMode();
  }

  Terminal::~Terminal() {
    this->disableRawMode();
  }

  void Terminal::die(std::string msg) {
    std::cerr << msg << ": " << strerror(errno) << std::endl;
      exit(1);
    }

  void Terminal::disableRawMode() { tcsetattr(STDIN_FILENO, TCSAFLUSH, &this->g_orig); }

  void Terminal::enableRawMode() {
    if (tcgetattr(STDIN_FILENO, &this->g_orig) == -1)
      this->die("tcgetattr");

    termios raw = this->g_orig;

    raw.c_lflag &= ~(ICANON | ECHO | ISIG);

    raw.c_iflag &= ~(IXON | ICRNL);

    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
      this->die("tcsetattr");
  }
};
