#include "GuiApp.h"

/************************* VARIABLES *************************/
int windowSize = 640;
int offset = 40;
const int boardSize = 8;
const float tileSize = windowSize / static_cast<float>(boardSize);


/************************* FUNCIONES AUXILIARES *************************/
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


std::set<std::pair<int,int>> GuiApp::calculateHighlights() {
    std::set<std::pair<int,int>> destinations;
    
    // Si no hay selección o no es mi turno, no calculamos nada
    if (!graphic.selected) return destinations;
    
    const Piece* p = game.getBoard().getPiece(graphic.selected->row, graphic.selected->col);
    if (!p || p->getColor() != game.getCurrentPlayer()) return destinations;

    // Calculamos movimientos
    auto legalMoves = game.getBoard().getLegalMoves(graphic.selected->row, graphic.selected->col);
    for (const auto& m : legalMoves) {
        destinations.insert({m.toRow, m.toColumn});
    }
    
    return destinations;
}

void GuiApp::drawBoardSquares(const std::set<std::pair<int,int>>& destinations) {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            sf::RectangleShape square(sf::Vector2f(tileSize, tileSize));
            square.setPosition(col * tileSize, row * tileSize + offset);

            // Color base
            bool dark = (row + col) % 2;
            sf::Color base = dark ? sf::Color(110,110,110) : sf::Color(230,230,230);

            // Resaltado
            bool isDest = destinations.count({row, col}) > 0;
            bool isSelected = (graphic.selected && row == graphic.selected->row && col == graphic.selected->col);

            if (isSelected) base = sf::Color(255, 255, 150);
            else if (isDest) base = sf::Color(255, 0, 0);
            
            square.setFillColor(base);
            graphic.window.draw(square);
        }
    }
}

void GuiApp::drawPieces() {
    for (int row = 0; row < boardSize; ++row) {
        for (int col = 0; col < boardSize; ++col) {
            const Piece* p = game.getBoard().getPiece(row, col);
            if (!p) continue;

            std::string key = textureKey(p->getColor(), p->getType());
            // Nota: asumo que texturesPieces es miembro de graphic o de GuiApp
            if (graphic.texturesPieces.find(key) == graphic.texturesPieces.end()) continue;

            sf::Sprite sprite(graphic.texturesPieces[key]);
            sf::Vector2u sz = graphic.texturesPieces[key].getSize();
            if (sz.x == 0 || sz.y == 0) continue;

            sprite.setScale(float(tileSize) / sz.x, float(tileSize) / sz.y);
            sprite.setPosition(col * tileSize, row * tileSize + offset);
            graphic.window.draw(sprite);
        }
    }
}

void GuiApp::drawGrid() {
    float boardPx = boardSize * tileSize;
    
    // Verticales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(2.f, boardPx));
        line.setFillColor(sf::Color::Black);
        line.setPosition(i * tileSize - 1.f, offset); // Ajusté un poco el centrado (-1.f)
        graphic.window.draw(line);
    }
    // Horizontales
    for (int i = 0; i <= boardSize; ++i) {
        sf::RectangleShape line(sf::Vector2f(boardPx, 2.f));
        line.setFillColor(sf::Color::Black);
        line.setPosition(0.f, offset + i * tileSize - 1.f);
        graphic.window.draw(line);
    }
}

void GuiApp::updateUITexts() {
    // 1. Actualizar Texto de Turno (Arriba Izquierda)
    std::string turnStr = (game.getCurrentPlayer() == PieceColor::white) ? "Play: WHITE" : "Play: BLACK";
    graphic.turnText.setString(turnStr);

    // 2. Actualizar Número de Turno
    graphic.turnNumberText.setString("TURN " + std::to_string(game.getTurnNumber()));

    // 3. Actualizar Mensaje de Estado (Abajo)
    // Con switch se decide qué mensaje mostrar según el modo actual
    std::string statusMsg = "";

    switch (state) {
        case GuiState::Promoting:
            // Prioridad máxima: Instrucciones de UI
            statusMsg = "Promocion: Elige Q, R, B, N";
            break;

        case GuiState::GameOver:
            // Prioridad alta: Resultado final
            statusMsg = game.getGameMessage(); // Ej: "CHECK MATE!"
            break;

        case GuiState::Playing:
            // Prioridad normal: Juego en curso
            if (game.isKingInCheck()) {
                if(game.isCheckMate() || game.isStaleMate())
                    state = GuiState::GameOver;
                else
                    statusMsg = "CHECK!"; // Aviso importante in-game
            } else {
                // Mensajes estándar del backend ("Play!", "Invalid Move", etc.)
                statusMsg = game.getGameMessage();
            }
            break;
    }

    graphic.statusText.setString(statusMsg);
}

void GuiApp::render(){
    graphic.window.clear(sf::Color::White);

    // 1. Preparar datos
    updateUITexts();
    auto highlights = calculateHighlights();

    // 2. Dibujar capas en orden
    drawBoardSquares(highlights); // Fondo
    drawPieces();                 // Piezas encima
    drawGrid();                   // Rejilla encima de todo

    // 3. Overlays (Estados especiales)
    if (state == GuiState::Promoting) {
        drawPromotionOverlay();
    }
    // else if (state == GuiState::GameOver) drawGameOverOverlay();

    // 4. Interfaz de usuario
    graphic.window.draw(graphic.turnText);
    graphic.window.draw(graphic.statusText);
    graphic.window.draw(graphic.turnNumberText);

    graphic.window.display();
}


void GuiApp::handleInputPromoting(int mouseX, int mouseY){
    if(game.isPromotionRequested()){
        PieceType chosen;
        if(pickPromotion(mouseX, mouseY, chosen)){
            game.makePromotion(chosen);
        }

        if(game.isCheckMate() || game.isStaleMate())
            state = GuiState::GameOver;
        else
            state = GuiState::Playing;
    }
}

void GuiApp::handleInputPlaying(int mouseX, int mouseY){
    bool moved = false;

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
            moved = game.play(m);
            graphic.selected.reset();
        }
    }

    if (moved) {
        if (game.isPromotionRequested()) {
            state = GuiState::Promoting;
            openPromotionMenu();
        } else if (game.isCheckMate() || game.isStaleMate()) {
            state = GuiState::GameOver;
        }
    }
}

void GuiApp::handleInputGameOver(){
    graphic.statusText.setString("GAME OVER!");
}

void GuiApp::processEvents(){
    sf::Event event;
    
    while (graphic.window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            graphic.window.close();
            continue;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            switch(state) {
                case GuiState::Playing:
                    if (isInsideBoard(event.mouseButton.x, event.mouseButton.y)) // Solo en modo juego valido el borde
                        handleInputPlaying(event.mouseButton.x, event.mouseButton.y);
                    else
                        graphic.statusText.setString("Invalid Click");
                    break;

                case GuiState::Promoting:
                    handleInputPromoting(event.mouseButton.x, event.mouseButton.y);
                    break;

                case GuiState::GameOver:
                    handleInputGameOver();
                    break;
            }
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

    // panel detrás
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
