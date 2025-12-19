#include "Bishop.h"
#include <stdlib.h>

Bishop::Bishop(pieceColor color) : Piece(color) {}

bool Bishop::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(abs(deltaRow) != abs(deltaCol))  // Movimiento no diagonal
        return false;

    return true;
}

char Bishop::symbol() const {
    return (getColor() == pieceColor::white) ? 'B' : 'b';
}

bool Bishop::canJump() const {
    return false;
}
