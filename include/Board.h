#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>
#include <iostream>

#include "Piece.h"
#include "movement.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"


class Board {
private:
    std::array<std::unique_ptr<Piece>, 64> board;

    int index(int row, int column) const;
    void initialize();
    bool isCastling(movement& m);

public:
    Board();

    bool checkEmpty(int row, int column) const;
    const Piece* getPiece(int row, int column) const;
    bool isPathClear(const movement& move) const;
    bool isEnemyAt(int row, int col, pieceColor myColor) const;

    bool move(const movement& m);
    bool isValidMove(const movement& m) const;

    void printBoard() const;
};

#endif
