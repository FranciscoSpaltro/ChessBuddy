#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"
#include "Board.h"

class Knight : public Piece {
public:
    explicit Knight(PieceColor color);

    bool isValidMove(const Board& board, const movement& move) const override;

    char symbol() const override;

    bool canJump() const override;

    std::vector<movement> pseudoLegalMoves(int r, int c, const Board& board) const override;
};

#endif
