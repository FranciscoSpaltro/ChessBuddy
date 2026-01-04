#ifndef KING_H
#define KING_H

#include "Piece.h"
#include "Board.h"

class King : public Piece {
public:
    explicit King(PieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;

    SpecialMove getSpecialMove(const movement& m) const override;

    std::vector<movement> pseudoLegalMoves(int r, int c, const Board& board) const override;

};

#endif
