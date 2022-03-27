#include "Canvas.h"

CanvasManager::CanvasManager(Renderer* renderer, const Rect& manager_rect) {
  assert(renderer);

  texture_ = TEXTURE_MANAGER->GetTexture(CANVAS_MANAGER_TEXTURE_ID);
  rect_ = manager_rect;
  is_shown_ = true;

  Rect close_rect = {manager_rect.x + CANVAS_CLOSE_X_INDENT, manager_rect.y + CANVAS_CLOSE_Y_INDENT, CANVAS_CLOSE_WIDTH, CANVAS_CLOSE_HEIGHT};
  Texture* close_texture = TEXTURE_MANAGER->GetTexture(CANVAS_CLOSE_TEXTURE_ID);
  Button<CloseCanvasFunctor>* close_button = new Button<CloseCanvasFunctor>(close_rect, true, CloseCanvasFunctor(this), close_texture, nullptr);
  AddChildren(close_button);

  renderer->SetDrawColor(WHITE_COLOR);
  Rect rect = {manager_rect.x + 1, manager_rect.y + manager_rect.height, CANVAS_WIDTH, CANVAS_HEIGHT};
  Texture* canvas_texture = new Texture(renderer, rect.width, rect.height);
  renderer->SetRenderTarget(canvas_texture);
  renderer->Clear();
  Canvas* canvas = new Canvas(rect, true, canvas_texture);
  AddChildren(canvas);
  renderer->SetRenderTarget(nullptr);

  Rect canvas_img_rect = {manager_rect.x, manager_rect.y + manager_rect.height - 1, CANVAS_IMG_WIDTH, CANVAS_IMG_HEIGHT};
  Texture* canvas_img_texture = TEXTURE_MANAGER->GetTexture(CANVAS_ID);
  Button<ToDoNothingFunctor>* canvas_img = new Button<ToDoNothingFunctor>(canvas_img_rect, true, ToDoNothingFunctor(), canvas_img_texture, nullptr);
  AddChildren(canvas_img);
}

bool CanvasManager::OnMouseButton(MouseButtonEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (event->IsButtonPressed()) {
      pre_x_ = event->GetMouseXPos();
      pre_y_ = event->GetMouseYPos();
      SetIsPressed(true);
    } else {
      SetIsPressed(false);
    }

    return true;
  }

  return false;
}

bool CanvasManager::OnMouseMotion(MouseMotionEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (is_pressed_) {
      PostEvent(new MoveWindowEvent(event->GetMouseXPos(), event->GetMouseYPos(), this));
    }

    return true;
  }

  return false;
}

void CanvasManager::OnMove(MoveWindowEvent* event) {
  int delta_x = event->GetNewXPos() - pre_x_;
  int delta_y = event->GetNewYPos() - pre_y_;

  if ( rect_.x + delta_x >= INSTRUMENT_X_POS + INSTRUMENT_WIDTH && rect_.x + delta_x + rect_.width <= EXAMPLE_X_POS + EXAMPLE_WIDTH
    && rect_.y + delta_y >= EXAMPLE_Y_POS + EXAMPLE_HEIGHT && rect_.y + delta_y + rect_.height + CANVAS_HEIGHT <= PALETTE_Y_POS) {
    Move(delta_x, delta_y);
    pre_x_ = event->GetNewXPos();
    pre_y_ = event->GetNewYPos();
  }
}

Canvas::Canvas(const Rect& rect, bool is_shown, Texture* texture)
  : AbstractWindow(rect, is_shown), texture_(texture) {}

Canvas::~Canvas() {}

void Canvas::OnRender(Renderer* renderer) const {
  assert(renderer);

  if (this->is_shown_) {
    renderer->CopyTexture(texture_, this->rect_);
  }
}

bool Canvas::OnMouseButton(MouseButtonEvent* event) {
  assert(event);

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (event->IsButtonPressed()) {
      pre_x_ = event->GetMouseXPos();
      pre_y_ = event->GetMouseYPos();
      TOOL_MANAGER.GetActiveTool()->BeginDraw(texture_, event->GetMouseXPos() - rect_.x, event->GetMouseYPos() - rect_.y);
      SetIsPressed(true);
    } else {
      TOOL_MANAGER.GetActiveTool()->EndDraw(texture_, event->GetMouseXPos() - rect_.x, event->GetMouseYPos() - rect_.y);
      SetIsPressed(false);
    }

    return true;
  }

  return false;
}

bool Canvas::OnMouseMotion(MouseMotionEvent* event) {
  assert(event);

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (is_pressed_) {
      TOOL_MANAGER.GetActiveTool()->Draw(texture_, pre_x_ - rect_.x, pre_y_ - rect_.y, event->GetMouseXPos() - rect_.x, event->GetMouseYPos() - rect_.y);
      pre_x_ = event->GetMouseXPos();
      pre_y_ = event->GetMouseYPos();
    }

    return true;
  }

  return false;
}

bool Canvas::HitTest(int x, int y) {
  return this->is_shown_ && this->rect_.x <= x && this->rect_.x + this->rect_.width >= x && this->rect_.y <= y && this->rect_.y + this->rect_.height >= y;
}

bool CanvasManagerManager::OnMouseButton(MouseButtonEvent* event) {
  assert(event);

  for (size_t i = 0; i < childrens_.size(); ++i) {
    if (childrens_[i]->OnMouseButton(event)) {
      AbstractWindow* temp_children = childrens_[i];
      for (size_t j = i; j != 0; --j) {
        childrens_[j] = childrens_[j - 1];
      }
      childrens_[0] = temp_children;
      return true;
    }
  }

  return false;
}

bool CanvasManagerManager::OnMouseMotion(MouseMotionEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  return false;
}
