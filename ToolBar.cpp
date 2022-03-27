#include "ToolBar.h"

ToolBar::ToolBar(Renderer* renderer, const Rect& toolbar_rect) {
  assert(renderer);

  texture_ = TEXTURE_MANAGER->GetTexture(TOOL_TEXTURE_ID);
  rect_ = toolbar_rect;
  is_shown_ = true;
}

void ToolBar::InsertTool(Texture* texture, Texture* neg_texture, AbstractTool* tool) {
  assert(texture);
  assert(neg_texture);

  Rect rect = {};
  if (childrens_.size() % 2 == 0) {
    rect = {INSTRUMENT_X_POS, static_cast<int>(INSTRUMENT_Y_POS + INSTRUMENT_HEIGHT + (childrens_.size()/2)*TOOL_HEIGHT), TOOL_WIDTH, TOOL_HEIGHT};
  } else {
    rect = {INSTRUMENT_X_POS + TOOL_WIDTH, static_cast<int>(INSTRUMENT_Y_POS + INSTRUMENT_HEIGHT + (childrens_.size()/2)*TOOL_HEIGHT), TOOL_WIDTH, TOOL_HEIGHT};
  }

  Button<SetToolFunctor>* tool_button = new Button<SetToolFunctor>(rect, true, SetToolFunctor(tool), texture, neg_texture);
  AddChildren(tool_button);
}

void ToolBar::InsertDefaultTools() {
  BrushTool* brush_tool = new BrushTool(BLACK_COLOR, TOOL_MANAGER.GetActiveSize());
  TOOL_MANAGER.AddTool(brush_tool);
  TOOL_MANAGER.SetActiveTool(brush_tool);
  Texture* brush_texture = TEXTURE_MANAGER->GetTexture(BRUSH_TEXTURE_ID);
  Texture* brush_neg_texture = TEXTURE_MANAGER->GetTexture(BRUSH_NEG_TEXTURE_ID);
  InsertTool(brush_texture, brush_neg_texture, brush_tool);

  EraserTool* eraser_tool = new EraserTool(TOOL_MANAGER.GetActiveSize());
  TOOL_MANAGER.AddTool(eraser_tool);
  Texture* eraser_texture = TEXTURE_MANAGER->GetTexture(ERASER_TEXTURE_ID);
  Texture* eraser_neg_texture = TEXTURE_MANAGER->GetTexture(ERASER_NEG_TEXTURE_ID);
  InsertTool(eraser_texture, eraser_neg_texture, eraser_tool);

  PencilTool* pencil_tool = new PencilTool(BLACK_COLOR);
  TOOL_MANAGER.AddTool(pencil_tool);
  Texture* pencil_texture = TEXTURE_MANAGER->GetTexture(PENCIL_TEXTURE_ID);
  Texture* pencil_neg_texture = TEXTURE_MANAGER->GetTexture(PENCIL_NEG_TEXTURE_ID);
  InsertTool(pencil_texture, pencil_neg_texture, pencil_tool);

  last_pressed_button_ = childrens_[0];
  childrens_[0]->SetIsPressed(true);
}

bool ToolBar::OnMouseButton(MouseButtonEvent* event) {
  assert(event);

  for (size_t i = 0; i < childrens_.size(); ++i) {
    bool is_consumed = childrens_[i]->OnMouseButton(event);
    if (is_consumed) {
      if (last_pressed_button_ != childrens_[i]) {
        last_pressed_button_->SetIsPressed(false);
        last_pressed_button_ = childrens_[i];
      } else {
        last_pressed_button_->SetIsPressed(true);
      }

      return true;
    }
  }

  return false;
}
