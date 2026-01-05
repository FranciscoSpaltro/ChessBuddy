CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -Ichessbuddy-core/include -Ichessbuddy-gui/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

GUI_SRC = $(wildcard chessbuddy-gui/src/*.cpp)

CORE_ALL = $(wildcard chessbuddy-core/src/*.cpp)
CORE_SRC = $(filter-out %/main.cpp main.cpp,$(CORE_ALL))
MAIN = chessbuddy-gui/main.cpp

TARGET = chessbuddy-gui/chessbuddy

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(GUI_SRC) $(CORE_SRC) $(MAIN) $(INCLUDES) $(LIBS) -o $(TARGET)

run: $(TARGET)
	cd chessbuddy-gui && ./chessbuddy

clean:
	rm -f $(TARGET)
