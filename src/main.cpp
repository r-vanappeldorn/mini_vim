#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <cerrno>
#include <csignal>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

static termios g_orig;

static void disableRawMode() {
  tcsetattr(STDERR_FILENO, TCSAFLUSH, &g_orig);
}

static void die(string msg) {
  cerr << msg << ": " << strerror(errno) << endl;
  exit(1);
}

static void enableRawMode() {
  if (tcgetattr(STDERR_FILENO, &g_orig) == -1) die("tcsetattr");

  atexit(disableRawMode);

  termios raw = g_orig;

  raw.c_lflag &= ~(ICANON | ECHO | ISIG);
  
  raw.c_iflag &= ~(IXON | ICRNL);

  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcsetattr");
}

int main() {
  enableRawMode();

  cout << "Raw mode ON. Press 'q' to quit" << endl;

  string buffer = "";

  while(true) {
    char c;

    ssize_t n = read(STDERR_FILENO, &c, 1);
    if (n == -1) die("read");

    if (c == 'q') {
      cout << "\nExiting..." << endl;
      break;
    }

    if (c >= 32 && c <= 126) {
      buffer.push_back((int)(unsigned char)c);
    } 

    if (buffer.length() != 0 && c == 127)  {
      buffer.pop_back();
    }

    cout << buffer << endl;
  }

  return 0;
}
