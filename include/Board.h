#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>

#include "Piece.h"
#include "movement.h"

class Board {
private:
    std::array<std::unique_ptr<Piece>, 64> board;

    int index(int row, int column) const;
    void initialize();

public:
    Board();

    bool checkEmpty(int row, int column) const;
    const Piece* getPiece(int row, int column) const;
    bool isPathClear(const movement& move) const;
    bool Board::isEnemyAt(int row, int col, PieceColor myColor) const;

    bool move(const movement& m);
    bool isValidMove(const movement& m) const;

    void printBoard() const;
};

#endif
