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
    if (mouseX < 0 || mouseX >= windowSize) return false;
    if (mouseY < offset || mouseY >= offset + windowSize) return false;
    return true;
}

/* *************************************************************************************************** */
bool GuiApp::initialize(void){    
    if (!graphic.font.loadFromFile("assets/DejaVuSans.ttf"))
        return false;

    graphic.turnText.setFont(graphic.font);
    graphic.turnText.setCharacterSize(20);
    graphic.turnText.setFillColor(sf::Color::Black);
    graphic.turnText.setPosition(10.f, 10.f);
    graphic.turnText.setString("Play: WHITE");

    graphic.statusText.setFont(graphic.font);
    graphic.statusText.setCharacterSize(20);
    graphic.statusText.setFillColor(sf::Color::Black);
    graphic.statusText.setPosition(400.f, 10.f);
    graphic.statusText.setString("");

    graphic.turnNumberText.setFont(graphic.font);
    graphic.turnNumberText.setCharacterSize(20);
    graphic.turnNumberText.setFillColor(sf::Color::Black);
    graphic.turnNumberText.setPosition(150.f, 10.f);
    graphic.turnNumberText.setString("TURN " + std::to_string(game.getTurnNumber()));

    if(!loadTexture(graphic.texturesPieces, "bP", "assets/bPawn.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wP", "assets/wPawn.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "bR", "assets/bRook.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wR", "assets/wRook.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "bN", "assets/bKnight.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wN", "assets/wKnight.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "bB", "assets/bBishop.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wB", "assets/wBishop.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "bQ", "assets/bQueen.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wQ", "assets/wQueen.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "bK", "assets/bKing.png")) return false;
    if(!loadTexture(graphic.texturesPieces, "wK", "assets/wKing.png")) return false;

    return true;
}

void GuiApp::handleInputPlaying(int mouseX, int mouseY){
    
}

void GuiApp::render(){
    graphic.window.clear(sf::Color::White);

    graphic.turnText.setString(game.getCurrentPlayer() == PieceColor::white ? "Play: WHITE" : "Play: BLACK");
    graphic.statusText.setString(game.getGameMessage());
    graphic.turnNumberText.setString("TURN " + std::to_string(game.getTurnNumber()));

    // dibujar tablero y piezas
    std::vector<movement> legalMoves;
    if (graphic.selected) {
        const Piece* p = game.getBoard().getPiece(graphic.selected->row, graphic.selected->col);
        if (p && p->getColor() == game.getCurrentPlayer()) {
            legalMoves = game.getBoard().getLegalMoves(graphic.selected->row, graphic.selected->col);
        }
    }

    std::set<std::pair<int,int>> destinations;

    // Abajo se van a dibujar 64 casillas. Si usara directamente legalMoves, por cada casilla tendrías que recorrer todo el vector para ver si hay que pintarla de rojo. Con el set, la búsqueda es instantánea (destinations.count({row, col}) encuentra las ocurrencias)
    if (graphic.selected) {
        for (const auto& m : legalMoves) {
            destinations.insert({m.toRow, m.toColumn}); // Para no recorrer todo legalMoves en cada casilla (doble for)
        }
    }


    // ITERACIÓN SOBRE CADA CASILLA
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {

            sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));    // Crea un cuadrado tamaño titleSize
            square.setPosition(col * tileSize, row * tileSize + offset);    // Lo ubica en la columna y fila correspondiente

            bool dark = (row + col) % 2;                                    // Si fila + columna es par -> blanco
            sf::Color base = dark ? sf::Color(110,110,110) : sf::Color(230,230,230);

            // RESALTADO (COLOREADO LÓGICO)
            bool isDest = false;
            if(graphic.selected){
                isDest = destinations.count({row, col}) > 0;
            }

            // Si se seleccionó previamente una pieza y la (row,col) es la pieza que seleccioné -> amarillo
            if (graphic.selected && row == graphic.selected->row && col == graphic.selected->col) {
                base = sf::Color(255, 255, 150); // amarillo claro
            } else if(isDest){
                // Si no es la pieza que seleccioné pero tiene un destino válido -> rojo
                base = sf::Color(255, 0, 0);
            }
            
            // Dibuja el cuadrado
            square.setFillColor(base);
            graphic.window.draw(square);

            // DIBUJO DE LA PIEZA
            const Piece* p = game.getBoard().getPiece(row, col);
            if (!p) continue;   // Si no hay ninguna pieza en esa (row,col), nada más que hacer

            // Busco la textura correspondiente al tipo y color de pieza que hay en (row,col)
            std::string key = textureKey(p->getColor(), p->getType());
            auto it = graphic.texturesPieces.find(key);
            if (it == graphic.texturesPieces.end())
                continue;   // Si no encontré la textura, nada más que hacer

            // Creo el Sprite (imagen visual)
            sf::Sprite sprite(it->second);

            sf::Vector2u sz = it->second.getSize();
            if (sz.x == 0 || sz.y == 0)
                continue;

            // Escalo, posiciono y dibujo el Sprite
            sprite.setScale(float(tileSize) / sz.x, float(tileSize) / sz.y);
            sprite.setPosition(col * tileSize, row * tileSize + offset);
            graphic.window.draw(sprite);
        }
    }


    // DIBUJOS ADICIONALES (LINEAS)
    const float boardPx = boardSize * tileSize;

    // Líneas verticales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(2.f, boardPx));
        line.setFillColor(sf::Color::Black);
        line.setPosition(i * tileSize - 2.f * 0.5f, offset);
        graphic.window.draw(line);
    }

    // Líneas horizontales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(boardPx, 2.f));
        line.setFillColor(sf::Color::Black);
        line.setPosition(0.f, offset + i * tileSize - 2.f * 0.5f);
        graphic.window.draw(line);
    }

    // PROMOCION
    if (game.isPromotionRequested()) {
        drawPromotionOverlay();
    }

    // DIBUJO LAS COSAS
    graphic.window.draw(graphic.turnText);
    graphic.window.draw(graphic.statusText);
    graphic.window.draw(graphic.turnNumberText);
    graphic.window.display();
}

