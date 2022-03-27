#include "ScrollBar.h"

ScrollBarManager::ScrollBarManager(Renderer* renderer, const Rect& manager_rect) {
    assert(renderer);

    texture_ = TEXTURE_MANAGER->GetTexture(SCROLLBAR_TEXTURE_ID);
    rect_ = manager_rect;
    is_shown_ = true;

    Rect scrollbar_rect = {manager_rect.x, manager_rect.y + manager_rect.height - SIZE_BUTTON_HEIGHT, SIZE_BUTTON_WIDTH, SIZE_BUTTON_HEIGHT};
    ScrollBar<ChangeBrushSizeFunctor>* scrollbar = new ScrollBar<ChangeBrushSizeFunctor>(renderer, scrollbar_rect, ChangeBrushSizeFunctor());
    AddChildren(scrollbar);

    Rect up_rect = {manager_rect.x, manager_rect.y - UP_HEIGHT, UP_WIDTH, UP_HEIGHT};
    Texture* up_texture = TEXTURE_MANAGER->GetTexture(UP_TEXTURE_ID);
    Button<ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>>* up_button = new Button<ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>>(up_rect, true, ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>(scrollbar, -5), up_texture, nullptr);
    AddChildren(up_button);

    Rect down_rect = {manager_rect.x, manager_rect.y + manager_rect.height, DOWN_WIDTH, DOWN_HEIGHT};
    Texture* down_texture = TEXTURE_MANAGER->GetTexture(DOWN_TEXTURE_ID);
    Button<ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>>* down_button = new Button<ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>>(down_rect, true, ChangeScrollbarPosFunctor<ChangeBrushSizeFunctor>(scrollbar, 5), down_texture, nullptr);
    AddChildren(down_button);
  }

void ChangeBrushSizeFunctor::operator()(float delta) {
  TOOL_MANAGER.SetActiveSize(TOOL_MANAGER.GetActiveSize() - delta);
}
