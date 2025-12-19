#include "piece.h"

Piece::Piece(pieceColor color) : color(color), moved(false) {}

pieceColor Piece::getColor() const {
    return color;
}

bool Piece::hasMoved() const {
    return moved;
}

bool Piece::setMoved() {
    moved = true;
    return moved;
}


