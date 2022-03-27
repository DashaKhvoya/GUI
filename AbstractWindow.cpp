#include "AbstractWindow.h"

AbstractWindow::AbstractWindow(const Rect& rect, bool is_shown)
  : rect_(rect), is_shown_(is_shown), is_pressed_(false) {}

bool AbstractWindow::PushEventToChildren(MouseButtonEvent* event) {
  assert(event != nullptr);

  for (size_t i = 0; i < childrens_.size(); ++i) {
    bool is_consumed = childrens_[i]->OnMouseButton(event);
    if (is_consumed) {
      return true;
    }
  }

  return false;
}

bool AbstractWindow::PushEventToChildren(MouseMotionEvent* event) {
  assert(event != nullptr);

  for (size_t i = 0; i < childrens_.size(); ++i) {
    bool is_consumed = childrens_[i]->OnMouseMotion(event);
    if (is_consumed) {
      return true;
    }
  }

  return false;
}

void AbstractWindow::RenderChildren(Renderer* renderer) const {
  assert(renderer);

  for (int i = childrens_.size() - 1; i >= 0; --i) {
    childrens_[i]->OnRender(renderer);
  }
}

void AbstractWindow::AddChildren(AbstractWindow* children) {
  childrens_.push_back(children);
}

void AbstractWindow::RemoveChildren(AbstractWindow* children) {
  for (size_t i = 0; i < childrens_.size(); ++i) {
    if (childrens_[i] == children) {
      childrens_.pop_back();
      break;
    }
  }
}

bool AbstractWindow::IsShown() const {
  return is_shown_;
}

void AbstractWindow::SetIsShown(bool is_shown) {
  is_shown_ = is_shown;
}

bool AbstractWindow::IsPressed() const {
  return is_pressed_;
}

void AbstractWindow::SetIsPressed(bool is_pressed) {
  is_pressed_ = is_pressed;
}

size_t AbstractWindow::GetXPos() const {
  return rect_.x;
}

size_t AbstractWindow::GetYPos() const {
  return rect_.y;
}

size_t AbstractWindow::GetWidth() const {
  return rect_.width;
}

size_t AbstractWindow::GetHeight() const {
  return rect_.height;
}

bool AbstractWindow::HitTest(int x, int y) {
  return is_shown_ && rect_.x <= x && rect_.x + rect_.width >= x && rect_.y <= y && rect_.y + rect_.height >= y;
}

void AbstractWindow::Move(int delta_x, int delta_y) {
  rect_.x += delta_x;
  rect_.y += delta_y;
  for (size_t i = 0; i < childrens_.size(); ++i) {
    childrens_[i]->Move(delta_x, delta_y);
  }
}
