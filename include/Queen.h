#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"
#include "Board.h"

class Queen : public Piece {
public:
    explicit Queen(PieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;
};

#endif
