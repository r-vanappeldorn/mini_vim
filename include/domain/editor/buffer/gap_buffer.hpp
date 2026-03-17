#pragma once

#include <string>
#include <vector>

namespace mini_vim::domain::editor::buffer {

class GapBuffer {
  private:
    std::vector<char> buffer;
    std::size_t gapStart;
    std::size_t gapEnd;
    void ensureGap(std::size_t need);
    void checkInvariants() const;

  public:
    explicit GapBuffer(std::size_t initialGap = 64);
    std::size_t size() const;
    std::size_t cursor() const;
    std::size_t capacity() const; 
    std::size_t gapSize() const; 
    void insert(char key);
    void insert(std::string_view key);
    bool backspace();
    bool del();
    void eraseBackspace();
    void eraseDelete();
    void moveLeft(std::size_t n = 1);
    void moveRight(std::size_t n = 1);
    void moveTo(std::size_t position);

    std::string toString() const;
};

}
