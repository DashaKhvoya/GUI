#include "Button.h"

void SetToolFunctor::operator()() {
  TOOL_MANAGER.SetActiveTool(tool_);
}

void ChangeColorFunctor::operator()() {
  TOOL_MANAGER.GetActiveTool()->SetColor(color_);
}

void CloseMainWindow::operator()() {
  *run_ = false;
}

void OpenAbstractWindowFunctor::operator()() {
  manager_->AddChildren(new CanvasManager(renderer_, rect_));
}

void CloseCanvasFunctor::operator()() {
  PostEvent(new CloseWindowEvent(window_));
}
