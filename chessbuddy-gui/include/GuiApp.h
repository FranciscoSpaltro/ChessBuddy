#ifndef GUI_APP_H
#define GUI_APP_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <map>
#include <string>
#include <set>

extern int windowSize;
extern int offset;
extern const int boardSize;
extern const float tileSize;


struct Square { 
    int row; 
    int col;
};

class GuiApp {
    private:
        Game game;
        sf::RenderWindow window;
        std::optional<Square> selected;
        std::map<std::string, sf::Texture> texturesPieces;
        sf::Font font;
        sf::Text turnText;
        sf::Text statusText;

        bool isInsideBoard(int mouseX, int mouseY);

    public:
        GuiApp() : window(sf::VideoMode(windowSize, windowSize + offset), "ChessBuddy"){}
        bool initialize();
        void render();
        void handleClick(int mouseX, int mouseY);
        void processEvents();
        int run();
};


#endif // GUI_APP_H