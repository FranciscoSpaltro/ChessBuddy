#ifndef PIECE_H
#define PIECE_H

#include "movement.h"

enum class PieceColor {
    white,
    black
};

enum class SpecialMove {
    None,
    Castling,
    EnPassant,
    Promotion
};

enum class PieceType {
    King,
    Queen,
    Bishop,
    Knight,
    Rook,
    Pawn
};

class Board;

class Piece {
    protected:
        PieceType type;
        PieceColor color;
        bool moved;

    public:
        explicit Piece(PieceColor color);
        virtual ~Piece() = default;

        PieceColor getColor() const;
        PieceType getType() const;
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
