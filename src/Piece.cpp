#include "piece.h"

Piece::Piece(PieceColor color) : color(color), moved(false) {}

PieceColor Piece::getColor() const {
    return color;
}

PieceType Piece::getType() const {
    return type;
}

bool Piece::hasMoved() const {
    return moved;
}

bool Piece::setMoved() {
    moved = true;
    return moved;
}


