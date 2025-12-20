#include "Board.h"

bool Board::isCastling(const movement& m){
    if(board[index(m.fromRow, m.fromColumn)] -> hasMoved())
        return false;

    bool kingSide = (m.toColumn > m.fromColumn);    // Si es positivo, se mueve a la derecha
    int rookCol = kingSide ? 7 : 0;                 // Si se mueve a la derecha, la columna de la torre es 7
    int row = m.fromRow;

    Piece* rookCandidate = board[index(row, rookCol)].get();
    if (!rookCandidate)
        return false;

    if (rookCandidate->getType() != PieceType::Rook)
        return false;

    if(rookCandidate->hasMoved())
        return false;

    movement aux = {m.fromRow, m.fromColumn, m.fromRow, kingSide ? rookCol - 1 : rookCol + 1};
    if(!isPathClear(aux))
        return false;

    return true;
}

bool Board::checkEmpty(int row, int column) const{
    if (!this -> getPiece(row, column))
        return true;
    return false;
}

int Board::index(int row, int column) const {
return row * 8 + column;
}

void Board::initialize(void){
    this -> board[index(0, 0)] = std::make_unique<Rook>(PieceColor::black);
    this -> board[index(0, 1)] = std::make_unique<Knight>(PieceColor::black);
    this -> board[index(0, 2)] = std::make_unique<Bishop>(PieceColor::black);
    this -> board[index(0, 3)] = std::make_unique<Queen>(PieceColor::black);
    this -> board[index(0, 4)] = std::make_unique<King>(PieceColor::black);
    this -> board[index(0, 5)] = std::make_unique<Bishop>(PieceColor::black);
    this -> board[index(0, 6)] = std::make_unique<Knight>(PieceColor::black);
    this -> board[index(0, 7)] = std::make_unique<Rook>(PieceColor::black);
    this -> board[index(1, 0)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 1)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 2)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 3)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 4)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 5)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 6)] = std::make_unique<Pawn>(PieceColor::black);
    this -> board[index(1, 7)] = std::make_unique<Pawn>(PieceColor::black);

    this -> board[index(6, 0)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 1)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 2)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 3)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 4)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 5)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 6)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(6, 7)] = std::make_unique<Pawn>(PieceColor::white);
    this -> board[index(7, 0)] = std::make_unique<Rook>(PieceColor::white);
    this -> board[index(7, 1)] = std::make_unique<Knight>(PieceColor::white);
    this -> board[index(7, 2)] = std::make_unique<Bishop>(PieceColor::white);
    this -> board[index(7, 3)] = std::make_unique<Queen>(PieceColor::white);
    this -> board[index(7, 4)] = std::make_unique<King>(PieceColor::white);
    this -> board[index(7, 5)] = std::make_unique<Bishop>(PieceColor::white);
    this -> board[index(7, 6)] = std::make_unique<Knight>(PieceColor::white);
    this -> board[index(7, 7)] = std::make_unique<Rook>(PieceColor::white);
}

Board::Board(void) {
    initialize();
};

const Piece* Board::getPiece(int row, int column) const {
    return board[index(row, column)].get();
}


bool Board::isValidMove(const movement& m) const {
    const Piece* piece = getPiece(m.fromRow, m.fromColumn);

    if (!piece)         // Si no seleccione una pieza
        return false;

    if (const Piece* target = getPiece(m.toRow, m.toColumn)) {
        if (target->getColor() == piece->getColor())            // Estaba ocupada por mi
            return false;
    }
    
    int dRow = abs(m.toRow - m.fromRow);
    int dCol = abs(m.toColumn - m.fromColumn);
    bool isLongMove = std::max(dRow, dCol) > 1;

    if (isLongMove && !piece->canJump())
        if(!isPathClear(m))
            return false;

    return piece->isValidMove(*this, m);
}

bool Board::isEnemyAt(int row, int col, PieceColor myColor) const {
    if (checkEmpty(row, col))
        return false;

    return getPiece(row, col)->getColor() != myColor;
}


