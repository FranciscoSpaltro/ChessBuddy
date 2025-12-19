#ifndef PIECE_H
#define PIECE_H

#include "movement.h"

enum class pieceColor {
    white,
    black
};

class Board;

class Piece {
    protected:
        pieceColor color;

    public:
        explicit Piece(pieceColor color);
        virtual ~Piece() = default;

        virtual char symbol() const = 0;
        pieceColor getColor() const;
        virtual bool isValidMove(const Board& board, const movement& move) const = 0;
        virtual bool canJump() const = 0;
};

#endif
