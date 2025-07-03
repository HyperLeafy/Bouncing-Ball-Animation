# 🎈 SDL3 Bouncing Ball Animation

A minimal animation demo using **SDL3** written in **C++17** — built using standard lifecycle callbacks (`SDL_AppInit`, `SDL_AppIterate`, etc.).

---

## 🛠️ Requirements

- C++17 compatible compiler (e.g., `g++`)
- [SDL3](https://github.com/libsdl-org/SDL) installed on your system

Tested on **Fedora Linux 42** using system-installed SDL3.

---

## 🚀 Build Instructions

Just compile it directly (no Make or CMake required):

```bash
g++ -std=c++17 -g -o bouncing_ball main.cxx -lSDL3
