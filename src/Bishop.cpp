#include "Bishop.h"
#include <stdlib.h>

bool Bishop::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(abs(deltaRow) != abs(deltaCol))  // Movimiento no diagonal
        return false;

    if(!board.isPathClear(move))
        return false;

    return true;
}

char Bishop::symbol() const {
    return (getColor() == PieceColor::white) ? 'B' : 'b';
}
