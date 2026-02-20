#include "infra/terminal.hpp"

#include <asm-generic/ioctls.h>
#include <cerrno>
#include <iostream>

#include <sys/ioctl.h>
#include <termios.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

namespace mini_vim::infra {

Terminal::Terminal() {
  this->enableRawMode();
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
}

Terminal::~Terminal() { this->disableRawMode(); }

void Terminal::die(std::string msg) {
  std::cerr << msg << ": " << strerror(errno) << std::endl;
  exit(1);
}

unsigned short Terminal::getRows() { return ws.ws_row; }

unsigned short Terminal::getColumns() { return ws.ws_col; }

void Terminal::disableRawMode() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &this->g_orig);
}

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
