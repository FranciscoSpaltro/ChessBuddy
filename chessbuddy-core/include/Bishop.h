#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"

class Bishop : public Piece {
public:
    explicit Bishop(PieceColor color);

    bool isValidMove(const Board& /*board*/, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;

    std::vector<movement> pseudoLegalMoves(int r, int c, const Board& board) const override;
};

#endif
