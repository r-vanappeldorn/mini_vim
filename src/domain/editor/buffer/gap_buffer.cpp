#include "domain/editor/buffer/gap_buffer.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string_view>
#include <vector>

namespace mini_vim::domain::editor::buffer {

GapBuffer::GapBuffer(std::size_t initailGap) : buffer(initailGap, '\0'), gapStart(0), gapEnd(initailGap) {}

std::size_t GapBuffer::size() const {
  return buffer.size() - gapSize();
}

std::size_t GapBuffer::cursor() const {
  return gapStart;
}

std::size_t GapBuffer::capacity() const {
  return buffer.size();
}

std::size_t GapBuffer::gapSize() const {
  return gapEnd - gapStart;
}

void GapBuffer::insert(char key) {
  ensureGap(1);
  buffer[gapStart++] = key;
  checkInvariants();
}

void GapBuffer::insert(std::string_view view) {
  ensureGap(view.size());
  for (char c : view) buffer[gapStart++] = c;
  checkInvariants();
}

bool GapBuffer::backspace() {
  if (gapStart == 0) return false;
  --gapStart;
  checkInvariants();

  return true;
}

bool GapBuffer::del() {
  if (gapStart == 0) return false;
  gapEnd++;
  checkInvariants();
  
  return true;
}

void GapBuffer::moveLeft(std::size_t n) {
  while (n-- > 0 && gapStart > 0) {
    buffer[gapEnd - 1] = buffer[gapStart -1];
    --gapStart;
    --gapEnd;
  }
  checkInvariants();
}

void GapBuffer::moveRight(std::size_t n) {
  while (n-- > 0 && gapEnd < buffer.size()) {
    buffer[gapStart] = buffer[gapEnd];
    ++gapStart;
    ++gapEnd;
  }
  checkInvariants();
}

void GapBuffer::moveTo(std::size_t position) {
  position = std::min(position, size());
  while (cursor() > position) moveLeft(1);
  while (cursor() < position) moveRight(1);
}

std::string GapBuffer::toString() const {
  std::string out;
  out.reserve(size());
  out.append(buffer.data(), buffer.data() + gapStart);
  out.append(buffer.data() + gapEnd, buffer.data() + buffer.size());

  return out;
}

void GapBuffer::ensureGap(std::size_t need) {
  if (gapSize() >= need) return;

  const std::size_t oldCap = buffer.size();
  const std::size_t newCap = std::max(oldCap * 2, oldCap + need + 64);

  std::vector<char> newBuffer(newCap, '\0');
  std::copy(buffer.begin(), buffer.begin() + gapStart, newBuffer.begin());

  const std::size_t rightLen = oldCap - gapEnd;
  const std::size_t newGapEnd = newCap - rightLen;

  std::copy(buffer.begin() + gapEnd, buffer.end(), newBuffer.begin() + newGapEnd);
  buffer.swap(newBuffer);
  gapEnd = newGapEnd;

  checkInvariants();
}

void GapBuffer::checkInvariants() const {
  assert(gapStart <= gapEnd);
  assert(gapEnd <= buffer.size());
}

};
