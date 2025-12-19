#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"

class Knight : public Piece {
public:
    explicit Knight(pieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;
};

#endif
