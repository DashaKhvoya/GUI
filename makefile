CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

LIBS = -lsdl2 -lsdl2_ttf -lsdl2_image

all: a.out

a.out: main.o AbstractWindow.o Manager.o Button.o Window.o Render.o Texture.o Event.o ToolBar.o Palette.o Menu.o Tool.o Canvas.o ScrollBar.o TextureManager.o
	$(CXX) -o a.out main.o AbstractWindow.o Manager.o Button.o Window.o Render.o Texture.o Event.o ToolBar.o Palette.o Menu.o Tool.o Canvas.o ScrollBar.o TextureManager.o $(LIBS)

main.o: main.cpp AbstractWindow.h Manager.h Button.h Window.h Render.h Texture.h Event.h ToolBar.h Palette.h Menu.h Tool.h Canvas.h ScrollBar.h TextureManager.h Const.h
	$(CXX) -o main.o -c $(CXXFLAGS) main.cpp

AbstractWindow.o: AbstractWindow.cpp AbstractWindow.h Render.h Event.h Const.h
	$(CXX) -o AbstractWindow.o -c $(CXXFLAGS) AbstractWindow.cpp

Manager.o: Manager.cpp Manager.h AbstractWindow.h Render.h Texture.h Event.h Const.h
		$(CXX) -o Manager.o -c $(CXXFLAGS) Manager.cpp

Button.o: Button.cpp Button.h AbstractWindow.h Render.h Texture.h Event.h Tool.h Canvas.h ScrollBar.h
		$(CXX) -o Button.o -c $(CXXFLAGS) Button.cpp

Window.o: Window.cpp Window.h Const.h
		$(CXX) -o Window.o -c $(CXXFLAGS) Window.cpp

Render.o: Render.cpp Render.h Window.h Texture.h Const.h
	$(CXX) -o Render.o -c $(CXXFLAGS) Render.cpp

Texture.o: Texture.cpp Texture.h Render.h Const.h
	$(CXX) -o Texture.o -c $(CXXFLAGS) Texture.cpp

Event.o: Event.cpp Event.h AbstractWindow.h Const.h
	$(CXX) -o Event.o -c $(CXXFLAGS) Event.cpp

ToolBar.o: ToolBar.cpp ToolBar.h AbstractWindow.h Manager.h Button.h Window.h Render.h Texture.h Event.h TextureManager.h Const.h
	$(CXX) -o ToolBar.o -c $(CXXFLAGS) ToolBar.cpp

Palette.o: Palette.cpp Palette.h AbstractWindow.h Manager.h Button.h Window.h Render.h Texture.h Event.h TextureManager.h Const.h
	$(CXX) -o Palette.o -c $(CXXFLAGS) Palette.cpp

Menu.o: Menu.cpp Menu.h AbstractWindow.h Manager.h Button.h Window.h Render.h Texture.h Event.h TextureManager.h Canvas.h Const.h
	$(CXX) -o Menu.o -c $(CXXFLAGS) Menu.cpp

Tool.o: Tool.cpp Tool.h Window.h Render.h Texture.h Event.h Const.h
	$(CXX) -o Tool.o -c $(CXXFLAGS) Tool.cpp

Canvas.o: Canvas.cpp Canvas.h AbstractWindow.h Button.h Manager.h Window.h Render.h Texture.h Event.h Tool.h TextureManager.h Const.h
	$(CXX) -o Canvas.o -c $(CXXFLAGS) Canvas.cpp

ScrollBar.o: ScrollBar.cpp ScrollBar.h AbstractWindow.h Button.h Manager.h Window.h Render.h Texture.h Event.h Tool.h TextureManager.h Const.h
	$(CXX) -o ScrollBar.o -c $(CXXFLAGS) ScrollBar.cpp

TextureManager.o: TextureManager.cpp TextureManager.h Render.h Texture.h Const.h
	$(CXX) -o TextureManager.o -c $(CXXFLAGS) TextureManager.cpp