void Board::printBoard() const {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {

            if (const Piece* p = getPiece(row, col)) {
                std::cout << p->symbol();
            } else {
                std::cout << '.';
            }

            if (col != 7)
                std::cout << " | ";
        }
        std::cout << '\n';
        std::cout << "---------------------------------------\n";
    }
}


bool Board::move(const movement& m) {
    if (!isValidMove(m)){
        return false;
    }

    Piece * originPiece = board[index(m.fromRow, m.fromColumn)].get();

    // Detecto posible enroque
    switch (originPiece->getSpecialMove(m))
    {
        case SpecialMove::Castling:{
            if(!isCastling(m))
                break;
            bool kingSide = (m.toColumn > m.fromColumn);

            int row = m.fromRow;
            int rookFromCol = kingSide ? 7 : 0;
            int rookToCol   = kingSide ? (m.fromColumn + 1) : (m.fromColumn - 1);

            // 1) mover rey
            board[index(m.toRow, m.toColumn)] = std::move(board[index(m.fromRow, m.fromColumn)]);
            board[index(m.toRow, m.toColumn)] -> setMoved();
            board[index(m.fromRow, m.fromColumn)] = nullptr;

            // 2) mover torre
            board[index(row, rookToCol)] = std::move(board[index(row, rookFromCol)]);
            board[index(row, rookToCol)] -> setMoved();
            board[index(row, rookFromCol)] = nullptr;
            return true;
        }

        case SpecialMove::Promotion:{
            board[index(m.toRow, m.toColumn)] = std::make_unique<Queen>(board[index(m.fromRow, m.fromColumn)] -> getColor());
            board[index(m.fromRow, m.fromColumn)] = nullptr;
            return true;
        }

        default:
            break;
    }


    if(!originPiece->hasMoved())
        originPiece->setMoved();

    board[index(m.toRow, m.toColumn)] = std::move(board[index(m.fromRow, m.fromColumn)]);
    board[index(m.fromRow, m.fromColumn)] = nullptr;

    return true;
}

// Detecta obstaculos en caminos horizontales, verticales y diagonales
bool Board::isPathClear(const movement& move) const {
    int stepRow = (move.toRow - move.fromRow == 0) ? 0 : (move.toRow > move.fromRow ? 1 : -1);  // Detecto el paso 0, derecha o izquierda
    int stepCol = (move.toColumn - move.fromColumn == 0) ? 0 : (move.toColumn > move.fromColumn ? 1 : -1);  // Detecto el paso 0, arriba o abajo

    int r = move.fromRow + stepRow;
    int c = move.fromColumn + stepCol;

    while (r != move.toRow || c != move.toColumn) {
        if (!checkEmpty(r, c))
            return false;
        r += stepRow;
        c += stepCol;
    }

    return true;
}


