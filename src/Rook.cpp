#include "Rook.h"
#include <stdlib.h>

Rook::Rook(PieceColor color) : Piece(color) {
    type = PieceType::Rook;
}

bool Rook::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(deltaRow != 0 && deltaCol != 0)  // Movimiento no recto
        return false;

    return true;
}

char Rook::symbol() const {
    return (getColor() == PieceColor::white) ? 'R' : 'r';
}

bool Rook::canJump() const {
    return false;
}