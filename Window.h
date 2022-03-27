#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>

class Window {
public:
  Window(const char* title);
  Window(const Window& other);
  Window(const char* title, int x0, int y0, int width, int height, uint32_t flags);

  ~Window();

  Window& operator=(const Window& other);

  SDL_Window* GetWindow();

  int GetWidth()  const;

  int GetHeight() const;

private:
  static const int      DEFAULT_X_POS  = 100;
  static const int      DEFAULT_Y_POS  = 100;
  static const int      DEFAULT_WIDTH  = 1103;
  static const int      DEFAULT_HEIGHT = 846;
  static const uint32_t DEFAULT_FLAGS  = SDL_WINDOW_SHOWN;

  SDL_Window* window_;
  const char* title_;
  int         x0_;
  int         y0_;
  int         width_;
  int         height_;
  uint32_t    flags_;
};
