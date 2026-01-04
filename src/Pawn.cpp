#include "Pawn.h"
#include <stdlib.h>

Pawn::Pawn(PieceColor color) : Piece(color) {
    type = PieceType::Pawn;
}

bool Pawn::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    int direction = (getColor() == PieceColor::white) ? -1 : 1;
    
    if (deltaRow != direction){
        // Evaluo primer movimiento
        int startRow = (getColor() == PieceColor::white) ? 6 : 1;
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
    return (getColor() == PieceColor::white) ? 'P' : 'p';
}

bool Pawn::canJump() const {
    return false;
}

SpecialMove Pawn::getSpecialMove(const movement& m) const {
    int promotionRow = getColor() == PieceColor::white ? 0 : 7;

    if(m.toRow == promotionRow){
        return SpecialMove::Promotion;
    }

    // Posible passant (forma geometrica del movimiento -> diagonal)
    int dir = getColor() == PieceColor::white ? -1 : +1;
    if(m.fromRow == m.toRow + dir && std::abs(m.fromColumn - m.toColumn) == 1){
        return SpecialMove::EnPassant;
    }
    
    return SpecialMove::None;

}
