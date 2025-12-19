#include "Rook.h"
#include <stdlib.h>

bool Rook::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(deltaRow != 0 && deltaCol != 0)  // Movimiento no recto
        return false;

    if(!board.isPathClear(move))
        return false;

    return true;
}

char Rook::symbol() const {
    return (getColor() == PieceColor::white) ? 'R' : 'r';
}
