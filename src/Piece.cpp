#include "piece.h"

Piece::Piece(PieceColor color) : color(color) {}

PieceColor Piece::getColor() const {
    return color;
}
