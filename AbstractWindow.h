#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <vector>
#include <unistd.h>

#include "Render.h"
#include "Event.h"

class MouseMotionEvent;
class MouseButtonEvent;
class CloseWindowEvent;
class MoveWindowEvent;
class ResizeWindowEvent;

class AbstractWindow {
public:
  AbstractWindow(const Rect& rect, bool is_shown);
  AbstractWindow() {}
  virtual ~AbstractWindow() {}

  virtual void OnRender(Renderer* renderer) const = 0;

  virtual bool OnMouseButton(MouseButtonEvent* event) = 0;
  virtual bool OnMouseMotion(MouseMotionEvent* event) = 0;
  virtual void OnClose() {}
  virtual void OnMove(MoveWindowEvent* event) {}

  bool PushEventToChildren(MouseButtonEvent* event);
  bool PushEventToChildren(MouseMotionEvent* event);

  void RenderChildren(Renderer* renderer) const;

  void AddChildren(AbstractWindow* children);
  void RemoveChildren(AbstractWindow* children);

  bool IsShown() const;
  void SetIsShown(bool is_shown);

  bool IsPressed() const;
  void SetIsPressed(bool is_pressed);

  size_t GetXPos() const;
  size_t GetYPos() const;
  void Move(int delta_x, int delta_y);

  size_t GetWidth() const;
  size_t GetHeight() const;

  virtual bool HitTest(int x, int y);

protected:
  Rect rect_;

  bool is_shown_;
  bool is_pressed_;

  std::vector<AbstractWindow*> childrens_;
};