void GuiApp::handleClick(int mouseX, int mouseY){
    if(!isInsideBoard(mouseX, mouseY)){
        graphic.statusText.setString("Invalid Click");
        return;
    }
    
    if(game.isPromotionRequested()){
        PieceType chosen;
        if(pickPromotion(mouseX, mouseY, chosen)){
            game.makePromotion(chosen);
        }

        promotionMode = false;

        return;
    }

    bool status = false;
    bool attemptMove = false;

    Square s{static_cast<int>((mouseY - offset) / tileSize), static_cast<int>(mouseX / tileSize)};

    if(!graphic.selected){  // Si selected esta vacio
        graphic.selected = s;
        bool checkOrigin = game.checkOrigin(Position{s.row, s.col});
        if(!checkOrigin){
            graphic.statusText.setString(game.getGameMessage());
            graphic.selected.reset();
        }
    } else {
        if(s.row == graphic.selected -> row && s.col == graphic.selected -> col){    // apreté de nuevo la misma pieza
            graphic.selected.reset();
        } else {
            movement m{graphic.selected->row, graphic.selected->col, s.row, s.col};
            status = game.play(m);
            graphic.selected.reset();
            attemptMove = true;
        }
    }

    if(status && game.isPromotionRequested()){
        openPromotionMenu();
        return;
    }

    if(attemptMove && !status){
        graphic.statusText.setString(game.getGameMessage());
    }

    attemptMove = false;

    if (game.isKingInCheck()){
        graphic.statusText.setString("King in check!");
    } else if(game.isCheckMate() || game.isStaleMate()){
        graphic.statusText.setString(game.getGameMessage());
        
    }
}

void GuiApp::processEvents(){
    sf::Event event;
    
    while (graphic.window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            graphic.window.close();
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

    while (graphic.window.isOpen()) {
        processEvents();
        render();
    }
    
    return 0;
}

bool GuiApp::pickPromotion(int mouseX, int mouseY, PieceType& chosen){
    sf::Vector2f p((float)mouseX, (float)mouseY);

    if (graphic.promoHit[0].contains(p)) { chosen = PieceType::Queen;  return true; }
    if (graphic.promoHit[1].contains(p)) { chosen = PieceType::Rook;   return true; }
    if (graphic.promoHit[2].contains(p)) { chosen = PieceType::Bishop; return true; }
    if (graphic.promoHit[3].contains(p)) { chosen = PieceType::Knight; return true; }

    return false;
}

void GuiApp::openPromotionMenu(void){
    // Panel 4x1 centrado sobre el tablero
    float boardPx = boardSize * tileSize;
    float x0 = (boardPx - 4.f * tileSize) / 2.f;
    float y0 = offset + (boardPx - 1.f * tileSize) / 2.f;

    const PieceType opts[4] = {
        PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight
    };

    for (int i = 0; i < 4; ++i) {
        // hitbox
        graphic.promoHit[i] = sf::FloatRect(x0 + i*tileSize, y0, tileSize, tileSize);

        // sprite
        std::string key = textureKey(game.getPromotionColor(), opts[i]);
        auto it = graphic.texturesPieces.find(key);
        if (it == graphic.texturesPieces.end()) continue;

        graphic.promoSprite[i].setTexture(it->second);

        sf::Vector2u sz = it->second.getSize();
        if (sz.x == 0 || sz.y == 0) continue;

        graphic.promoSprite[i].setScale(tileSize / sz.x, tileSize / sz.y);
        graphic.promoSprite[i].setPosition(x0 + i*tileSize, y0);
    }

    graphic.statusText.setString("Choose promotion: Q R B N");
}

void GuiApp::drawPromotionOverlay(){
    // oscurecer fondo
    sf::RectangleShape dim(sf::Vector2f((float)graphic.window.getSize().x, (float)graphic.window.getSize().y));
    dim.setFillColor(sf::Color(0, 0, 0, 140));
    graphic.window.draw(dim);

    // panel detrás (opcional pero queda mucho más claro)
    float boardPx = boardSize * tileSize;
    float x0 = (boardPx - 4.f * tileSize) / 2.f;
    float y0 = offset + (boardPx - 1.f * tileSize) / 2.f;

    sf::RectangleShape panel;
    panel.setPosition(x0 - 8.f, y0 - 8.f);
    panel.setSize(sf::Vector2f(4.f * tileSize + 16.f, tileSize + 16.f));
    panel.setFillColor(sf::Color(30, 30, 30, 220));
    graphic.window.draw(panel);

    // dibujar sprites de opciones
    for (int i = 0; i < 4; ++i) {
        graphic.window.draw(graphic.promoSprite[i]);
    }
}
