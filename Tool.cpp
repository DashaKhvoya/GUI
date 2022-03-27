#include "Tool.h"

ToolManager TOOL_MANAGER {};

AbstractTool::AbstractTool(const Color& color, float size)
  : color_(color), size_(size) {}

float AbstractTool::GetSize() const {
  return size_;
}

void AbstractTool::SetSize(float size) {
  size_ = size;
  TOOL_MANAGER.SetActiveSize(size);
}

Color AbstractTool::GetColor() const {
  return color_;
}

void AbstractTool::SetColor(Color color) {
  color_ = color;
}

ToolManager::ToolManager() : active_size_(1) {}

ToolManager::~ToolManager() { tools_.clear(); }

std::list<AbstractTool*> ToolManager::GetTools() const {
  return tools_;
}

AbstractTool* ToolManager::GetActiveTool() const {
  return active_tool_;
}

void ToolManager::SetActiveTool(AbstractTool* tool) {
  active_tool_ = tool;
}

float ToolManager::GetActiveSize() const {
  return active_size_;
}

void ToolManager::SetActiveSize(float size) {
  active_size_ = size;
}

void ToolManager::AddTool(AbstractTool* tool) {
  tools_.push_back(tool);
}

void ToolManager::RemoveTool(AbstractTool* tool) {
  tools_.remove(tool);
}

BrushTool::BrushTool(const Color& color, float size) : AbstractTool(color, size) {}

BrushTool::~BrushTool() {}

void BrushTool::BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  size_ = TOOL_MANAGER.GetActiveSize();
  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos - size_/2), static_cast<int>(mouse_y_pos - size_/2), static_cast<int>(size_), static_cast<int>(size_)};
  canvas->DrawRect(rect);
}

void BrushTool::Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  int delta_x = mouse_x_end - mouse_x_begin;
  int delta_y = mouse_y_end - mouse_y_begin;
  for (int i = static_cast<int>(mouse_x_begin - size_/2); i <= static_cast<int>(mouse_x_begin + size_/2); ++i) {
    for (int j = static_cast<int>(mouse_y_begin - size_/2); j <= static_cast<int>(mouse_y_begin + size_/2); ++j) {
      canvas->DrawLine(i, j, i + delta_x, j + delta_y);
    }
  }
}

void BrushTool::EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos - size_/2), static_cast<int>(mouse_y_pos - size_/2), static_cast<int>(size_), static_cast<int>(size_)};

  canvas->DrawRect(rect);
}

PencilTool::PencilTool(const Color& color) : AbstractTool(color, 1) {}

PencilTool::~PencilTool() {}

void PencilTool::BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos), static_cast<int>(mouse_y_pos), static_cast<int>(size_), static_cast<int>(size_)};
  canvas->DrawRect(rect);
}

void PencilTool::Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  canvas->DrawLine(mouse_x_begin, mouse_y_begin, mouse_x_end, mouse_y_end);
}

void PencilTool::EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos), static_cast<int>(mouse_y_pos), static_cast<int>(size_), static_cast<int>(size_)};

  canvas->DrawRect(rect);
}

EraserTool::EraserTool(float size) : AbstractTool(WHITE_COLOR, size) {}

EraserTool::~EraserTool() {}

void EraserTool::BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  size_ = TOOL_MANAGER.GetActiveSize();
  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos - size_/2), static_cast<int>(mouse_y_pos - size_/2), static_cast<int>(size_), static_cast<int>(size_)};
  canvas->DrawRect(rect);
}

void EraserTool::Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  int delta_x = mouse_x_end - mouse_x_begin;
  int delta_y = mouse_y_end - mouse_y_begin;
  for (int i = static_cast<int>(mouse_x_begin - size_/2); i <= static_cast<int>(mouse_x_begin + size_/2); ++i) {
    for (int j = static_cast<int>(mouse_y_begin - size_/2); j <= static_cast<int>(mouse_y_begin + size_/2); ++j) {
      canvas->DrawLine(i, j, i + delta_x, j + delta_y);
    }
  }
}

void EraserTool::EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) {
  assert(canvas);

  canvas->SetDrawColor(color_);
  canvas->Clear();
  Rect rect = {static_cast<int>(mouse_x_pos - size_/2), static_cast<int>(mouse_y_pos - size_/2), static_cast<int>(size_), static_cast<int>(size_)};

  canvas->DrawRect(rect);
}
