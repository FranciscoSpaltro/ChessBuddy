#include "GuiApp.h"

int windowSize = 640;
int offset = 40;
const int boardSize = 8;
const float tileSize = windowSize / static_cast<float>(boardSize);

bool loadTexture(std::map<std::string, sf::Texture>& textures, const std::string& key, const std::string& path){
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

/* *************************************************************************************************** */

bool GuiApp::isInsideBoard(int mouseX, int mouseY){
    if(mouseY < offset)
        return false;

    return true;
}

/* *************************************************************************************************** */
bool GuiApp::initialize(void){    
    if (!font.loadFromFile("assets/DejaVuSans.ttf"))
        return false;

    turnText.setFont(font);
    turnText.setCharacterSize(20);
    turnText.setFillColor(sf::Color::Black);
    turnText.setPosition(10.f, 10.f);
    turnText.setString("Play: WHITE");

    statusText.setFont(font);
    statusText.setCharacterSize(20);
    statusText.setFillColor(sf::Color::Black);
    statusText.setPosition(400.f, 10.f);
    statusText.setString("");

    if(!loadTexture(texturesPieces, "bP", "assets/bPawn.png")) return false;
    if(!loadTexture(texturesPieces, "wP", "assets/wPawn.png")) return false;
    if(!loadTexture(texturesPieces, "bR", "assets/bRook.png")) return false;
    if(!loadTexture(texturesPieces, "wR", "assets/wRook.png")) return false;
    if(!loadTexture(texturesPieces, "bN", "assets/bKnight.png")) return false;
    if(!loadTexture(texturesPieces, "wN", "assets/wKnight.png")) return false;
    if(!loadTexture(texturesPieces, "bB", "assets/bBishop.png")) return false;
    if(!loadTexture(texturesPieces, "wB", "assets/wBishop.png")) return false;
    if(!loadTexture(texturesPieces, "bQ", "assets/bQueen.png")) return false;
    if(!loadTexture(texturesPieces, "wQ", "assets/wQueen.png")) return false;
    if(!loadTexture(texturesPieces, "bK", "assets/bKing.png")) return false;
    if(!loadTexture(texturesPieces, "wK", "assets/wKing.png")) return false;

    return true;
}

void GuiApp::render(){
    window.clear(sf::Color::White);

    turnText.setString(game.getCurrentPlayer() == PieceColor::white ? "Play: WHITE" : "Play: BLACK");

    if(game.getBoard().isCheckMate(game.getCurrentPlayer())){
        statusText.setString("CHECK MATE!");
    } else if(game.getBoard().isKingInCheck(game.getCurrentPlayer())){
        statusText.setString("CHECK!");
    } else {
        statusText.setString("PLAY!");
    }

    // dibujar tablero y piezas
    std::vector<movement> legalMoves;
    if(selected){
        legalMoves = game.getBoard().getLegalMoves(selected->row, selected->col);
    } 

    std::set<std::pair<int,int>> destinations;

    if (selected) {
        for (const auto& m : legalMoves) {
            destinations.insert({m.toRow, m.toColumn}); // Para no recorrer todo legalMoves en cada casilla (doble for)
        }
    }

    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {

            sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));
            square.setPosition(col * tileSize, row * tileSize + offset);

            bool dark = (row + col) % 2;
            sf::Color base = dark ? sf::Color(110,110,110) : sf::Color(230,230,230);

            bool isDest = false;
            if(selected){
                isDest = destinations.count({row, col}) > 0;
            }

            if (selected && row == selected->row && col == selected->col) {
                base = sf::Color(255, 255, 150); // amarillo claro
            } else if(isDest){
                base = sf::Color(255, 0, 0);
            }
            
            square.setFillColor(base);
            window.draw(square);

            const Piece* p = game.getBoard().getPiece(row, col);
            if (!p) continue;

            std::string key = textureKey(p->getColor(), p->getType());

            auto it = texturesPieces.find(key);
            if (it == texturesPieces.end())
                continue;

            sf::Sprite sprite(it->second);

            sf::Vector2u sz = it->second.getSize();
            if (sz.x == 0 || sz.y == 0)
                continue;

            sprite.setScale(float(tileSize) / sz.x, float(tileSize) / sz.y);
            sprite.setPosition(col * tileSize, row * tileSize + offset);
            window.draw(sprite);
        }
    }

    const float boardPx = boardSize * tileSize;

    // Líneas verticales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(2.f, boardPx));
        line.setFillColor(sf::Color::Black);
        line.setPosition(i * tileSize - 2.f * 0.5f, offset);
        window.draw(line);
    }

    // Líneas horizontales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(boardPx, 2.f));
        line.setFillColor(sf::Color::Black);
        line.setPosition(0.f, offset + i * tileSize - 2.f * 0.5f);
        window.draw(line);
    }

    window.draw(turnText);
    window.draw(statusText);
    window.display();
}

void GuiApp::handleClick(int mouseX, int mouseY){
    if(!isInsideBoard(mouseX, mouseY)){
        statusText.setString("Invalid Click");
        return;
    }
        
    bool status = false;

    Square s{static_cast<int>((mouseY - offset) / tileSize), static_cast<int>(mouseX / tileSize)};

    if(!selected){  // Si selected esta vacio
        selected = s;
    } else {
        if(s.row == selected -> row && s.col == selected -> col){    // apreté de nuevo la misma pieza
            selected.reset();
        } else {
            movement m{selected->row, selected->col, s.row, s.col};
            status = game.play(m);
            selected.reset();
        }
    }

    if(!status){
        statusText.setString("Invalid Move");
    }
}

void GuiApp::processEvents(){
    sf::Event event;
    
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            window.close();
            continue;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            handleClick(event.mouseButton.x, event.mouseButton.y);
            continue;
        }
    }
}

int GuiApp::run() {

    if (!initialize())
        return 1;

    while (window.isOpen()) {
        processEvents();
        render();
    }
    
    return 0;
}
