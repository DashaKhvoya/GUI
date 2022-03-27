#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <cstring>
#include <vector>
#include <unistd.h>

#include "AbstractWindow.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "Const.h"

class Manager : public AbstractWindow {
public:
  Manager(const Rect& rect, bool is_shown, Texture* texture);
  Manager() : AbstractWindow(), texture_(nullptr) {}
  virtual ~Manager() override;

  virtual void OnRender(Renderer* renderer) const override;

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool OnMouseMotion(MouseMotionEvent* event) override;
  virtual void OnClose() override;

protected:
  Texture* texture_;
  Texture* neg_texture_;
};
