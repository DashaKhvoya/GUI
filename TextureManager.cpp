#include "TextureManager.h"

TextureManager* TEXTURE_MANAGER = nullptr;

TextureManager::TextureManager(Renderer* renderer) {
  for (size_t i = 0; i < NUMBER_OF_TEXTURES; ++i) {
    textures_.push_back(new Texture(renderer, TEXTURES[i]));
  }
}

TextureManager::~TextureManager() {
  textures_.clear();
}

Texture* TextureManager::GetTexture(size_t texture_id) {
  return textures_[texture_id];
}
