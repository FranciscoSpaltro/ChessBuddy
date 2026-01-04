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

struct Position {
    int row;
    int col;
};

struct MoveRecord {
    int fromRow, fromCol, toRow, toCol;
    std::unique_ptr<Piece> captured;
};

class Board {
private:
    std::array<std::unique_ptr<Piece>, 64> board;

    int index(int row, int column) const;
    void initialize();
    bool isCastling(const movement& m);
    Position findKing(PieceColor color) const;
    MoveRecord applyMove(const movement& m);
    void undoMove(MoveRecord& r);

public:
    Board();

    bool checkEmpty(int row, int column) const;
    const Piece* getPiece(int row, int column) const;
    bool isPathClear(const movement& move) const;
    bool isEnemyAt(int row, int col, PieceColor myColor) const;

    bool move(const movement& m);
    bool isValidMove(const movement& m) const;
    bool isSquareAttacked(const int targetRow, const int targetColumn, PieceColor playerAttacked) const;
    bool isKingInCheck(PieceColor color) const;

    void printBoard() const;
};

#endif
