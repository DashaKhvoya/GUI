#pragma once

#include "AbstractWindow.h"
#include "Manager.h"
#include "Button.h"
#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "TextureManager.h"
#include "Const.h"

class ToolBar : public Manager {
public:
  ToolBar(Renderer* renderer, const Rect& toolbar_rect);
  ~ToolBar() {}

  void InsertTool(Texture* texture, Texture* neg_texture, AbstractTool* tool);
  void InsertDefaultTools();
  
  virtual bool OnMouseButton(MouseButtonEvent* event) override;

private:
  AbstractWindow* last_pressed_button_;
};
