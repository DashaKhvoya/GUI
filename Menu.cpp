#include "Menu.h"

Menu::Menu(Renderer* renderer, const char* name, const Rect& menu_rect) {
  assert(renderer);

  renderer->SetDrawColor(WHITE_COLOR);
  renderer->SetDrawFont(FONT_TTF_WAY);
  texture_ = new Texture(renderer, menu_rect.width, menu_rect.height);
  renderer->SetRenderTarget(texture_);
  renderer->Clear();
  renderer->DrawText(name, {0, BEGIN_INDENT, menu_rect.width - LEFT_INDENT, menu_rect.height - BEGIN_INDENT}, BLACK_COLOR);

  renderer->SetDrawColor(BLACK_COLOR);
  neg_texture_ = new Texture(renderer, menu_rect.width, menu_rect.height);
  renderer->SetRenderTarget(neg_texture_);
  renderer->Clear();
  renderer->DrawText(name, {0, BEGIN_INDENT, menu_rect.width - LEFT_INDENT, menu_rect.height - BEGIN_INDENT}, WHITE_COLOR);
  renderer->SetRenderTarget(nullptr);

  rect_ = menu_rect;
  is_shown_ = true;
}

void Menu::InsertItem(const char* name, Renderer* renderer, Rect window_rect, Manager* manager) {
  assert(renderer);

  Rect button_rect = {rect_.x, static_cast<int>(rect_.y + (childrens_.size() + 1)*rect_.height), rect_.width, rect_.height};
  renderer->SetDrawColor(WHITE_COLOR);
  Texture* texture = new Texture(renderer, button_rect.width, button_rect.height);
  renderer->SetRenderTarget(texture);
  renderer->Clear();
  renderer->DrawText(name, {0, BEGIN_INDENT, button_rect.width - LEFT_INDENT, button_rect.height - BEGIN_INDENT}, BLACK_COLOR);
  renderer->SetRenderTarget(nullptr);

  Button<OpenAbstractWindowFunctor>* button = new Button<OpenAbstractWindowFunctor>(button_rect, false, OpenAbstractWindowFunctor(renderer, window_rect, manager), texture, nullptr);
  button->SetIsShown(false);
  AddChildren(button);
}

bool Menu::OnMouseButton(MouseButtonEvent* event) {
  assert(event != nullptr);

  bool is_consumed = PushEventToChildren(event);
  if (is_consumed) {
    return true;
  }

  if (HitTest(event->GetMouseXPos(), event->GetMouseYPos())) {
    if (!event->IsButtonPressed()) {
      Texture* temp_texture = texture_;
      texture_ = neg_texture_;
      neg_texture_ = temp_texture;

      for (size_t i = 0; i < childrens_.size(); ++i) {
        childrens_[i]->SetIsShown(childrens_[i]->IsShown() == false);
      }
    }

    return true;
  }

  return false;
}

bool Menu::HitTest(int x, int y) {
  return is_shown_ && rect_.x <= x && rect_.x + rect_.width >= x && rect_.y <= y && rect_.y + rect_.height >= y;
}

MenuManager::MenuManager(Renderer* renderer) {
  assert(renderer);

  texture_ = TEXTURE_MANAGER->GetTexture(EXAMPLE_TEXTURE_ID);
  rect_ = {EXAMPLE_X_POS, EXAMPLE_Y_POS, EXAMPLE_WIDTH, EXAMPLE_HEIGHT};
  is_shown_ = true;

  Menu* file_menu = InsertMenu(renderer, "File");
  InsertMenu(renderer, "Edit");
  CanvasManagerManager* manager = new CanvasManagerManager();
  AddChildren(manager);
  file_menu->InsertItem("New", renderer, {CANVAS_MANAGER_X_POS, CANVAS_MANAGER_Y_POS, CANVAS_MANAGER_WIDTH, CANVAS_MANAGER_HEIGHT}, manager);

  Rect apple_rect = {rect_.x, rect_.y, ICON_WIDTH, ICON_HEIGHT};
  Texture* apple_texture = TEXTURE_MANAGER->GetTexture(ICON_TEXTURE_ID);
  Button<ToDoNothingFunctor>* button = new Button<ToDoNothingFunctor>(apple_rect, true, ToDoNothingFunctor(), apple_texture, nullptr);
  AddChildren(button);

  Rect close_rect = {rect_.x + rect_.width - CLOSE_WIDTH - BEGIN_INDENT, rect_.y + BEGIN_INDENT, CLOSE_WIDTH, CLOSE_HEIGHT};
  Texture* close_texture = TEXTURE_MANAGER->GetTexture(CLOSE_TEXTURE_ID);
  Button<CloseMainWindow>* close_button = new Button<CloseMainWindow>(close_rect, true, CloseMainWindow(&run), close_texture, nullptr);
  AddChildren(close_button);

  Rect minus_rect = {close_rect.x - MINUS_WIDTH - BEGIN_INDENT, close_rect.y + BEGIN_INDENT, MINUS_WIDTH, MINUS_HEIGHT};
  Texture* minus_texture = TEXTURE_MANAGER->GetTexture(MINUS_TEXTURE_ID);
  Button<ToDoNothingFunctor>* minus_button = new Button<ToDoNothingFunctor>(minus_rect, true, ToDoNothingFunctor(), minus_texture, nullptr);
  AddChildren(minus_button);
}

Menu* MenuManager::InsertMenu(Renderer* renderer, const char* name) {
  assert(renderer);
  Menu* menu = new Menu(renderer, name, {static_cast<int>(rect_.x + ICON_WIDTH + TOP_INDENT + childrens_.size()*MENU_WIDTH), rect_.y, MENU_WIDTH, MENU_HEIGHT});
  AddChildren(menu);

  return menu;
}
