#include "Bishop.h"
#include <stdlib.h>

Bishop::Bishop(PieceColor color) : Piece(color) {
    type = PieceType::Bishop;
}

bool Bishop::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(abs(deltaRow) != abs(deltaCol))  // Movimiento no diagonal
        return false;

    return true;
}

char Bishop::symbol() const {
    return (getColor() == PieceColor::white) ? 'B' : 'b';
}

bool Bishop::canJump() const {
    return false;
}
