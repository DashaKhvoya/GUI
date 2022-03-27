#pragma once

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <unistd.h>

#include "AbstractWindow.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "Tool.h"
#include "Canvas.h"
#include "ScrollBar.h"

class CanvasManager;

template <class Functor>
class ScrollBar;

template <class Functor>
class Button : public AbstractWindow {
public:
  Button(const Rect& rect, bool is_shown, const Functor& functor, Texture* texture, Texture* neg_texture);
  virtual ~Button() override;

  virtual void OnRender(Renderer* renderer) const override;

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;

  void SetFunctor(Functor functor);

  virtual bool HitTest(int x, int y) override;

protected:
  Functor functor_;

  Texture* texture_;
  Texture* neg_texture_;
};

class ToDoNothingFunctor {
public:
  ToDoNothingFunctor() {}
  ~ToDoNothingFunctor() {}

  void operator()() {}
};

class SetToolFunctor {
public:
  SetToolFunctor(AbstractTool* tool) : tool_(tool) {}
  ~SetToolFunctor() {}

  void operator()();

private:
  AbstractTool* tool_;
};

class ChangeColorFunctor {
public:
  ChangeColorFunctor(Color color) : color_(color) {}
  ~ChangeColorFunctor() {}

  void operator()();

private:
  Color color_;
};

class CloseMainWindow {
public:
  CloseMainWindow(bool* run) : run_(run) {}
  ~CloseMainWindow() {}

  void operator()();

private:
  bool* run_;
};

class OpenAbstractWindowFunctor {
public:
  OpenAbstractWindowFunctor(Renderer* renderer, Rect rect, Manager* manager) : renderer_(renderer), rect_(rect), manager_(manager) {}
  ~OpenAbstractWindowFunctor() {}

  void operator()();

private:
  Renderer* renderer_;
  Rect rect_;
  Manager* manager_;
};

class CloseCanvasFunctor {
public:
  CloseCanvasFunctor(AbstractWindow* window) : window_(window) {}
  ~CloseCanvasFunctor() {}

  void operator()();

private:
  AbstractWindow* window_;
};

template <class Functor>
class ChangeScrollbarPosFunctor {
public:
  ChangeScrollbarPosFunctor(ScrollBar<Functor>* scrollbar, float delta) : scrollbar_(scrollbar), delta_(delta) {}
  ~ChangeScrollbarPosFunctor() {}

  void operator()();

private:
  ScrollBar<Functor>* scrollbar_;
  float delta_;
};

template<class Functor>
void ChangeScrollbarPosFunctor<Functor>::operator()() {
  if (scrollbar_->GetYPos() + delta_ >= SCROLLBAR_Y_POS && scrollbar_->GetYPos() + delta_ + scrollbar_->GetHeight() <= SCROLLBAR_Y_POS + SCROLLBAR_HEIGHT) {
    scrollbar_->SetY(delta_);
  }
}

template<class Functor>
Button<Functor>::Button(const Rect& rect, bool is_shown, const Functor& functor, Texture* texture, Texture* neg_texture)
    : AbstractWindow(rect, is_shown), functor_(functor), texture_(texture), neg_texture_(neg_texture) {}


template<class Functor>
Button<Functor>::~Button() {}

template<class Functor>
void Button<Functor>::OnRender(Renderer* renderer) const {
  assert(renderer);

  if (this->is_shown_) {
    if (this->is_pressed_ && neg_texture_ != NULL) {
      renderer->CopyTexture(neg_texture_, this->rect_);
    } else {
      renderer->CopyTexture(texture_, this->rect_);
    }
  }

  RenderChildren(renderer);
}

template<class Functor>
bool Button<Functor>::OnMouseButton(MouseButtonEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (!event->IsButtonPressed()) {
      functor_();

      SetIsPressed(IsPressed() == false);
    }

    return true;
  }

  return false;
}

template<class Functor>
bool Button<Functor>::OnMouseMotion(MouseMotionEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    return true;
  }

  return false;
}

template<class Functor>
void Button<Functor>::SetFunctor(Functor functor) {
  functor_ = functor;
}

template<class Functor>
bool Button<Functor>::HitTest(int x, int y) {
  return this->is_shown_ && this->rect_.x <= x && this->rect_.x + this->rect_.width >= x && this->rect_.y <= y && this->rect_.y + this->rect_.height >= y;
}
