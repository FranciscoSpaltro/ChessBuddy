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

std::vector<movement> Pawn::pseudoLegalMoves(int r, int c, const Board& board) const {
    std::vector<movement> moves;
    PieceColor color = this->getColor();

    // Se mueve 1 adelante, 2 adelante si no se movio, diagonal para capturar si hay del contrario y diagonal vacio si es EnPassant
    int dir = color == PieceColor::white ? -1 : +1;
    int nr = r + dir;
    if (nr >= 0 && nr <= 7){
        if(board.checkEmpty(nr, c))
            moves.push_back(movement{r, c, nr, c});
        
        if(c + 1 <= 7 && board.isEnemyAt(nr, c + 1, color))
            moves.push_back(movement{r, c, nr, c + 1});

        if(c - 1 >= 0 && board.isEnemyAt(nr, c - 1, color))
            moves.push_back(movement{r, c, nr, c - 1});
    }

    int nr2 = r + 2*dir;
    if (!this->hasMoved() && nr2 >= 0 && nr2 <= 7 && board.checkEmpty(nr, c) && board.checkEmpty(nr2, c))
        moves.push_back(movement{r, c, nr2, c});

    const EnPassantTarget* ep = board.getEnPassantTarget();

    if (ep->valid && ep->row == nr && std::abs(ep->col - c) == 1)
        moves.push_back(movement{r, c, ep->row, ep->col});

    return moves;
}