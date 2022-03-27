#pragma once

#include "Window.h"
#include "Render.h"
#include "Texture.h"
#include "Event.h"
#include "Const.h"
#include "list"

class AbstractTool {
public:
  AbstractTool(const Color& color, float size);
  virtual ~AbstractTool() {}

  virtual void BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) = 0;
  virtual void Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) = 0;
  virtual void EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) = 0;

  float GetSize() const;
  void SetSize(float size);

  Color GetColor() const;
  void SetColor(Color color);

protected:
  Color color_;

  float size_;
};

class ToolManager {
public:
    ToolManager();
    ~ToolManager();

    std::list<AbstractTool*> GetTools() const;

    AbstractTool* GetActiveTool() const;
    void SetActiveTool(AbstractTool* tool);

    float GetActiveSize() const;
    void SetActiveSize(float size);

    void AddTool(AbstractTool* tool);
    void RemoveTool(AbstractTool* tool);

protected:
  std::list<AbstractTool*> tools_;
  AbstractTool* active_tool_;

  float active_size_;
};

extern ToolManager TOOL_MANAGER;

class BrushTool : public AbstractTool {
public:
  BrushTool(const Color& color, float size);
  virtual ~BrushTool() override;

  virtual void BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
  virtual void Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) override;
  virtual void EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
};

class PencilTool : public AbstractTool {
public:
  PencilTool(const Color& color);
  virtual ~PencilTool() override;

  virtual void BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
  virtual void Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) override;
  virtual void EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
};

class EraserTool : public AbstractTool {
public:
  EraserTool(float size);
  virtual ~EraserTool() override;

  virtual void BeginDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
  virtual void Draw(Texture* canvas, int mouse_x_begin, int mouse_y_begin, int mouse_x_end, int mouse_y_end) override;
  virtual void EndDraw(Texture* canvas, int mouse_x_pos, int mouse_y_pos) override;
};
