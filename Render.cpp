#include "Render.h"

Renderer::Renderer(Window* window) : font_(NULL) {
  assert(window);

  window_ = window->GetWindow();
  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  assert(renderer_);
}

Renderer::~Renderer() {
  assert(renderer_);

  SDL_DestroyRenderer(renderer_);
  TTF_CloseFont(font_);
}

int Renderer::SetDrawColor(const Color& color) {
  assert(renderer_);

  if (SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a) < 0) {
      printf("SetDrawColor failed: %s\n", SDL_GetError());
      return SET_DRAW_COLOR_ERROR;
  }

  color_.r = color.r;
  color_.g = color.g;
  color_.b = color.b;
  color_.a = color.a;

  return RENDERER_OK;
}

int Renderer::SetDrawFont(const char* font_path) {
  assert(renderer_);
  assert(font_path);
  TTF_Init();
  font_ = TTF_OpenFont(font_path, 64);
  if (font_ == NULL) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    return OPEN_FONT_ERROR;
  }

  return RENDERER_OK;
}

int Renderer::SetRenderTarget(Texture* texture) {
  assert(renderer_);

  if (texture == nullptr) {
    SDL_SetRenderTarget(renderer_, nullptr);
    return RENDERER_OK;
  }

  if (SDL_SetRenderTarget(renderer_, texture->GetTexture()) < 0) {
    printf("Render Target failed: %s\n", SDL_GetError());
    return RENDER_TARGET_ERROR;
  }

  return RENDERER_OK;
}

void Renderer::Present() {
  assert(renderer_);

  SDL_RenderPresent(renderer_);
}

int Renderer::Clear() {
  assert(renderer_);

  if (SDL_RenderClear(renderer_) < 0) {
    printf("Clear failed: %s\n", SDL_GetError());
    return CLEAR_ERROR;
  }

  return RENDERER_OK;
}

int Renderer::DrawLine(int x1, int y1, int x2, int y2) {
  assert(renderer_);

  if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) < 0) {
    printf("DrawLine failed: %s\n", SDL_GetError());
    return DRAW_LINE_ERROR;
  }

  return RENDERER_OK;
}

int Renderer::DrawPixel(int x, int y) {
  assert(renderer_);

  if (SDL_RenderDrawPoint(renderer_, x, y) < 0) {
    printf("DrawPixel failed: %s\n", SDL_GetError());
    return DRAW_PIXEL_ERROR;
  }

  return RENDERER_OK;
}

int Renderer::DrawRect(const Rect& rect) {
  assert(renderer_);

  SDL_Rect sdl_rect = {rect.x, rect.y, rect.width, rect.height};
  if (SDL_RenderFillRect(renderer_, &sdl_rect) < 0) {
    printf("DrawRectangle failed: %s\n", SDL_GetError());
    return DRAW_RECTANGLE_ERROR;
  }

  return RENDERER_OK;
}

int Renderer::DrawFrame(const Rect& rect) {
  assert(renderer_);

  SDL_Rect sdl_rect = {rect.x, rect.y, rect.width, rect.height};
  if (SDL_RenderDrawRect(renderer_, &sdl_rect) < 0) {
    printf("DrawRectangle failed: %s\n", SDL_GetError());
    return DRAW_RECTANGLE_ERROR;
  }

  return RENDERER_OK;
}

void Renderer::DrawText(const char* text, const Rect& rect, const Color& text_color) {
  assert(renderer_);

  SDL_Color color = { text_color.r, text_color.g, text_color.b, text_color.a };
  SDL_Surface* surface = TTF_RenderText_Blended(font_, text, color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);

  SDL_Rect sdl_rect = {rect.x, rect.y, rect.width, rect.height};
  SDL_RenderCopy(renderer_, texture, NULL, &sdl_rect);

  SDL_FreeSurface(surface);
}

int Renderer::CopyTexture(Texture* texture, const Rect& rect) {
  SDL_Rect sdl_rect = { rect.x, rect.y, rect.width, rect.height };

  if (SDL_RenderCopy(renderer_, texture->GetTexture(), NULL, &sdl_rect) < 0) {
    printf("RenderCopy failed: %s\n", SDL_GetError());
    return RENDER_COPY_ERROR;
  }

  return RENDERER_OK;
}

SDL_Renderer* Renderer::GetRenderer() const {
  return renderer_;
}
