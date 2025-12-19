#include "Knight.h"
#include <stdlib.h>

Knight::Knight(pieceColor color) : Piece(color) {}

bool Knight::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(!((abs(deltaRow) == 2 && abs(deltaCol) == 1) || (abs(deltaRow) == 1 && abs(deltaCol) == 2)))  // Movimiento no caballo
        return false;

    return true;
}

char Knight::symbol() const {
    return (getColor() == pieceColor::white) ? 'N' : 'n';
}

bool Knight::canJump() const {
    return true;
}