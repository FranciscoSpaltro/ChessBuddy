#include "Board.h"

bool Board::checkEmpty(int row, int column) const{
    if (!this -> getPiece(row, column))
        return true;
    return false;
}

int Board::index(int row, int column) const {
return row * 8 + column;
}

void Board::initialize(void){
    this -> board[index(0, 0)] = std::make_unique<Rook>(pieceColor::black);
    this -> board[index(0, 1)] = std::make_unique<Knight>(pieceColor::black);
    this -> board[index(0, 2)] = std::make_unique<Bishop>(pieceColor::black);
    this -> board[index(0, 3)] = std::make_unique<Queen>(pieceColor::black);
    this -> board[index(0, 4)] = std::make_unique<King>(pieceColor::black);
    this -> board[index(0, 5)] = std::make_unique<Bishop>(pieceColor::black);
    this -> board[index(0, 6)] = std::make_unique<Knight>(pieceColor::black);
    this -> board[index(0, 7)] = std::make_unique<Rook>(pieceColor::black);
    this -> board[index(1, 0)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 1)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 2)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 3)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 4)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 5)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 6)] = std::make_unique<Pawn>(pieceColor::black);
    this -> board[index(1, 7)] = std::make_unique<Pawn>(pieceColor::black);

    this -> board[index(6, 0)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 1)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 2)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 3)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 4)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 5)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 6)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(6, 7)] = std::make_unique<Pawn>(pieceColor::white);
    this -> board[index(7, 0)] = std::make_unique<Rook>(pieceColor::white);
    this -> board[index(7, 1)] = std::make_unique<Knight>(pieceColor::white);
    this -> board[index(7, 2)] = std::make_unique<Bishop>(pieceColor::white);
    this -> board[index(7, 3)] = std::make_unique<Queen>(pieceColor::white);
    this -> board[index(7, 4)] = std::make_unique<King>(pieceColor::white);
    this -> board[index(7, 5)] = std::make_unique<Bishop>(pieceColor::white);
    this -> board[index(7, 6)] = std::make_unique<Knight>(pieceColor::white);
    this -> board[index(7, 7)] = std::make_unique<Rook>(pieceColor::white);
}

Board::Board(void) {
    initialize();
};

const Piece* Board::getPiece(int row, int column) const {
    return board[index(row, column)].get();
}


bool Board::isValidMove(const movement& m) const {
    const Piece* piece = getPiece(m.fromRow, m.fromColumn);
    bool capture = false;

    if (!piece)         // Si no seleccione una pieza
        return false;

    if (const Piece* target = getPiece(m.toRow, m.toColumn)) {
        if (target->getColor() == piece->getColor())            // Estaba ocupada por mi
            return false;
        else
            capture = true;
    }
    
    int dRow = abs(m.toRow - m.fromRow);
    int dCol = abs(m.toColumn - m.fromColumn);
    bool isLongMove = std::max(dRow, dCol) > 1;

    if (isLongMove && !piece->canJump())
        if(!isPathClear(m))
            return false;

    if(piece->isValidMove(*this, m)){
        if(capture){
            // Sabemos que es captura
            return true;
        }

        return true;
    }

    return false;
}

bool Board::isEnemyAt(int row, int col, pieceColor myColor) const {
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

    board[index(m.toRow, m.toColumn)] = std::move(board[index(m.fromRow, m.fromColumn)]);
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
