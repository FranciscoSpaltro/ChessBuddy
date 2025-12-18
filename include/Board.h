#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "piece.h"
#include "movement.h"

class Board {
    private:
        std::array<piece, 64> board;

        int index(int row, int column) const;
        void initialize(void);
        bool checkEmpty(int row, int column) const;

    public:
        Board(void);
        piece whatIsIn(int row, int column);     // @note: mas adelante, devolver const peice&
        bool move(const movement& m, pieceColor player);
        void printBoard(void) const;
        bool isValidMove(const movement& m, pieceColor player) const;

};

#endif