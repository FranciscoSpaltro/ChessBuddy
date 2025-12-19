#include "piece.h"

Piece::Piece(pieceColor color) : color(color) {}

pieceColor Piece::getColor() const {
    return color;
}
