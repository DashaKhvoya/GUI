#include "Manager.h"

Manager::Manager(const Rect& rect, bool is_shown, Texture* texture)
  : AbstractWindow(rect, is_shown), texture_(texture), neg_texture_(nullptr) {}

Manager::~Manager() {}

void Manager::OnRender(Renderer* renderer) const {
  assert(renderer);

  if (is_shown_ && texture_ != nullptr) {
    for (int i = 0; i < rect_.width; i += texture_->GetWidth()) {
      for (int j = 0; j < rect_.height; j += texture_->GetHeight()) {
        Rect rect = {rect_.x + i, rect_.y + j, texture_->GetWidth(), texture_->GetHeight()};
        renderer->CopyTexture(texture_, rect);
      }
    }
  }

  RenderChildren(renderer);
}

bool Manager::OnMouseButton(MouseButtonEvent* event) {
  assert(event != nullptr);

  return PushEventToChildren(event);
}

bool Manager::OnMouseMotion(MouseMotionEvent* event) {
  assert(event != nullptr);

  return PushEventToChildren(event);
}

void Manager::OnClose() {
  childrens_.clear();
  is_shown_ = false;
}
