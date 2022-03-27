#include "Palette.h"

Palette::Palette(Renderer* renderer, const Rect& palette_rect) {
  assert(renderer);

  texture_ = TEXTURE_MANAGER->GetTexture(PALETTE_TEXTURE_ID);
  rect_ = palette_rect;
  is_shown_ = true;

  for (int i = 0; i < NUMBER_OF_COLOR; ++i) {
    Texture* texture = TEXTURE_MANAGER->GetTexture(ColorID[i]);
    InsertColor(texture, COLORS[i]);
  }
}

void Palette::InsertColor(Texture* texture, const Color& color) {
  assert(texture);

  Rect rect;
  if (childrens_.size() % 2 == 0) {
    rect = {static_cast<int>(COLOR_X_POS + (childrens_.size()/2)*COLOR_WIDTH), COLOR_Y_POS, COLOR_WIDTH, COLOR_HEIGHT};
  } else {
    rect = {static_cast<int>(COLOR_X_POS + (childrens_.size()/2)*COLOR_WIDTH), COLOR_Y_POS + COLOR_HEIGHT - 2, COLOR_WIDTH, COLOR_HEIGHT};
  }
  Button<ChangeColorFunctor>* color_button = new Button<ChangeColorFunctor>(rect, true, ChangeColorFunctor(color), texture, NULL);
  AddChildren(color_button);
}
