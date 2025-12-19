#include "King.h"
#include <stdlib.h>

King::King(pieceColor color) : Piece(color) {}

bool King::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza
    // La validacion de si el rey queda en jaque la hace Game
    // Tampoco implemento enroque aca

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(deltaRow == 0 && abs(deltaCol) == 2)     // Posible enroque
        return true;

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

SpecialMove King::getSpecialMove(const movement& m) const {
    // ENROQUE: aun no se ha movido y se desplaza desde el origen 2 columnas de distancia en la misma fila
    if(hasMoved())
        return SpecialMove::None;

    if(m.fromRow == m.toRow && abs(m.toColumn - m.fromColumn) == 2)
        return SpecialMove::Castling;
    
    return SpecialMove::None;
}