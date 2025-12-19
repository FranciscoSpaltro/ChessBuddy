#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"

class Rook : public Piece {
public:
    explicit Rook(pieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;
};

#endif
