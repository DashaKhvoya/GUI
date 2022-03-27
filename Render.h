#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "Window.h"
#include "Texture.h"
#include "Const.h"

class Texture;
class Window;

enum RendererState {
  RENDERER_OK,
  SET_DRAW_COLOR_ERROR,
  CLEAR_ERROR,
  DRAW_LINE_ERROR,
  DRAW_PIXEL_ERROR,
  DRAW_RECTANGLE_ERROR,
  RENDER_TARGET_ERROR,
  RENDER_COPY_ERROR,
  OPEN_FONT_ERROR
};

struct Color;

struct Rect {
  int x;
  int y;
  int width;
  int height;
};

class Renderer {
public:
   Renderer(Window* window);
  ~Renderer();

  int  SetDrawColor(const Color& color);
  int  SetDrawFont(const char* font_path);
  int  SetRenderTarget(Texture* texture);

  void Present();
  int  Clear();

  int  DrawLine(int x1, int y1, int x2, int y2);
  int  DrawPixel(int x, int y);
  int  DrawRect(const Rect& rect);
  int  DrawFrame(const Rect& rect);
  void DrawText(const char* text, const Rect& rect, const Color& text_color);

  int CopyTexture(Texture* texture, const Rect& rect);

  SDL_Renderer* GetRenderer() const;

private:
  SDL_Renderer* renderer_;
  SDL_Window*   window_;

  SDL_Color     color_;
  TTF_Font*     font_;
};
