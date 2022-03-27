#include "AbstractWindow.h"
#include "Manager.h"
#include "Button.h"
#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "TextureManager.h"
#include "Const.h"

class Palette : public Manager {
public:
  Palette(Renderer* renderer, const Rect& palette_rect);
  ~Palette() {}

  void InsertColor(Texture* texture, const Color& color);
};
