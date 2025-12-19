#ifndef PIECE_H
#define PIECE_H

#include "movement.h"

enum class pieceColor {
    white,
    black
};

enum class SpecialMove {
    None,
    Castling,
    EnPassant,
    Promotion
};

class Board;

class Piece {
    protected:
        pieceColor color;
        bool moved;

    public:
        explicit Piece(pieceColor color);
        virtual ~Piece() = default;

        pieceColor getColor() const;
        bool hasMoved() const;
        bool setMoved();
        virtual char symbol() const = 0;
        virtual bool isValidMove(const Board& board, const movement& move) const = 0;
        virtual bool canJump() const = 0;
        virtual SpecialMove getSpecialMove(const movement& m) const {
            return SpecialMove::None;
        }
};

#endif
