#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
#include "Board.h"

class Pawn : public Piece {
public:
    explicit Pawn(PieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;

    SpecialMove getSpecialMove(const movement& m) const override;
};

#endif
