#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"

class King : public Piece {
public:
    explicit King(pieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;
};

#endif
