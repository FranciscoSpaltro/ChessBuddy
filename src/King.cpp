#include "King.h"
#include <stdlib.h>

King::King(pieceColor color) : Piece(color) {}

bool King::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza
    // La validacion de si el rey queda en jaque la hace Game
    // Tampoco implemento enroque aca

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if (std::max(abs(deltaRow), abs(deltaCol)) != 1)
        return false;

    return true;
}

char King::symbol() const {
    return (getColor() == pieceColor::white) ? 'K' : 'k';
}

bool King::canJump() const {
    return false;
}