#include "Window.h"

Window::Window(const char* title) : window_(nullptr), title_(title), x0_(DEFAULT_X_POS), y0_(DEFAULT_Y_POS),
                   width_(DEFAULT_WIDTH), height_(DEFAULT_HEIGHT), flags_(DEFAULT_FLAGS) {
  window_ = SDL_CreateWindow(title_, x0_, y0_, width_, height_, flags_);

  assert(window_);
}

Window::Window(const Window& other) : window_(nullptr), title_(other.title_), x0_(other.x0_), y0_(other.y0_),
                                      width_(other.width_), height_(other.height_), flags_(other.flags_) {
  window_ = SDL_CreateWindow(title_, x0_, y0_, width_, height_, flags_);

  assert(window_);
}

Window::Window(const char* title, int x0, int y0, int width, int height, uint32_t flags)
      : window_(nullptr), title_(nullptr), x0_(x0), y0_(y0), width_(width), height_(height), flags_(flags) {
  assert(title);

  title_ = title;
  window_ = SDL_CreateWindow(title_, x0_, y0_, width_, height_, flags_);

  assert(window_);
}

Window::~Window() {
  assert(window_);

  SDL_DestroyWindow(window_);
}

Window& Window::operator=(const Window& other) {
  if (this == &other) {
    return *this;
  }

  title_  = other.title_;
  x0_     = other.x0_;
  y0_     = other.y0_;
  width_  = other.width_;
  height_ = other.height_;
  flags_  = other.flags_;
  window_ = SDL_CreateWindow(title_, x0_, y0_, width_, height_, flags_);
  assert(window_);

  return *this;
}

SDL_Window* Window::GetWindow() {
  assert(window_);

  return window_;
}

int Window::GetWidth() const {
  return width_;
}

int Window::GetHeight() const {
  return height_;
}
