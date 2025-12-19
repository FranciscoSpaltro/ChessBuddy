#include "Queen.h"
#include <stdlib.h>

bool Queen::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if((abs(deltaRow) != abs(deltaCol)) && (deltaRow != 0 && deltaCol != 0))  // Movimiento no puramente diagonal o puramente recto
        return false;

    if(!board.isPathClear(move))
        return false;

    return true;
}

char Queen::symbol() const {
    return (getColor() == PieceColor::white) ? 'Q' : 'q';
}
