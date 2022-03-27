#include "AbstractWindow.h"
#include "Manager.h"
#include "Button.h"
#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "Const.h"
#include "ToolBar.h"
#include "Palette.h"
#include "Menu.h"
#include "Tool.h"
#include "Canvas.h"
#include "ScrollBar.h"
#include "TextureManager.h"

bool run = true;

int main() {
  SDL_Init(SDL_INIT_EVERYTHING);

  Window window("GUI");
  Renderer* renderer = new Renderer(&window);
  TEXTURE_MANAGER = new TextureManager(renderer);

  Manager main_window({WALL_X_POS, WALL_Y_POS, WALL_WIDTH, WALL_HEIGHT}, true, TEXTURE_MANAGER->GetTexture(WALL_TEXTURE_ID));

  Palette palette(renderer, {PALETTE_X_POS, PALETTE_Y_POS, PALETTE_WIDTH, PALETTE_HEIGHT});
  main_window.AddChildren(&palette);

  ToolBar tool_bar(renderer, {INSTRUMENT_X_POS, INSTRUMENT_Y_POS, INSTRUMENT_WIDTH, INSTRUMENT_HEIGHT});
  tool_bar.InsertDefaultTools();
  main_window.AddChildren(&tool_bar);

  MenuManager menu_manager(renderer);
  main_window.AddChildren(&menu_manager);

  ScrollBarManager scrollbar_manager(renderer, {SCROLLBAR_X_POS, SCROLLBAR_Y_POS, SCROLLBAR_WIDTH, SCROLLBAR_HEIGHT});
  main_window.AddChildren(&scrollbar_manager);

  while (run) {
    PumpEvents(&main_window);
    ApplicationEvents(&main_window);
    renderer->SetDrawColor(WHITE_COLOR);
    renderer->Clear();
    main_window.OnRender(renderer);
    renderer->Present();
  }
}
