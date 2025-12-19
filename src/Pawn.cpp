#include "Pawn.h"
#include <stdlib.h>

Pawn::Pawn(pieceColor color) : Piece(color) {}

bool Pawn::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    int direction = (getColor() == pieceColor::white) ? -1 : 1;
    
    if (deltaRow != direction){
        // Evaluo primer movimiento
        int startRow = (getColor() == pieceColor::white) ? 6 : 1;
        if (move.fromRow == startRow && deltaRow == 2 * direction) {
            int midRow = move.fromRow + direction;
            return board.checkEmpty(midRow, move.fromColumn) && board.checkEmpty(move.toRow, move.toColumn);
        } else
            return false;
    }
    
    if(deltaCol == 0){   // Movimiento de avance
        return board.checkEmpty(move.toRow, move.toColumn);

    } else if(abs(deltaCol) == 1){ // Movimiento de captura
        return board.isEnemyAt(move.toRow, move.toColumn, getColor());

    }

    return false;
}

char Pawn::symbol() const {
    return (getColor() == pieceColor::white) ? 'P' : 'p';
}

bool Pawn::canJump() const {
    return false;
}