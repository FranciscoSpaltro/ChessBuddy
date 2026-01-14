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

enum class GuiState { 
    Playing, 
    Promoting, 
    GameOver 
};

struct graphicElements {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(windowSize, windowSize + offset), "ChessBuddy");
    std::optional<Square> selected;
    std::map<std::string, sf::Texture> texturesPieces;
    sf::Font font;
    sf::Text turnText;
    sf::Text statusText;
    sf::Text turnNumberText;
    std::array<sf::FloatRect, 4> promoHit;
    std::array<sf::Sprite, 4>    promoSprite;
};

class GuiApp {
    private:
        Game game;
        graphicElements graphic;
        bool promotionMode = false;
        GuiState state = GuiState::Playing;

        bool isInsideBoard(int mouseX, int mouseY);
        bool pickPromotion(int mouseX, int mouseY, PieceType& chosen);
        void openPromotionMenu(void);
        void drawPromotionOverlay();

    public:
        bool initialize();
        void render();
        void handleClick(int mouseX, int mouseY);
        void handleInputPlaying(int mouseX, int mouseY);
        void processEvents();
        int run();
};


#endif // GUI_APP_H