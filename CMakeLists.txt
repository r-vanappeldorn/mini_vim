cmake_minimum_required(VERSION 3.20)
project(mini_vim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mini_vim
  src/main.cpp
  src/infra/terminal.cpp
  src/domain/editor/editor.cpp
  src/domain/editor/editor_state.cpp
  src/domain/editor/buffer/string_buffer.cpp
  src/domain/editor/mode/insert.cpp
)

target_include_directories(mini_vim PRIVATE include)
target_compile_options(mini_vim PRIVATE -Wall -Wextra -Wpedantic)

