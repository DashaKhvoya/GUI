#pragma once

#include "AbstractWindow.h"
#include "Manager.h"
#include "Button.h"
#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "TextureManager.h"
#include "Canvas.h"
#include "Const.h"

extern bool run;

class Menu : public Manager {
public:
  Menu(Renderer* renderer, const char* name, const Rect& menu_rect);
  ~Menu() {}

  void InsertItem(const char* name, Renderer* renderer, Rect rect, Manager* manager);

  virtual bool OnMouseButton(MouseButtonEvent* event) override;
  virtual bool HitTest(int x, int y) override;
};

class MenuManager : public Manager {
public:
  MenuManager(Renderer* renderer);
  ~MenuManager() {}

  Menu* InsertMenu(Renderer* renderer, const char* name);
};
