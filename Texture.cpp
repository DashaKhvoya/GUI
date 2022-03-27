#include "Texture.h"

Texture::Texture(Renderer* renderer, int width, int height) {
  assert(renderer);

  renderer_ = renderer->GetRenderer();
  texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

  assert(texture_);
}

Texture::Texture(Renderer* renderer, const char* file) {
  renderer_ = renderer->GetRenderer();

  SDL_Surface* surface = IMG_Load(file);
  if (surface == NULL) {
    std::cout << "Error: file" << file << "not found" << std::endl;
    exit(0);
  }

  texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
  SDL_FreeSurface(surface);

  assert(texture_);
}

Texture::~Texture() {
  assert(texture_);
  SDL_DestroyTexture(texture_);
}

SDL_Texture* Texture::GetTexture() const {
  assert(texture_);

  return texture_;
}

int Texture::GetWidth() const {
  assert(texture_);

  int width = 0;
  SDL_QueryTexture(texture_, NULL, NULL, &width, NULL);
  return width;

}

int Texture::GetHeight() const {
  assert(texture_);

  int height = 0;
  SDL_QueryTexture(texture_, NULL, NULL, NULL, &height);
  return height;
}

void Texture::DrawLine(int x1, int y1, int x2, int y2) {
  assert(texture_);

  SDL_SetRenderTarget(renderer_, texture_);
  SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
  SDL_SetRenderTarget(renderer_, nullptr);
}

void Texture::DrawRect(const Rect& rect) {
  assert(texture_);

  SDL_Rect sdl_rect = {rect.x, rect.y, rect.width, rect.height};
  SDL_SetRenderTarget(renderer_, texture_);
  SDL_RenderFillRect(renderer_, &sdl_rect);
  SDL_SetRenderTarget(renderer_, nullptr);
}

void Texture::SetDrawColor(const Color& color) {
  assert(texture_);

  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
}

void Texture::Clear() {
  assert(texture_);

  SDL_RenderClear(renderer_);
}
