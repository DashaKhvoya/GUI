#pragma once

#include "AbstractWindow.h"
#include "Button.h"
#include "Manager.h"
#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "Tool.h"
#include "TextureManager.h"
#include "Const.h"

template <class Functor>
class ScrollBar : public AbstractWindow {
public:
  ScrollBar(Renderer* renderer, const Rect& rect, const Functor& functor);
  virtual ~ScrollBar() override;

  virtual void OnRender(Renderer* renderer) const override;

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;
  virtual void OnMove(MoveWindowEvent* event) override;

  void SetY(float delta_y);

private:
  Functor functor_;
  Texture* texture_;

  Texture* active_size_texture_;
  Rect active_size_rect_;

  int pre_y_;
};

class ChangeBrushSizeFunctor {
public:
  ChangeBrushSizeFunctor() {}
  ~ChangeBrushSizeFunctor() {}

  void operator()(float delta);
};

class ScrollBarManager : public Manager {
public:
  ScrollBarManager(Renderer* renderer, const Rect& manager_rect);
  ~ScrollBarManager() {}
};

template<class Functor>
ScrollBar<Functor>::ScrollBar(Renderer* renderer, const Rect& rect, const Functor& functor) {
  assert(renderer);

  texture_ = TEXTURE_MANAGER->GetTexture(SIZE_BUTTON_TEXTURE_ID);
  active_size_texture_ = new Texture(renderer, BEGIN_SIZE, BEGIN_SIZE);
  rect_ = rect;
  active_size_rect_ = {rect_.x + rect_.width + BEGIN_INDENT, rect_.y + (rect_.height - active_size_texture_->GetHeight())/2, active_size_texture_->GetWidth(), active_size_texture_->GetHeight()};
  is_shown_ = true;

  functor_ = functor;
}

template<class Functor>
ScrollBar<Functor>::~ScrollBar() {}

template<class Functor>
void ScrollBar<Functor>::OnRender(Renderer* renderer) const {
  assert(renderer);

  if (this->is_shown_) {
    renderer->CopyTexture(texture_, this->rect_);
    renderer->CopyTexture(active_size_texture_, {active_size_rect_.x, active_size_rect_.y, active_size_rect_.width/5, active_size_rect_.height/5});
  }
}

template<class Functor>
bool ScrollBar<Functor>::OnMouseButton(MouseButtonEvent* event) {
  assert(event);

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (event->IsButtonPressed()) {
      pre_y_ = event->GetMouseYPos();
      SetIsPressed(true);
    } else {
      SetIsPressed(false);
    }

    return true;
  }

  return false;
}

template<class Functor>
bool ScrollBar<Functor>::OnMouseMotion(MouseMotionEvent* event) {
  assert(event);

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (is_pressed_) {
      PostEvent(new MoveWindowEvent(event->GetMouseXPos(), event->GetMouseYPos(), this));
    }

    return true;
  }

  return false;
}

template<class Functor>
void ScrollBar<Functor>::OnMove(MoveWindowEvent* event) {
  int delta_y = event->GetNewYPos() - pre_y_;

  if (rect_.y + delta_y >= SCROLLBAR_Y_POS && rect_.y + delta_y + rect_.height <= SCROLLBAR_Y_POS + SCROLLBAR_HEIGHT) {
    SetY(delta_y);
    pre_y_ = event->GetNewYPos();
  }
}

template<class Functor>
void ScrollBar<Functor>::SetY(float delta_y) {
  rect_.y += delta_y;
  active_size_rect_.width  -= delta_y;
  active_size_rect_.height -= delta_y;
  active_size_rect_.y += delta_y;
  functor_(delta_y/5);
}
