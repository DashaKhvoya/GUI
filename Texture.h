#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Render.h"

class Renderer;
struct Rect;
struct Color;

class Texture {
public:
  Texture(Renderer* renderer, int width, int height);
  Texture(Renderer* renderer, const char* file);
  ~Texture();

  SDL_Texture* GetTexture() const;

  int GetWidth() const;
  int GetHeight() const;

  void DrawLine(int x1, int y1, int x2, int y2);
  void DrawRect(const Rect& rect);

  void SetDrawColor(const Color& color);
  void Clear();

private:
  SDL_Texture*  texture_;
  SDL_Renderer* renderer_;
};
