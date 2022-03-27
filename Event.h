#pragma once

#include <cassert>
#include <cstdint>
#include <cmath>
#include <vector>
#include <queue>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "AbstractWindow.h"

class AbstractWindow;

enum EventType {
  MOUSE_MOTION,
  MOUSE_BUTTON,
  WINDOW_CLOSE,
  WINDOW_MOVE
};

class AbstractEvent {
public:
  AbstractEvent(int type);
  virtual ~AbstractEvent() {}

  int GetType() const;

protected:
  int type_;
};

class MouseMotionEvent : public AbstractEvent {
public:
  MouseMotionEvent(int mouse_x_pos, int mouse_y_pos);
  virtual ~MouseMotionEvent() override {}

  int GetMouseXPos() const;
  int GetMouseYPos() const;

protected:
  int mouse_x_pos_;
  int mouse_y_pos_;
};

class MouseButtonEvent : public AbstractEvent {
public:
  MouseButtonEvent(int mouse_x_pos, int mouse_y_pos, bool is_pressed);
  virtual ~MouseButtonEvent() override {}

  int GetMouseXPos() const;
  int GetMouseYPos() const;

  bool IsButtonPressed() const;

protected:
  int mouse_x_pos_;
  int mouse_y_pos_;

  bool is_pressed_;
};

class CloseWindowEvent : public AbstractEvent {
public:
  CloseWindowEvent(AbstractWindow* window);
  virtual ~CloseWindowEvent() override {}

  AbstractWindow* GetWindow() const;

protected:
  AbstractWindow* window_;
};

class MoveWindowEvent : public AbstractEvent {
public:
  MoveWindowEvent(int new_x_pos_, int new_y_pos_, AbstractWindow* window);
  virtual ~MoveWindowEvent() override {}

  int GetNewXPos() const;
  int GetNewYPos() const;
  AbstractWindow* GetWindow() const;

protected:
  int new_x_pos_;
  int new_y_pos_;

  AbstractWindow* window_;
};

void PostEvent(AbstractEvent* event);
void PollEvent(AbstractEvent** event);

void PumpEvents(AbstractWindow* main_window);
void ApplicationEvents(AbstractWindow* main_window);
