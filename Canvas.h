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

class Canvas : public AbstractWindow {
public:
  Canvas(const Rect& rect, bool is_shown, Texture* texture);
  virtual ~Canvas() override;

  virtual void OnRender(Renderer* renderer) const override;

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;

  virtual bool HitTest(int x, int y) override;

private:
  Texture* texture_;

  int pre_x_;
  int pre_y_;
};

class CanvasManager : public Manager {
public:
  CanvasManager(Renderer* renderer, const Rect& manager_rect);
  ~CanvasManager() {}

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;
  virtual void OnMove(MoveWindowEvent* event) override;

private:
  int pre_x_;
  int pre_y_;
};

class CanvasManagerManager : public Manager {
public:
  CanvasManagerManager() {}
  ~CanvasManagerManager() {}

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;
};