bool Board::isSquareAttacked(const int targetRow, const int targetColumn, PieceColor attacker) const{
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece * evalPiece = board[index(i, j)].get();
            if(evalPiece == nullptr)
                continue;
            
            if(evalPiece -> getColor() != attacker)
                continue;

            switch(evalPiece -> getType()){
                case PieceType::Pawn: {
                    // Si el contrario juega con negras, va +1
                    int direction = attacker == PieceColor::white ? -1 : +1;
                    if(i + direction == targetRow && (j + 1 == targetColumn ||  j - 1 == targetColumn))
                        return true;
                    break; 
                }

                case PieceType::Rook: {
                    if (i != targetRow && j != targetColumn)
                        break;

                    bool blocked = false;

                    // Misma fila
                    if (i == targetRow) {
                        int direction = targetColumn > j ? +1 : -1;
                        for (int k = j + direction; k != targetColumn; k += direction) {
                            Piece* aux = board[index(i, k)].get();
                            if (aux != nullptr){
                                blocked = true;
                                break;
                            }
                        }
                        
                        if(!blocked)
                            return true;
                    }

                    // Misma columna
                    else if (j == targetColumn) {
                        int direction = targetRow > i ? +1 : -1;
                        for (int k = i + direction; k != targetRow; k += direction) {
                            Piece* aux = board[index(k, j)].get();
                            if (aux != nullptr){
                                blocked = true;
                                break;
                            }
                        }

                        if(!blocked)
                            return true;
                    }

                    break;
                }

                case PieceType::Knight: {
                    if( (i + 1 == targetRow && j + 2 == targetColumn) ||
                        (i + 1 == targetRow && j - 2 == targetColumn) ||
                        (i + 2 == targetRow && j + 1 == targetColumn) ||
                        (i + 2 == targetRow && j - 1 == targetColumn) ||
                        (i - 1 == targetRow && j + 2 == targetColumn) ||
                        (i - 1 == targetRow && j - 2 == targetColumn) ||
                        (i - 2 == targetRow && j + 1 == targetColumn) ||
                        (i - 2 == targetRow && j - 1 == targetColumn) )
                        return true;
                
                    break;
                }

                case PieceType::Bishop: {
                    if (abs(targetRow - i) != abs(targetColumn - j))    // No esta en diagonal
                        break;

                    bool blocked = false;
                    int rowStep = (targetRow > i) ? +1 : -1;
                    int colStep = (targetColumn > j) ? +1 : -1;

                    for (int k = 1; k < abs(targetRow - i); k++) {
                        if (board[index(i + k * rowStep, j + k * colStep)] != nullptr) {
                            blocked = true;
                            break;
                        }
                    }

                    if (!blocked)
                        return true;

                    break;
                }

                case PieceType::King: {
                     if( (i + 1 == targetRow && j + 0 == targetColumn) ||
                        (i + 1 == targetRow && j + 1 == targetColumn) ||
                        (i + 1 == targetRow && j - 1 == targetColumn) ||
                        (i - 1 == targetRow && j + 0 == targetColumn) ||
                        (i - 1 == targetRow && j + 1 == targetColumn) ||
                        (i - 1 == targetRow && j - 1 == targetColumn) ||
                        (i + 0 == targetRow && j + 1 == targetColumn) ||
                        (i + 0 == targetRow && j - 1 == targetColumn))
                        return true;
                
                    break;
                }

                case PieceType::Queen: {
                    bool blocked = false;
                    if (i == targetRow || j == targetColumn){
                        // Misma fila
                        if (i == targetRow) {
                            int direction = targetColumn > j ? +1 : -1;
                            for (int k = j + direction; k != targetColumn; k += direction) {
                                Piece* aux = board[index(i, k)].get();
                                if (aux != nullptr){
                                    blocked = true;
                                    break;
                                }
                            }
                            
                            if(!blocked)
                                return true;
                        }

                        // Misma columna
                        else if (j == targetColumn) {
                            int direction = targetRow > i ? +1 : -1;
                            for (int k = i + direction; k != targetRow; k += direction) {
                                Piece* aux = board[index(k, j)].get();
                                if (aux != nullptr){
                                    blocked = true;
                                    break;
                                }
                            }

                            if(!blocked)
                                return true;
                        }
                    } else if(abs(targetRow - i) == abs(targetColumn - j)){
                        int rowStep = (targetRow > i) ? +1 : -1;
                        int colStep = (targetColumn > j) ? +1 : -1;

                        for (int k = 1; k < abs(targetRow - i); k++) {
                            if (board[index(i + k * rowStep, j + k * colStep)] != nullptr) {
                                blocked = true;
                                break;
                            }
                        }

                        if (!blocked)
                            return true;

                    } 

                    break;
                }

            }

        }
    }

    return false;

}

Position Board::findKing(PieceColor color) const{
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece * kingCandidate = board[index(i,j)].get();
            if(kingCandidate == nullptr)
                continue;

            if(kingCandidate -> getType() == PieceType::King && kingCandidate -> getColor() == color)
                return Position{i,j};

        }
    }

    throw std::logic_error("King not found on board");
}

bool Board::isKingInCheck(PieceColor color) const {
    Position k = findKing(color);
    return isSquareAttacked(k.row, k.col, color == PieceColor::white ? PieceColor::black : PieceColor::white);
}