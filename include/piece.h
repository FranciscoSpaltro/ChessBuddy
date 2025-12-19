#ifndef PIECE_H
#define PIECE_H

#include "movement.h"

enum class PieceColor {
    white,
    black
};

class Board;

class Piece {
    protected:
        PieceColor color;

    public:
        explicit Piece(PieceColor color);
        virtual ~Piece() = default;

        virtual char symbol() const = 0;
        PieceColor getColor() const;
        virtual bool isValidMove(const Board& board, const movement& move) const = 0;
};

#endif
