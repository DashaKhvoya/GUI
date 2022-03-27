#include "Event.h"

static std::queue<AbstractEvent*> EVENT_QUEUE;

AbstractEvent::AbstractEvent(int type) : type_(type) {}

int AbstractEvent::GetType() const {
  return type_;
}

MouseMotionEvent::MouseMotionEvent(int mouse_x_pos, int mouse_y_pos)
  : AbstractEvent(MOUSE_MOTION), mouse_x_pos_(mouse_x_pos), mouse_y_pos_(mouse_y_pos) {}

int MouseMotionEvent::GetMouseXPos() const {
  return mouse_x_pos_;
}

int MouseMotionEvent::GetMouseYPos() const {
  return mouse_y_pos_;
}

MouseButtonEvent::MouseButtonEvent(int mouse_x_pos, int mouse_y_pos, bool is_pressed)
  : AbstractEvent(MOUSE_BUTTON), mouse_x_pos_(mouse_x_pos), mouse_y_pos_(mouse_y_pos), is_pressed_(is_pressed) {}

int MouseButtonEvent::GetMouseXPos() const {
  return mouse_x_pos_;
}

int MouseButtonEvent::GetMouseYPos() const {
  return mouse_y_pos_;
}

bool MouseButtonEvent::IsButtonPressed() const {
  return is_pressed_;
}

CloseWindowEvent::CloseWindowEvent(AbstractWindow* window)
  : AbstractEvent(WINDOW_CLOSE), window_(window) {}

AbstractWindow* CloseWindowEvent::GetWindow() const {
  return window_;
}

MoveWindowEvent::MoveWindowEvent(int new_x_pos, int new_y_pos, AbstractWindow* window)
  : AbstractEvent(WINDOW_MOVE), new_x_pos_(new_x_pos), new_y_pos_(new_y_pos), window_(window) {}

int MoveWindowEvent::GetNewXPos() const {
  return new_x_pos_;
}

int MoveWindowEvent::GetNewYPos() const {
  return new_y_pos_;
}

AbstractWindow* MoveWindowEvent::GetWindow() const {
  return window_;
}

void PostEvent(AbstractEvent* event) {
  EVENT_QUEUE.push(event);
}

void PollEvent(AbstractEvent** event) {
  *event = EVENT_QUEUE.front();
  EVENT_QUEUE.pop();
}

void PumpEvents(AbstractWindow* window) {
  SDL_Event event{};

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT: {
        PostEvent(new CloseWindowEvent(window));
      } break;

      case SDL_MOUSEBUTTONDOWN: {
        PostEvent(new MouseButtonEvent(event.button.x, event.button.y, true));
      } break;

      case SDL_MOUSEBUTTONUP: {
        PostEvent(new MouseButtonEvent(event.button.x, event.button.y, false));
      } break;

      case SDL_MOUSEMOTION: {
        PostEvent(new MouseMotionEvent(event.button.x, event.button.y));
      } break;
    }
  }
}

void ApplicationEvents(AbstractWindow* main_window) {
  while (!EVENT_QUEUE.empty()) {
    AbstractEvent* event = nullptr;
    PollEvent(&event);
    assert(event);
    switch (event->GetType()) {
      case MOUSE_MOTION: {
        MouseMotionEvent* new_event = dynamic_cast<MouseMotionEvent*>(event);
        main_window->OnMouseMotion(new_event);
      } break;

      case MOUSE_BUTTON: {
        MouseButtonEvent* new_event = dynamic_cast<MouseButtonEvent*>(event);
        main_window->OnMouseButton(new_event);
      } break;

      case WINDOW_CLOSE: {
        CloseWindowEvent* new_event = dynamic_cast<CloseWindowEvent*>(event);
        new_event->GetWindow()->OnClose();
      } break;

      case WINDOW_MOVE: {
        MoveWindowEvent* new_event = dynamic_cast<MoveWindowEvent*>(event);
        new_event->GetWindow()->OnMove(new_event);
      } break;
    }
  }
}
