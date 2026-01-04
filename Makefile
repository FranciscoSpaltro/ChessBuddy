CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -Ichessbuddy-core/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

GUI_SRC = chessbuddy-gui/main.cpp

CORE_ALL_SRC_DIR = $(wildcard chessbuddy-core/src/*.cpp)
CORE_ALL_FLAT    = $(wildcard chessbuddy-core/*.cpp)
CORE_ALL         = $(if $(CORE_ALL_SRC_DIR),$(CORE_ALL_SRC_DIR),$(CORE_ALL_FLAT))
CORE_SRC         = $(filter-out %/main.cpp main.cpp,$(CORE_ALL))

TARGET = chessbuddy-gui/chessbuddy

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) $(GUI_SRC) $(CORE_SRC) $(INCLUDES) $(LIBS) -o $(TARGET)

run: $(TARGET)
	cd chessbuddy-gui && ./chessbuddy

clean:
	rm -f $(TARGET)
