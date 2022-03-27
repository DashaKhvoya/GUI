#pragma once

#include "Render.h"
#include "Texture.h"
#include "Const.h"

class TextureManager {
public:
  TextureManager(Renderer* renderer);
  ~TextureManager();

  Texture* GetTexture(size_t texture_id);
protected:
  std::vector<Texture*> textures_;
};

extern TextureManager* TEXTURE_MANAGER;
