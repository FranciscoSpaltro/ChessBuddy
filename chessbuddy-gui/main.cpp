#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include "Game.h"

bool loadTexture(std::map<std::string, sf::Texture>& textures,
                 const std::string& key,
                 const std::string& path)
{
    sf::Texture tex;
    if (!tex.loadFromFile(path)) {
        return false;
    }
    textures[key] = tex;
    return true;
}

std::string textureKey(PieceColor c, PieceType t)
{
    char color = (c == PieceColor::white) ? 'w' : 'b';
    char type  = '?';

    switch (t) {
        case PieceType::Pawn:   type = 'P'; break;
        case PieceType::Knight: type = 'N'; break;
        case PieceType::Bishop: type = 'B'; break;
        case PieceType::Rook:   type = 'R'; break;
        case PieceType::Queen:  type = 'Q'; break;
        case PieceType::King:   type = 'K'; break;
        default: return "";
    }

    return std::string() + color + type;
}

int main()
{
    Game game;

    const int windowSize = 600;
    const int offset = 45;
    const int boardSize = 8;
    const float tileSize = windowSize / static_cast<float>(boardSize);

    sf::RenderWindow window(
        sf::VideoMode(windowSize, windowSize + offset),
        "ChessBuddy"
    );

    sf::Font font;
    if (!font.loadFromFile("assets/DejaVuSans.ttf"))
        return 1;

    sf::Text turnText;
    turnText.setFont(font);
    turnText.setCharacterSize(20);
    turnText.setFillColor(sf::Color::Black);
    turnText.setPosition(10.f, 10.f);

    sf::Text miscText;
    miscText.setFont(font);
    miscText.setCharacterSize(20);
    miscText.setFillColor(sf::Color::Black);
    miscText.setPosition(400.f, 10.f);

    std::map<std::string, sf::Texture> textures;

    loadTexture(textures, "bP", "assets/bPawn.png");
    loadTexture(textures, "wP", "assets/wPawn.png");
    loadTexture(textures, "bR", "assets/bRook.png");
    loadTexture(textures, "wR", "assets/wRook.png");
    loadTexture(textures, "bN", "assets/bKnight.png");
    loadTexture(textures, "wN", "assets/wKnight.png");
    loadTexture(textures, "bB", "assets/bBishop.png");
    loadTexture(textures, "wB", "assets/wBishop.png");
    loadTexture(textures, "bQ", "assets/bQueen.png");
    loadTexture(textures, "wQ", "assets/wQueen.png");
    loadTexture(textures, "bK", "assets/bKing.png");
    loadTexture(textures, "wK", "assets/wKing.png");

    int selectedRow = -1;
    int selectedCol = -1;
    int clickedRow = -1;
    int clickedCol = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                // click arriba del tablero
                if (event.mouseButton.y < offset)
                    continue;

                int col = static_cast<int>(event.mouseButton.x / tileSize);
                int row = static_cast<int>((event.mouseButton.y - offset) / tileSize);

                if (row < 0 || row >= boardSize || col < 0 || col >= boardSize)
                    continue;

                clickedRow = row;
                clickedCol = col;

                if (selectedRow == -1) {
                    // primer click: seleccionar pieza válida
                    const Piece* p = game.getBoard().getPiece(row, col);
                    if (!p) continue;
                    if (p->getColor() != game.getCurrentPlayer()) continue;

                    selectedRow = row;
                    selectedCol = col;
                }
                else {
                    // segundo click: intentar mover
                    movement m{selectedRow, selectedCol, row, col};
                    game.play(m);

                    selectedRow = -1;
                    selectedCol = -1;
                }
            }
        }

        window.clear(sf::Color::White);

        turnText.setString(game.getCurrentPlayer() == PieceColor::white ? "Play: WHITE" : "Play: BLACK");

        if(game.getBoard().isCheckMate(game.getCurrentPlayer())){
            miscText.setString("CHECK MATE!");
        } else if(game.getBoard().isKingInCheck(game.getCurrentPlayer())){
            miscText.setString("CHECK!");
        } else {
            miscText.setString("PLAY!");
        }

        // dibujar tablero y piezas
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {

                sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));
                square.setPosition(col * tileSize, row * tileSize + offset);

                bool dark = (row + col) % 2;
                sf::Color base = dark ? sf::Color(110,110,110) : sf::Color(230,230,230);

                if (row == clickedRow && col == clickedCol) {
                    base = sf::Color(255, 255, 150); // amarillo claro
                }

                square.setFillColor(base);
                window.draw(square);

                const Piece* p = game.getBoard().getPiece(row, col);
                if (!p) continue;

                std::string key = textureKey(p->getColor(), p->getType());

                auto it = textures.find(key);
                if (it == textures.end())
                    continue;

                sf::Sprite sprite(it->second);

                sf::Vector2u sz = it->second.getSize();
                if (sz.x == 0 || sz.y == 0)
                    continue;

                sprite.setScale(tileSize / sz.x, tileSize / sz.y);
                sprite.setPosition(col * tileSize, row * tileSize + offset);
                window.draw(sprite);
            }
        }

        window.draw(turnText);
        window.draw(miscText);
        window.display();
    }

    return 0;
}
