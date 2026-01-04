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

struct EnPassantTarget {
    bool valid = false;
    // Casillas a la que se moveria el peon capturador (una fila anterior al movimiento)
    int row = -1;
    int col = -1;
    PieceColor capturablePawnColor; // color del peón que puede ser capturado (el que movió doble)
};

class Board {
private:
    std::array<std::unique_ptr<Piece>, 64> board;
    struct EnPassantTarget ep;

    int index(int row, int column) const;
    void initialize();
    bool isCastling(const movement& m);
    Position findKing(PieceColor color) const;
    MoveRecord applyMove(const movement& m);
    void undoMove(MoveRecord& r);
    bool isEnPassantMove(const movement& m) const;
    void resetEPStatus(void);

public:
    Board();

    bool checkEmpty(int row, int column) const;
    const Piece* getPiece(int row, int column) const;
    bool isPathClear(const movement& move) const;
    bool isEnemyAt(int row, int col, PieceColor myColor) const;

    const EnPassantTarget * getEnPassantTarget(void) const;

    bool move(const movement& m);
    bool isValidMove(const movement& m) const;
    bool isSquareAttacked(const int targetRow, const int targetColumn, PieceColor playerAttacked) const;
    bool isKingInCheck(PieceColor color) const;
    bool isCheckMate(PieceColor color);
    bool isStalemate(PieceColor color);

    std::vector<movement> getLegalMoves(int r, int c);

    void printBoard() const;
};

#endif
