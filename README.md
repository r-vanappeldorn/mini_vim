# mini_vim

`mini_vim` is a small experimental text editor written in **C++20**.

I started this project because I wanted to understand **how text editors
work under the hood**. Tools like Vim and Neovim feel almost magical in
how fast and responsive they are, and I wanted to explore the core
building blocks myself: buffers, rendering, input handling, and editor
modes.

This project is mainly a **learning exercise** focused on:

-   Understanding terminal input/output
-   Experimenting with text buffer implementations (e.g. gap buffer)
-   Implementing modal editing (normal / insert / command)
-   Structuring a small editor with a domain-oriented architecture

The project is built directly on **Linux terminal APIs**, so it
currently only targets Linux.

------------------------------------------------------------------------

# Features (Work in Progress)

-   Modal editing (Normal / Insert / Command)
-   Gap buffer implementation
-   Terminal rendering layer
-   Event handling system
-   Minimal editor state management

This project is still **work in progress** and mainly exists for
experimentation and learning.

------------------------------------------------------------------------

# Project Structure

    src/
      infra/
        terminal.cpp

      domain/
        editor/
          editor.cpp
          editor_state.cpp

          buffer/
            string_buffer.cpp
            gap_buffer.cpp

          mode/
            insert.cpp
            normal.cpp
            command.cpp
            mode_enum.cpp

        renderer/
          renderer.cpp

        events/
          event_manager.cpp

The codebase roughly separates responsibilities:

-   **infra** → system / terminal interaction
-   **domain** → editor logic
-   **renderer** → drawing to the terminal
-   **events** → input/event handling

------------------------------------------------------------------------

# Requirements

-   Linux
-   CMake ≥ 3.20
-   C++20 compatible compiler (tested with `clang` and `gcc`)

------------------------------------------------------------------------

# Build Instructions (Linux)

Clone the repository:

``` bash
git clone https://github.com/r-vanappeldorn/mini_vim.git
cd mini_vim
```

Configure the project with CMake:

``` bash
cmake -B build -S .
```

Build the project:

``` bash
cmake --build build
```

Run the editor:

``` bash
./build/mini_vim
```

------------------------------------------------------------------------

# Compiler Flags

The project uses strict compiler warnings:

    -Wall
    -Wextra
    -Wpedantic

These help keep the codebase clean and encourage good C++ practices.

------------------------------------------------------------------------

# Learning Goals

Some of the concepts explored in this project:

-   Gap buffer vs string buffer
-   Terminal raw mode
-   Key event processing
-   Editor modes
-   Rendering strategies
-   Editor architecture

------------------------------------------------------------------------

# License

MIT
